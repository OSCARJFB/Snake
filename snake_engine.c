#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include "snake_structures.h"
#include "snake_prototypes.h"
#include "snake_enumerations.h"
#include "snake_definitions.h"

int main(void)
{
	gameSetup();
	snake head = snakeSetup();
	food food_spawn = foodSetup();
	runGame(head, food_spawn);

	return 0;
}

void gameSetup(void)
{
	const char* SCREEN_TITLE = "Snake Game"; 

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE); 
	SetTargetFPS(60);
	srand(time(NULL));
}

snake snakeSetup(void)
{
	snake head = malloc(sizeof(struct snake));
	if(head == NULL)
	{
		exit(1); 
	}
	
	head->next = NULL;
	head->y = SCREEN_WIDTH / 2;
	head->x = SCREEN_HEIGHT / 2; 

	return head;
}

food foodSetup(void)
{
	food good_food;
	good_food.x = 20 * (rand() % (360 / 20) + 1); 
	good_food.y = 20 * (rand() % (360 / 20) + 1); 
	good_food.direction = rand() % 4 + 1;
	good_food.score = 0;
	good_food.spawned = true; 
	
	return good_food;
}

void runGame(snake head, food food_spawn)
{
	float timer = 0.0f, limit = 0.15f;
	bool pause = false, game_over = false;
	int direction = 0; 

	while(!WindowShouldClose())
	{
		BeginDrawing();

			ClearBackground(THE_VOID);

			drawGrid();
			drawBorders();
			drawScore(food_spawn.score);
			drawSnake(head);
			food_spawn = drawFood(food_spawn); 
			food_spawn = devourFood(head, food_spawn);
			pause = pauseGame(pause);

			if(borderCollision(head) || bodyCollision(head))
			{	
				game_over = gameOver(); 
			}

			if(timer >= limit && !pause && !game_over)
			{
				direction = snakeDirection(direction, pause);
				moveSnake(head, direction);
				timer = 0.0f;
			}
			else
			{
				timer += GetFrameTime();
			}

		EndDrawing();

	}

	free(head);
}

int snakeDirection(int direction, bool pause)
{
	if(!pause)
	{
		if(IsKeyDown(KEY_W) && direction != KEY_S)
		{
			direction = KEY_W;
		}
		else if(IsKeyDown(KEY_A) && direction != KEY_D)
		{
			direction = KEY_A;
		}
		else if(IsKeyDown(KEY_S) && direction != KEY_W)
		{
			direction = KEY_S;
		}
		else if(IsKeyDown(KEY_D) && direction != KEY_A)
		{
			direction  = KEY_D;
		}
	}

	return direction;
}

void moveSnake(snake head, int direction)
{
	const int speed = 20;
	
	snake body = head;
	body = body->next;

	int temp_x = 0, temp_y = 0;
	int old_x = head->x, old_y = head->y;

	switch (direction)
	{
		case KEY_W:
			head->y -= speed;
			break;
		case KEY_A:
			head->x -= speed;
			break;
		case KEY_S:
			head->y += speed;
			break;	
		case KEY_D:
			head->x += speed;
			break;
	}
	
	while(body != NULL)
	{
		temp_x = body->x, temp_y = body->y;

		body->x = old_x;
		body->y = old_y;

		old_x = temp_x, old_y = temp_y;
		body = body->next;
	}

}

void drawSnake(snake head)
{
	while(head != NULL)
	{
		DrawRectangle(head->x,   head->y, 
					  WIDTH,     HEIGHT, SNAKE_PURPLE);
								
		head = head->next;
	}
}

food drawFood(food food_spawn)
{
	if(!food_spawn.spawned)
	{
		food_spawn.x = 20 * (rand() % (360 / 20) + 1); 
		food_spawn.y = 20 * (rand() % (360 / 20) + 1); 
		food_spawn.spawned = true; 
	}

	DrawRectangle(food_spawn.x, food_spawn.y, WIDTH, HEIGHT, FOOD_GREEN);

	return food_spawn; 
}

food devourFood(snake head, food food_spawn)
{
	if(head->x == food_spawn.x && head->y == food_spawn.y)
	{
		return addSnakeParts(&head, food_spawn);
	}

	return food_spawn; 
}

food addSnakeParts(snake* head, food good_food)
{ 
	snake new_node = malloc(sizeof(struct snake));
	if(new_node == NULL)
	{
		exit(1);
	}
	
	new_node->next = NULL;
	new_node->x = -20, new_node->y = -20;

	snake current_node = *head;
	while(current_node->next != NULL)
	{
		current_node = current_node->next;
	}	
	
	current_node->next = new_node;

	good_food.spawned = false; 
	++good_food.score;

	return good_food;
}

void drawGrid(void)
{
	for(int y = 0; y <= SCREEN_HEIGHT; y += HEIGHT)
	{
		for(int x = 0; x <= SCREEN_WIDTH; x += WIDTH)
		{
			DrawRectangleLines(x, 	  y, 
							   WIDTH, HEIGHT, GRID_GRAY);
		}
	}
}

void drawBorders(void) 
{
	DrawRectangle(0, 0, 20, SCREEN_HEIGHT, BORDER_GRAY);
	DrawRectangle(0, 0, SCREEN_WIDTH, 20, BORDER_GRAY);
	DrawRectangle(SCREEN_WIDTH - 20, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BORDER_GRAY);
	DrawRectangle(0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, SCREEN_HEIGHT, BORDER_GRAY);
}

void drawScore(int score)
{
	const char* MESSAGE = "Score: %d";
	DrawText(TextFormat(MESSAGE, score), 1 ,1 , FONT_SIZE, TEXT_YELLOW);
}

bool borderCollision(snake head)
{
	bool isColliding = false; 

	if(head->x < LEFT_BORDER)
	{
		isColliding = true; 
	}

	if(head->x > RIGHT_BORDER)
	{
		isColliding = true;
	}

	if(head->y < TOP_BORDER)
	{
		isColliding = true; 
	}

	if(head->y > BOTTOM_BORDER)
	{
		isColliding = true;
	}

	return isColliding; 
}

bool bodyCollision(snake head)
{
	bool isColliding = false; 

	snake body = head; 
	body = body->next; 
	
	while(body != NULL)
	{
		if(head->x == body->x && head->y == body->y)
		{
			isColliding = true; 
			break; 
		}
		body = body->next;
	}

	return isColliding;
}

bool gameOver(void)
{
	const char* MESSAGE = "Game over!";
	DrawText(MESSAGE, SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 - 50, 
			 FONT_SIZE, TEXT_YELLOW);
	
	return true; 
}

bool pauseGame(bool pause)
{
	const char* MESSAGE = "Game is paused!";

	if(IsKeyPressed(KEY_P) && !pause)
	{
		pause = true; 
	}
	else if(IsKeyPressed(KEY_P) && pause)
	{
		pause = false; 
	}
	else if(pause)
	{	
		DrawText(MESSAGE, SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 50, 
				FONT_SIZE, TEXT_YELLOW);
	}
	
	return pause;
}