#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include "snake_structures.h"
#include "snake_prototypes.h"
#include "snake_enumerations.h"

int main(void)
{
	gameSetup();

	struct snake* head = snakeSetup();
	struct food good_food = goodFoodSetup();
	struct food bad_food = badFoodSetup(); 

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

struct snake* snakeSetup(void)
{
	struct snake* head = malloc(sizeof(struct snake));
	if(head == NULL)
	{
		exit(1); 
	}
	
	head->next = NULL;
	head->y = SCREEN_WIDTH / 2;
	head->x = SCREEN_HEIGHT / 2; 

	return head;
}

struct food goodFoodSetup(void)
{
	struct food good_food;
	good_food.x = WIDTH * (rand() % ((SCREEN_WIDTH - 60) / 20) + 2);
	good_food.y = HEIGHT * (rand() % ((SCREEN_HEIGHT - 60) / 20) + 2);
	good_food.direction = rand() % 4 + 1, good_food.score = 0;
	good_food.status = true, good_food.spawned = true; 
	
	return good_food;
}

struct food badFoodSetup(void)
{
	struct food bad_food;
	bad_food.x = WIDTH * (rand() % ((SCREEN_WIDTH - 60) / 20) + 2);
	bad_food.y = HEIGHT * (rand() % ((SCREEN_HEIGHT - 60) / 20) + 2);
	bad_food.direction = rand() % 4 + 1, bad_food.score = 0;
	bad_food.status = false, bad_food.spawned = true; 

	return bad_food;
}

void runGame(struct snake* head, struct food good_food, struct food bad_food)
{
	float snake_timer = 0.0f, snake_timer_limit = 0.2f;
	float food_timer = 0.0f, food_timer_limit = 0.5f;
	
	bool pause, game_over, bad_food_dev; 
	pause = game_over = bad_food_dev = false;

	int direction = 0; 

	while(!WindowShouldClose())
	{
		BeginDrawing();
			
			if(borderCollision(head) || bodyCollision(head) || bad_food_dev)
			{	
				game_over = gameOver(); 
			}

			pause = pauseGame(pause);

			ClearBackground((Color){0, 0, 0, 0});

			drawGrid();
			drawBorders();
			drawScore(good_food);
			drawSnake(head);
			good_food = drawFood(good_food);
			bad_food = drawFood(bad_food);
			
			good_food = devourFood(head, good_food, &bad_food_dev); 
			bad_food = devourFood(head, bad_food, &bad_food_dev); 

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

void moveSnake(struct snake* head, int direction)
{
	const int speed = 20;
	
	struct snake* body = head;
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

struct food moveFood(struct food good_food)
{
	const int speed = 20;
	int select_direction = good_food.direction;

	if(good_food.x >= RIGHT_BORDER)
	{
		select_direction = select_direction == RIGHT_UP ? LEFT_UP : LEFT_DOWN;
	}
	else if(good_food.x <= LEFT_BORDER)
	{
		select_direction = select_direction == LEFT_UP ? RIGHT_UP : RIGHT_DOWN;
	}
	else if(good_food.y <= TOP_BORDER)
	{
		select_direction = select_direction == LEFT_UP ? LEFT_DOWN : RIGHT_DOWN;
	} 
	else if(good_food.y >= BOTTOM_BORDER)
	{
		select_direction = select_direction == LEFT_DOWN ? LEFT_UP : RIGHT_UP;
	} 

	good_food.direction = select_direction;

	switch(good_food.direction)
	{
		case LEFT_UP:
			good_food.y -= speed;
			good_food.x -= speed; 
			break;
		case RIGHT_UP:
			good_food.y -= speed;
			good_food.x += speed; 
			break;
		case LEFT_DOWN:
			good_food.y += speed;
			good_food.x -= speed; 
			break;
		case RIGHT_DOWN:
			good_food.y += speed;
			good_food.x += speed; 
			break;
	}
	 
	return good_food; 
}

void drawSnake(struct snake* head)
{
	struct snake* body = head;

	while(body != NULL)
	{
		DrawRectangle(body->x,   body->y, 
					  WIDTH,     HEIGHT, (Color){100, 40, 110, 255});
								
		body = body->next;
	}
}

struct food drawFood(struct food food_spawn)
{
	if(!food_spawn.spawned)
	{
		food_spawn.x = WIDTH * (rand() % ((SCREEN_WIDTH - 60) / 20) + 2);
		food_spawn.y = HEIGHT * (rand() % ((SCREEN_HEIGHT - 60) / 20) + 2);
		food_spawn.spawned = true; 
	}

	if(food_spawn.status)
	{
		DrawRectangle(food_spawn.x, food_spawn.y, WIDTH, HEIGHT, (Color){0, 255, 0, 255});
	}
	else
	{
		DrawRectangle(food_spawn.x, food_spawn.y, WIDTH, HEIGHT, (Color){255, 0, 0, 255}); 
	}

	return food_spawn; 
}

struct food devourFood(struct snake* head, struct food food_spawn, bool* bad_food_dev)
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

struct food addSnakeParts(struct snake** head, struct food good_food)
{ 
	struct snake* new_node = malloc(sizeof(struct snake));
	if(new_node == NULL)
	{
		exit(1);
	}
	
	new_node->next = NULL;
	new_node->x = -20, new_node->y = -20;

	struct snake* current_node = *head;
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
							   WIDTH, HEIGHT, (Color){100, 100, 100, 150});
		}
	}
}

void drawBorders(void) 
{
	DrawRectangle(0, 0, 20, SCREEN_HEIGHT, 
				 (Color){100, 100, 100, 255});
	DrawRectangle(0, 0, SCREEN_WIDTH, 20, 
				 (Color){100, 100, 100, 255});
	DrawRectangle(SCREEN_WIDTH - 20, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 
				 (Color){100, 100, 100, 255});
	DrawRectangle(0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, SCREEN_HEIGHT, 
			     (Color){100, 100, 100, 255});
}

void drawScore(struct food good_food)
{
	const char* MESSAGE = "Score: %d";
	DrawText(TextFormat(MESSAGE, good_food.score),1 ,1 , FONT_SIZE, (Color){255, 255, 0, 255});
}

bool borderCollision(struct snake* head)
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

bool bodyCollision(struct snake* head)
{
	bool isColliding = false; 

	struct snake* body = head; 
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
	const char* MESSAGE = "Game Over!";
	DrawText(MESSAGE, SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 - 45, 
			 FONT_SIZE, (Color){255, 255, 0, 255});
	
	return true; 
}

bool pauseGame(bool pause)
{
	if(IsKeyPressed(KEY_P) && !pause)
	{
		pause = true; 
	}
	else if(IsKeyPressed(KEY_P) && pause)
	{
		pause = false; 
	}
	
	return pause;
}
