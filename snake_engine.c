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
	struct food food_spawn = foodSetup();
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

struct food foodSetup(void)
{
	struct food food_spawn;
	food_spawn.x = WIDTH * (rand() % ((SCREEN_WIDTH - 60) / 20) + 2);
	food_spawn.y = HEIGHT * (rand() % ((SCREEN_HEIGHT - 60) / 20) + 2);
	food_spawn.direction = rand() % 4 + 1;
	food_spawn.score = 0;
	food_spawn.spawned = true; 
	
	return food_spawn;
}

void runGame(struct snake* head, struct food food_spawn)
{
	float snake_timer = 0.0f, snake_timer_limit = 0.2f;
	float food_timer = 0.0f, food_timer_limit = 0.5f;

	int direction = 0; 
	bool pause = false, game_over = false; 

	while(!WindowShouldClose())
	{
		BeginDrawing();
			
			if(borderCollision(head) || bodyCollision(head))
			{	
					game_over = gameOver(); 
			}

			pause = pauseGame(pause);

			ClearBackground((Color){0, 0, 0, 0});

			drawGrid();
			drawBorders();
			drawScore(food_spawn);

			drawSnake(head);
			food_spawn = drawFood(food_spawn);
			food_spawn = devourFood(head, food_spawn); 

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
				food_spawn = moveFood(food_spawn);
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

struct food moveFood(struct food food_spawn)
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

void drawSnake(struct snake* head)
{
	struct snake* body = head;

	while(body != NULL)
	{
		DrawRectangle(body->x,   body->y, 
					  WIDTH,     HEIGHT, (Color){0, 255, 0, 255});

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

	DrawRectangle(food_spawn.x, food_spawn.y, WIDTH, HEIGHT, (Color){255, 0, 0, 255}); 

	return food_spawn; 
}

struct food devourFood(struct snake* head, struct food food_spawn)
{
	if(head->x == food_spawn.x && head->y == food_spawn.y)
	{
		return addSnakeParts(&head, food_spawn);
	}

	return food_spawn; 
}

struct food addSnakeParts(struct snake** head, struct food food_spawn)
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

	food_spawn.spawned = false; 
	++food_spawn.score;

	return food_spawn;
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

void drawScore(struct food food_spawn)
{
	const char* MESSAGE = "Score: %d";
	DrawText(TextFormat(MESSAGE, food_spawn.score),1 ,1 , FONT_SIZE, (Color){255, 255, 0, 255});
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
	if(IsKeyPressed(KEY_P)&& !pause)
	{
		pause = true; 
	}
	else if(IsKeyPressed(KEY_P) && pause)
	{
		pause = false; 
	}
	
	return pause;
}
