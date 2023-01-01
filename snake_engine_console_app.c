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
#include "snake_structures.h"
#include "snake_prototypes_console.h"
#include "snake_enumerations.h"
#include "snake_macros.h"

/* Used to reset terminal from raw mode. */
struct termios reset_terminal;

int main(void)
{
	if (!rawSetup())
	{
		return EXIT_FAILURE;
	}

	char gameBoard[grid_len][grid_wid];

	snake head = snakeSetup();
	food food_spawn = foodSetUp();
	boardSetup(head, food_spawn, gameBoard);
	runGame(head, food_spawn, gameBoard);

	return EXIT_SUCCESS;
}

snake snakeSetup()
{
	snake head = malloc(sizeof(snake));
	head->x = snake_spawn;
	head->y = snake_spawn;
	head->next = NULL;

	return head;
}

food foodSetUp()
{
	srand(time(NULL));
	food food_spawn;
	food_spawn.x = rand() % grid_len;
	food_spawn.y = rand() % grid_len;
	food_spawn.score = 0; 
	if (food_spawn.x == snake_spawn && food_spawn.y == snake_spawn)
	{
		++food_spawn.x;
	}

	return food_spawn;
}

void boardSetup(snake head, food food_spawn, char gameBoard[grid_len][grid_wid])
{
	for (int y = 0; y < grid_len; ++y)
	{
		for (int x = 0; x < grid_wid; ++x)
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

void runGame(snake head, food food_spawn, char gameBoard[grid_len][grid_wid])
{
	char byte, direction;

	while (byte != ESCAPE_KEY)
	{
		refreshRate();
		byte = _kbhit();
		direction = translateByte(byte, direction);
		renderBoard(gameBoard, food_spawn.score);
		moveSnake(head, direction, gameBoard);
	}
}

void refreshRate(void)
{
	int result;
	struct timespec timer;
	timer.tv_sec = 0;
	timer.tv_nsec = 100000000;

	result = nanosleep(&timer, NULL);
	if (result == FAIL)
	{
		/* Handle error. */
	}
}

int _kbhit(void)
{
	char byte = ' ';
	int result;

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

void renderBoard(char gameBoard[grid_len][grid_wid], int score)
{
	system("clear");
	printf("Score: %d\n", score);
	for (int y = 0; y < grid_len; ++y)
	{
		for (int x = 0; x < grid_wid; ++x)
		{
			if (y == 0 || y == grid_len - 1)
			{
				printf("#");
			}
			else if (x == 0 || x == grid_wid - 1)
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

void moveSnake(snake head, char direction, char gameBoard[grid_len][grid_wid])
{
	snake body = head;
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

