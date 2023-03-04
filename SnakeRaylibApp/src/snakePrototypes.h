/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

#ifndef SNAKEPROTOTYPES_H
#define SNAKEPROTOTYPES_H
#include "snakeStructures.h"

/**
 * 	Initiate the game settings. Create a window, set the size of that window, 
 *  the target fps and do seed for random value generation.
 */
void gameSetup(void);

/**
 * 	Initiates the starting location of the snake.
 */
snake *snakeSetup(void);

/**
 * 	Initiates the starting location of good food.
 */
food foodSetup(void);

/**
 * 	Will excute the game loop, this loop will run until the end of the game. 
 *  This functions controls and calls most of the other logic in this game.
 */
void runGame(struct snake *, struct food);

/**
 * 	Gets user input from the keyboard which can used to steer the movement direction of the snake.
 */
int snakeDirection(int, bool);

/**
 * 	Move the snake according to the direction calculated provided by an integer parameter.
 */
void moveSnake(struct snake *, int);

/**
 * 	Iterates a linked list and draw each node unto the screen.
 *  This will write the snake onto the game.
 */
void drawSnake(struct snake *);

/**
 * 	Draw food that may be devoured by the snake.
 */
struct food drawFood(struct food);

/**
 * 	Check if the snake has devoured the current food.
 */
struct food devourFood(struct snake *, struct food);

/**
 *	Add a new node to a linked list, this is done in order to grow the snake.
 *  This is what actually make the snake grow in size.
 */
struct food addSnakeParts(struct snake **, struct food);

/**
 * 	Draw a grid that covers the background of the screen.
 */
void drawGrid(void);

/**
 * 	Draw a border that covers the edges of the screen view.
 */
void drawBorders(void);

/**
 *	Draws the current score to the screen.
 */
void drawScore(int);

/**
 * 	Controls if the snake has colided with the wall at the edges of the screen.
 * 	Prevents the player from traversing out of bounds.
 */
bool borderCollision(snake *);

/**
 * 	Controls if the snake has colided with itself.
 * 	Use to make sure player does not cross the snake body.
 */
bool bodyCollision(snake *);

/**
 *	Run if game over is triggered.
 */
bool gameOver(void);

/**
 *	Looks for a keystroke which equals p (for pause).
 */
bool pauseGame(bool pause);

#endif // SNAKEPROTOTYPES_H