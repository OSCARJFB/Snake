#ifndef SNAKE_STRUCTURE_H
#define SNAKE_STRUCTURE_H

/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

/// @brief This linked list keeps track of the snakes body parts.
/// @brief All nodes get a value dependent on how the head traverses the screen.
struct snake
{
	int x, y;
	struct snake *next;
};

/// @brief This linked list keeps track of the snakes body parts.
/// @brief All nodes get a value dependent on how the head traverses the screen.
typedef struct snake *snake;

/// @brief This structure holds the coordinates of the in game food spawn,
/// @brief how much food that has been devoured(score)
/// @brief and also if the food is spawned or not.
struct food
{
	int x, y, direction;
	int score;
	bool spawned;
};

/// @brief This structure holds the coordinates of food, how much food that has been devoured(score) and also if food is spawned or not.
typedef struct food food;

#endif // SNAKE_STRUCTURE_H