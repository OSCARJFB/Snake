#ifndef SNAKE_STRUCTURE_H
#define SNAKE_STRUCTURE_H

/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

/// @brief This linked list keeps track of the snake/snakes body parts.
/// @brief All nodes get a value dependent on how the head traverses the screen/gameboard.
typedef struct snake
{
	int x, y;
	struct snake *next;
}snake;

/// @brief This structure holds the coordinates of the in game food spawn,
/// @brief how much food that has been devoured(score) and also if the food is spawned or not.
typedef struct food
{
	int x, y, direction;
	int score;
	bool spawned;
}food;

#endif // SNAKE_STRUCTURE_H