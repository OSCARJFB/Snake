/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

#ifndef SNAKESTRUCTURE_H
#define SNAKESTRUCTURE_H

/**
 * 	This struct/linked list keeps track of the snake/snakes body parts.
 *	All nodes get a value dependent on how the head traverses the screen/gameboard.
 */
typedef struct snake
{
	int x, y;
	struct snake *next;
} snake;

/**
 * 	This structure holds the coordinates of the in game food spawn,
 *	how much food that has been devoured(score) and also if the food is spawned or not.
 */
typedef struct food
{
	int x, y, direction;
	int score;
	bool spawned;
} food;

#endif // SNAKESTRUCTURE_H