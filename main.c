#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>

enum snake_properties
{
	HEIGHT = 20,
	WIDTH = 20,
};

enum screen_properties
{
	SCREEN_WIDTH = 480,
	SCREEN_HEIGHT = 720,
};

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
struct snake* snakeSetup(void);
struct food foodSetup(void);
void runGame(struct snake*, struct food);
int snakeDirection(int); 
void moveSnake(struct snake* head, int);
void drawSnake(struct snake*);
struct food addSnakeParts(struct snake** head, struct food food_spawn, 
						  int, 				   int);
struct food drawFood(struct food food_spawn); 
struct food devourFood(struct snake* head, struct food food_spawn); 
void drawBorders(void);
bool borderCollision(struct snake* head); 
bool bodyCollision(struct snake* head);
void gameOver(); 

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
	food_spawn.x = rand() % (SCREEN_WIDTH - 10) + 10;
	food_spawn.y = rand() % (SCREEN_HEIGHT - 10) + 10;
	food_spawn.score = 0;
	food_spawn.spawned = true; 

	return food_spawn;
}

void runGame(struct snake* head, struct food food_spawn)
{
	float timer = 0.0f, timer_limit = 0.2f;
	int direction = 0; 
	
	while(!WindowShouldClose())
	{
		direction = snakeDirection(direction);

		BeginDrawing();
			
			ClearBackground((Color){0, 0, 0, 0}); 
			
			drawBorders();
			drawSnake(head);

			if(timer >= timer_limit)
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
			
			if(borderCollision(head))
			{
				gameOver(); 
			}

		EndDrawing();			
	}

	free(head);
}

int snakeDirection(int direction)
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

struct food addSnakeParts(struct snake** head, struct food food_spawn, 
				  		 int x, 			  int y)
{
	struct snake* new_snake = malloc(sizeof(struct snake));
	if(new_snake == NULL)
	{
		failedAlloc();
	}
	
	new_snake->next = NULL;
	new_snake->x = x, new_snake->y = y;

	struct snake* current_snake = *head;
	while(current_snake->next != NULL)
	{
		current_snake = current_snake->next;
	}	
	
	current_snake->next = new_snake;

	food_spawn.spawned = false; 
	++food_spawn.score;

	return food_spawn;
}

struct food drawFood(struct food food_spawn)
{
	const float radius = 10.0f;

	if(!food_spawn.spawned)
	{
		food_spawn.x = rand() % (SCREEN_WIDTH - 10) + 10;
		food_spawn.y = rand() % (SCREEN_HEIGHT - 10) + 10;
		food_spawn.spawned = true; 
	}

	DrawCircle(food_spawn.x, food_spawn.y, radius, (Color){255, 0, 0, 255}); 

	return food_spawn; 
}

struct food devourFood(struct snake* head, struct food food_spawn)
{
	const int radius = 15;

	if((head->x < food_spawn.x + radius && head->x > food_spawn.x - radius) &&
	   (head->y < food_spawn.y + radius && head->y > food_spawn.y - radius))	
	{
		return food_spawn = addSnakeParts(&head, food_spawn, head->x, head->y);
	}

	if((head->x > food_spawn.x - radius && head->x < food_spawn.x + radius) &&
	   (head->y < food_spawn.y + radius && head->y > food_spawn.y - radius))	
	{
		return food_spawn = addSnakeParts(&head, food_spawn, head->x, head->y); 
	}

	if((head->y < food_spawn.y + radius && head->y > food_spawn.y - radius) && 
	   (head->x < food_spawn.x + radius && head->x > food_spawn.x - radius))	
	{
		return food_spawn = addSnakeParts(&head, food_spawn, head->x, head->y);
	}

	if((head->y > food_spawn.y - radius && head->y < food_spawn.y + radius) &&
	   (head->x < food_spawn.x + radius && head->x > food_spawn.x - radius))	
	{
		return food_spawn = addSnakeParts(&head, food_spawn, head->x, head->y); 
	}

	return food_spawn; 
}

void drawBorders(void) 
{
	DrawRectangle(0, 0, 20, SCREEN_HEIGHT, (Color){100, 100, 100, 255});
	DrawRectangle(0, 0, SCREEN_WIDTH, 20, (Color){100, 100, 100, 255});
	DrawRectangle(SCREEN_WIDTH - 20, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){100, 100, 100, 255});
	DrawRectangle(0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){100, 100, 100, 255});
}

bool borderCollision(struct snake* head)
{
	bool isColliding = false; 
	const int leftBorder = 20, rightBorder = 440;
	const int topBorder = 20, bottonBorder = 700;

	if(head->x < leftBorder)
	{
		isColliding = true; 
	}

	if(head->x > rightBorder)
	{
		isColliding = true;
	}

	if(head->y < topBorder)
	{
		isColliding = true; 
	}

	if(head->y > bottonBorder)
	{
		isColliding = true;
	}

	return isColliding; 
}

bool bodyCollision(struct snake* head)
{
	struct snake* body = head; 
	body = body->next; 
	
	while(body->next != NULL)
	{
		body = body->next;
	}
}

void gameOver()
{
	bool gameStatus = true; 
	const char* message = "Game Over!";
	DrawText(message, 480 / 2, 720 / 2, 5, (Color){255, 255, 255 ,255});
}