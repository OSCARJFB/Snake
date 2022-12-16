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
	food good_food = goodFoodSetup();
	food bad_food = badFoodSetup(); 

	runGame(head, good_food, bad_food);

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

food goodFoodSetup(void)
{
	food good_food;
	good_food.x = WIDTH * (rand() % ((SCREEN_WIDTH - 60) / 20) + 2);
	good_food.y = HEIGHT * (rand() % ((SCREEN_HEIGHT - 60) / 20) + 2);
	good_food.direction = rand() % 4 + 1, good_food.score = 0;
	good_food.status = true, good_food.spawned = true; 
	
	return good_food;
}

food badFoodSetup(void)
{
	food bad_food;
	bad_food.x = WIDTH * (rand() % ((SCREEN_WIDTH - 60) / 20) + 2);
	bad_food.y = HEIGHT * (rand() % ((SCREEN_HEIGHT - 60) / 20) + 2);
	bad_food.direction = rand() % 4 + 1, bad_food.score = 0;
	bad_food.status = false, bad_food.spawned = true; 

	return bad_food;
}

void runGame(snake head, food good_food, food bad_food)
{
	float snake_timer = 0.0f, snake_timer_limit = 0.15f;
	float food_timer = 0.0f, food_timer_limit = 0.3f;
	
	bool pause, game_over, bad_food_dev; 
	pause = game_over = bad_food_dev = false;

	int direction = 0; 

	while(!WindowShouldClose())
	{
		BeginDrawing();

			ClearBackground(THE_VOID);

			drawGrid();
			drawBorders();
			drawScore(good_food);
			drawSnake(head);
			good_food = drawFood(good_food);
			bad_food = drawFood(bad_food);
			
			good_food = devourFood(head, good_food, &bad_food_dev); 
			bad_food = devourFood(head, bad_food, &bad_food_dev); 

			pause = pauseGame(pause);
			if(borderCollision(head) || bodyCollision(head) || bad_food_dev)
			{	
				game_over = gameOver(); 
			}

			if(snake_timer >= snake_timer_limit && !pause && !game_over)
			{
				direction = snakeDirection(direction, pause);
				moveSnake(head, direction);
				snake_timer = 0.0f;
			}
			else
			{
				snake_timer += GetFrameTime();
			}

			if(food_timer >= food_timer_limit && !pause && !game_over)
			{
				good_food = moveFood(good_food);
				bad_food = moveFood(bad_food);
				food_timer = 0.0f;
			}
			else
			{
				food_timer += GetFrameTime();
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

food moveFood(food food_spawn)
{
	const int speed = 20;
	int select_direction = food_spawn.direction;

	if(food_spawn.x >= RIGHT_BORDER)
	{
		select_direction = select_direction == RIGHT_UP ? LEFT_UP : LEFT_DOWN;
	}
	else if(food_spawn.x <= LEFT_BORDER)
	{
		select_direction = select_direction == LEFT_UP ? RIGHT_UP : RIGHT_DOWN;
	}
	else if(food_spawn.y <= TOP_BORDER)
	{
		select_direction = select_direction == LEFT_UP ? LEFT_DOWN : RIGHT_DOWN;
	} 
	else if(food_spawn.y >= BOTTOM_BORDER)
	{
		select_direction = select_direction == LEFT_DOWN ? LEFT_UP : RIGHT_UP;
	} 

	food_spawn.direction = select_direction;

	switch(food_spawn.direction)
	{
		case LEFT_UP:
			food_spawn.y -= speed;
			food_spawn.x -= speed; 
			break;
		case RIGHT_UP:
			food_spawn.y -= speed;
			food_spawn.x += speed; 
			break;
		case LEFT_DOWN:
			food_spawn.y += speed;
			food_spawn.x -= speed; 
			break;
		case RIGHT_DOWN:
			food_spawn.y += speed;
			food_spawn.x += speed; 
			break;
	}
	 
	return food_spawn; 
}

void drawSnake(snake head)
{
	snake body = head;

	while(body != NULL)
	{
		DrawRectangle(body->x,   body->y, 
					  WIDTH,     HEIGHT, SNAKE_PURPLE);
								
		body = body->next;
	}
}

food drawFood(food food_spawn)
{
	if(!food_spawn.spawned)
	{
		food_spawn.x = WIDTH * (rand() % ((SCREEN_WIDTH - 60) / 20) + 2);
		food_spawn.y = HEIGHT * (rand() % ((SCREEN_HEIGHT - 60) / 20) + 2);
		food_spawn.spawned = true; 
	}

	if(food_spawn.status)
	{
		DrawRectangle(food_spawn.x, food_spawn.y, WIDTH, HEIGHT, FOOD_GREEN);
	}
	else
	{
		DrawRectangle(food_spawn.x, food_spawn.y, WIDTH, HEIGHT, FOOD_RED); 
	}

	return food_spawn; 
}

food devourFood(snake head, food food_spawn, bool* bad_food_dev)
{
	if(head->x == food_spawn.x && head->y == food_spawn.y && food_spawn.status)
	{
		return addSnakeParts(&head, food_spawn);
	}
	else if(head->x == food_spawn.x && head->y == food_spawn.y && !food_spawn.status)
	{
		*bad_food_dev = true;
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
	DrawRectangle(0, 0, 20, SCREEN_HEIGHT, 
				 BORDER_GRAY);
	DrawRectangle(0, 0, SCREEN_WIDTH, 20, 
				 BORDER_GRAY);
	DrawRectangle(SCREEN_WIDTH - 20, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 
				 BORDER_GRAY);
	DrawRectangle(0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, SCREEN_HEIGHT, 
			     BORDER_GRAY);
}

void drawScore(food good_food)
{
	const char* MESSAGE = "Score: %d";
	DrawText(TextFormat(MESSAGE, good_food.score),1 ,1 , FONT_SIZE, TEXT_YELLOW);
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

void snakeFoodCollision(food spawn_food)
{
}