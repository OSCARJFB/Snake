/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

#ifndef SNAKEPROTOTYPES_H
#define SNAKEPROTOTYPES_H
#include "snakeStructures.h"
#include "snakeEnums.h"

/// @brief Sets the terminal into raw mode. This is needed to be able to read a single key hit and prevent echo of characters.
/// @return a integer depending on success or failure.
int rawSetup(void);

/// @brief  Reset to the terminal to cooked mode. This is necessary as to prevent any issues on exit.
void rawDisable(void);

/// @brief Initiates the start location of the snake.
/// @return the allocated head of a linked list.
snake *snakeSetup(void);

/// @brief Initiates the start location of good food.
/// @return A structure containing the data about food.
food foodSetUp(void);

/// @brief Initiates the all values in the array used to visualize the game.
/// @param struct*
/// @param struct
/// @param char[][]
void boardSetup(snake *, food, char[grid_height][grid_width]);

/// @brief Will excute the game loop, this loop will run until the end of the game. This functions controls and calls most of the other logic in this game.
/// @param struct*
/// @param struct
void runGame(snake *, food, char[grid_height][grid_width]);

/// @brief Determines how fast the game is rendered and the input is read.
void refreshRate(void);

/// @brief Reads a byte representation of a key being hit or pressed.
/// @return returns a integer value.
int _kbhit(void);

/// @brief Translate the byte and set movement pattern of the snake.
/// @param char
/// @param char
/// @return a integer representing the set direction.
int translateByte(char, char);

/// @brief Render the game board.
/// @param char[][]
/// @param int
void renderBoard(char[grid_height][grid_width], int score);

/// @brief Move the snake.
/// @param struct*
/// @param char
/// @param char[][]
void moveSnake(snake *, char, char[grid_height][grid_width]);

/// @brief Check if the snake has devoured any food.
/// @param struct
/// @param struct*
/// @return A struct used by the food logic.
food devourFood(food, snake *);

/// @brief Add a new node to the linked list, this is done in order to grow the snake.
/// @param struct**
/// @param struct
void addSnakeParts(snake **, bool);

/// @brief Spawns new food once devoured.
/// @param struct
/// @param char[][]
/// @param struct* 
food spawnFood(food, char[grid_height][grid_width], snake *);

/// @brief If new food is about to spawn atop of the snake, give it a new position.
/// @param int* 
/// @param int*
/// @param struct*
void preventOverlapping(int *x, int *y, snake **head);

/// @brief Controls if the snake has colided with itself.
/// @param struct
/// @return A bool depending on collision status.
bool snakecollision(snake *);

/// @brief Controls if the snake has colided with the wall at the edges of the screen.
/// @param struct
/// @return A bool depending on collision status.
bool borderCollision(snake *);

#endif // SNAKEPROTOTYPES_H