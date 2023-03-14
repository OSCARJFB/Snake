/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

#ifndef SNAKESTRUCTURE_H
#define SNAKESTRUCTURE_H

// This struct/linked list keeps track of the snake/snakes body parts.
typedef struct snake
{
	int x, y;
	struct snake *next;
} snake;

// This structure holds the coordinates of food spawns, how much food that has been devoured(score).
typedef struct food
{
	int x, y, direction;
	int score;
	bool spawned;
} food;

#endif // SNAKESTRUCTURE_H