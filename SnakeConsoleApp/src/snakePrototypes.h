/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

#ifndef SNAKEPROTOTYPES_H
#define SNAKEPROTOTYPES_H
#include "snakeStructures.h"
#include "snakeEnums.h"

/** 
 *	Sets the terminal into raw mode. This is needed to be able to read a single key hit and prevent echo of characters.
 */
int rawSetup(void);

/** 
 *	Reset to the terminal to cooked mode. This is necessary as to prevent any issues on exit
 */
void rawDisable(void);

/** 
 *	Initiates the start location of the snake.
 */
snake *snakeSetup(void);

/** 
 *	Initiates the start location of good food.
 */
food foodSetUp(void);

/** 
 *	Initiates the all values in the array used to visualize the game.
 */
void boardSetup(snake *, food, char[GRID_HEIGHT][GRID_WIDTH]);

/** 
 *	Will excute the game loop, this loop will run until the end of the game. 
 *	This functions controls and calls most of the other logic in this game.
 */
void runGame(snake *, food, char[GRID_HEIGHT][GRID_WIDTH]);

/** 
 *	Determines how fast the game is rendered and the input is read.
 */
void refreshRate(void);

/**
 * Reads a keystroke and resturns it ascii value.
 */
int _kbhit(void);

/**
 * 	Translates the read byte into keyboardstroke.
 * 	Current movement direction is set to any legitimate direction change made.
 *  Without this function the snake will only move one step when executing the move function.
 */
int translateByte(char, char);

/**
 *	Renders the game board.
 */
void renderBoard(char[GRID_HEIGHT][GRID_WIDTH], int score);

/**
 *	Move the snake across the grid.
 *  This is done by translating the user keyboard input to direction.
 */
void moveSnake(snake *, char, char[GRID_HEIGHT][GRID_WIDTH]);

/**
 * 	Check if the snake has devoured the current food.
 * 	Set food spawn flag to false, indicating that new food can be spawned.
 */
food devourFood(food, snake *);

/**
 *	Add a new node to a linked list, this is done in order to grow the snake.
 *  This is what actually make the snake grow in size.
 */
void addSnakeParts(snake **, bool);

/**
 *	Spawns new food once devoured.
 *  Devoured food makes the snake grow and increment the total score.
 */
food spawnFood(food, char[GRID_HEIGHT][GRID_WIDTH], snake *);

/**
 * 	Controls if the snake has colided with itself.
 * 	Use to make sure player does not cross the snake body.
 */
bool snakecollision(snake *);

/**
 * 	Controls if the snake has colided with the wall at the edges of the screen.
 * 	Prevents the player from traversing out of bounds.
 */
bool borderCollision(snake *);

#endif // SNAKEPROTOTYPES_H