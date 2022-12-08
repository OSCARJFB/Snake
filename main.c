#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include "enumerations.h"

struct snake
{
	int x, y;
	struct snake* next;
};

struct food
{
	int x, y; 
	int score;
	bool spawned; 
};

void failedAlloc(void) {exit(1);}
void gameSetup(void);
void runGame(struct snake*, struct food);
void moveSnake(struct snake* head, int);
void drawSnake(struct snake*);
void drawBorders(void);
void drawGrid(void);
void drawGrid(void);

int snakeDirection(int, bool); 

struct snake* snakeSetup(void);
struct food foodSetup(void);
struct food addSnakeParts(struct snake** head, struct food food_spawn);
struct food drawFood(struct food food_spawn); 
struct food devourFood(struct snake* head, struct food food_spawn); 

bool borderCollision(struct snake* head); 
bool bodyCollision(struct snake* head);
bool gameOver(void); 
bool pauseGame(bool pause); 

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
		failedAlloc(); 
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
	food_spawn.score = 0;
	food_spawn.spawned = true; 
	
	return food_spawn;
}

void runGame(struct snake* head, struct food food_spawn)
{
	float timer = 0.0f, timer_limit = 0.2f;
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
			direction = snakeDirection(direction, pause);

			ClearBackground((Color){0, 0, 0, 0});

			drawGrid();
			drawBorders();

			drawSnake(head);
			if(timer >= timer_limit && !pause && !game_over)
			{
				moveSnake(head, direction);
				timer = 0.0f;
			}
			else
			{
				timer += GetFrameTime();
			}

			food_spawn = drawFood(food_spawn);
			food_spawn = devourFood(head, food_spawn); 

		EndDrawing();

	}

	free(head);
}

int snakeDirection(int direction, bool pause)
{
	if(!pause)
	{
		if(IsKeyDown(KEY_W) && direction != KEY_S && 
		!IsKeyDown(KEY_A) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_S))
		{
			direction = KEY_W;
		}
		else if(IsKeyDown(KEY_A) && direction != KEY_D &&
				!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_S))
		{
			direction = KEY_A;
		}
		else if(IsKeyDown(KEY_S) && direction != KEY_W && 
				!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
		{
			direction = KEY_S;
		}
		else if(IsKeyDown(KEY_D) && direction != KEY_A && 
				!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S))
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
		failedAlloc();
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
	const char* message = "Game Over!";
	DrawText(message, SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 - 45, 
			 20, (Color){255, 255, 255 ,255});
	
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
