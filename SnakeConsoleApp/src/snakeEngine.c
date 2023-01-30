/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "snakeStructures.h"
#include "snakePrototypes.h"
#include "snakeEnums.h"
#include "snakeMacros.h"

/* Used to reset terminal from raw mode. */
struct termios reset_terminal;

int main(void)
{
	if (!rawSetup())
	{
		return EXIT_FAILURE;
	}

	char gameBoard[grid_height][grid_width];

	srand(time(NULL));
	snake *head = snakeSetup();
	food food_spawn = foodSetUp();
	boardSetup(head, food_spawn, gameBoard);
	runGame(head, food_spawn, gameBoard);

	return EXIT_SUCCESS;
}

snake *snakeSetup(void)
{
	snake *head = malloc(sizeof(snake));
	if (head == NULL)
	{
		printf("snakeSetup: invalid nullptr error.");
		exit(EXIT_FAILURE);
	}

	head->x = snake_spawn_x;
	head->y = snake_spawn_y;
	head->next = NULL;

	return head;
}

food foodSetUp(void)
{
	food food_spawn;

	food_spawn.x = rand() % (grid_width - 2) + 1;
	food_spawn.y = rand() % (grid_height - 2) + 1;
	food_spawn.score = 0;
	food_spawn.spawned = true;

	if (food_spawn.x == snake_spawn_x && food_spawn.y == snake_spawn_y)
	{
		++food_spawn.x;
	}

	return food_spawn;
}

void boardSetup(snake *head, food food_spawn, char gameBoard[grid_height][grid_width])
{
	for (int y = 0; y < grid_height; ++y)
	{
		for (int x = 0; x < grid_width; ++x)
		{
			if (head->x == x && head->y == y)
			{
				gameBoard[y][x] = 'O';
			}
			else if (food_spawn.x == x && food_spawn.y == y)
			{
				gameBoard[y][x] = 'X';
			}
			else
			{
				gameBoard[y][x] = ' ';
			}
		}
	}
}

void runGame(snake *head, food food_spawn, char gameBoard[grid_height][grid_width])
{
	char byte, direction;

	while (byte != ESCAPE_KEY)
	{
		refreshRate();
		byte = _kbhit();
		direction = translateByte(byte, direction);
		renderBoard(gameBoard, food_spawn.score);
		moveSnake(head, direction, gameBoard);
		food_spawn = devourFood(food_spawn, head);
		printf("y: %d x: %d\n", food_spawn.y, food_spawn.x);
		addSnakeParts(&head, food_spawn.spawned);
		food_spawn = spawnFood(food_spawn, gameBoard, head);
		if (borderCollision(head) || snakecollision(head))
		{
			printf("\nS C O R E :  %d\n", food_spawn.score);
			printf("\nG A M E  O V E R !\n\n");
			break;
		}
	}

	free(head);
	head = NULL;
}

void refreshRate(void)
{
	int result = 0;
	struct timespec timer;
	timer.tv_sec = 0;
	timer.tv_nsec = SECOND / 6;

	result = nanosleep(&timer, NULL);
	if (result == FAIL)
	{
		printf("refreshRate: error.");
		exit(EXIT_FAILURE);
	}
}

int _kbhit(void)
{
	char byte = ' ';
	int result = 0;

	result = read(STDIN_FILENO, &byte, ONE_BYTE);
	return byte = result == SUCCESS ? byte : FAIL;
}

int translateByte(char byte, char direction)
{
	switch (byte)
	{
	case 'w':
		if (direction != 's')
		{
			direction = byte;
		}
		break;
	case 'a':
		if (direction != 'd')
		{
			direction = byte;
		}
		break;
	case 's':
		if (direction != 'w')
		{
			direction = byte;
		}
		break;
	case 'd':
		if (direction != 'a')
		{
			direction = byte;
		}
		break;
	default:
		break;
	}

	return direction;
}

int rawSetup()
{
	int result = 0;

	result = tcgetattr(STDIN_FILENO, &reset_terminal);
	if (result == FAIL)
	{
		return FAIL;
	}

	atexit(rawDisable);

	struct termios raw_terminal;
	if (memcpy(&raw_terminal, &reset_terminal, sizeof(struct termios)) == NULL)
	{
		return FAIL;
	}

	raw_terminal.c_lflag &= ~(ICANON | ECHO);
	raw_terminal.c_cc[VMIN] = 0;
	raw_terminal.c_cc[VTIME] = 0;

	result = tcsetattr(STDIN_FILENO, TCSANOW, &raw_terminal);
	if (result == FAIL)
	{
		return FAIL;
	}

	return SUCCESS;
}

void rawDisable()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &reset_terminal);
}

void renderBoard(char gameBoard[grid_height][grid_width], int score)
{
	system("clear");
	printf("Score: %d\n", score);
	for (int y = 0; y < grid_height; ++y)
	{
		for (int x = 0; x < grid_width; ++x)
		{
			if (y == 0 || y == grid_height - 1 || x == 0 || x == grid_width - 1)
			{
				printf("#");
			}
			else
			{
				printf("%c", gameBoard[y][x]);
			}
		}
		printf("\n");
	}
}

void moveSnake(snake *head, char direction, char gameBoard[grid_height][grid_width])
{
	snake *body = head;
	body = body->next;

	int temp_x, temp_y;
	int old_X = head->x, old_y = head->y;

	gameBoard[old_y][old_X] = ' ';

	switch (direction)
	{
	case 'w':
		head->y -= 1;
		break;
	case 'a':
		head->x -= 1;
		break;
	case 's':
		head->y += 1;
		break;
	case 'd':
		head->x += 1;
		break;
	}

	gameBoard[head->y][head->x] = 'O';

	while (body != NULL)
	{
		temp_x = body->x, temp_y = body->y;
		body->x = old_X, body->y = old_y;

		gameBoard[body->y][body->x] = 'O';
		gameBoard[temp_y][temp_x] = ' ';

		old_X = temp_x, old_y = temp_y;

		body = body->next;
	}
}

food devourFood(food food_spawn, snake *head)
{
	if (head->x == food_spawn.x && head->y == food_spawn.y)
	{
		++food_spawn.score;
		food_spawn.spawned = false;
	}

	return food_spawn;
}

food spawnFood(food food_spawn, char gameBoard[grid_height][grid_width], snake *head)
{
	if (food_spawn.spawned == false)
	{
		food_spawn.x = rand() % (grid_width - 2) + 1;
		food_spawn.y = rand() % (grid_height - 2) + 1;
		gameBoard[food_spawn.y][food_spawn.x] = 'X';
		food_spawn.spawned = true;

		preventOverlapping(&food_spawn.x, &food_spawn.y, &head);
	}

	return food_spawn;
}

void preventOverlapping(int *x, int *y, snake **head)
{	
	int n_x = 1, n_y = 1; 
	bool overlapping = false; 
	snake *check_head = *head; 
	while(check_head != NULL)
	{
		if(check_head->x == *x && check_head->y == *y)
		{
			*y = n_y; 
			check_head = *head; 

			/* New row */
			if(n_x == grid_width - 2 && n_y != grid_height - 2)
			{
				++n_y;
				n_x = 0;
			}

			*x = n_x++;

			/* DEBUG LOGGING */
			FILE *f;
			f = fopen("x.log", "a+");
			fprintf(f, "Overlapping, so setting new values x/y to, x:%d y:%d\n", *x, *y); 
			fclose(f);
		} 

		check_head = check_head->next; 
	}
}

void addSnakeParts(snake **head, bool food_is_spawned)
{
	if (food_is_spawned == true)
	{
		return;
	}

	snake *new_node = malloc(sizeof(snake));
	if (new_node == NULL)
	{
		printf("addSnakeParts: invalid nullptr error.");
		exit(EXIT_FAILURE);
	}

	new_node->next = NULL;

	snake *current_node = *head;
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}

	current_node->next = new_node;
}

bool snakecollision(snake *head)
{
	bool colliding = false;
	int x = head->x, y = head->y;

	head = head->next;

	while (head != NULL)
	{
		if (head->x == x && head->y == y)
		{
			colliding = true;
			break;
		}
		head = head->next;
	}

	return colliding;
}

bool borderCollision(snake *head)
{
	bool colliding = false;

	if (head->x <= grid_width - grid_width || head->x >= grid_width - 1)
	{
		colliding = true;
	}

	if (head->y <= grid_height - grid_height || head->y >= grid_height - 1)
	{
		colliding = true;
	}

	return colliding;
}
