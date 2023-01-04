/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

#ifndef SNAKE_PROTOTYPES_CONSOLE_H
#define SNAKE_PROTOTYPES_CONSOLE_H
#include "snake_structures.h"
#include "snake_enumerations.h"

/// @brief Sets the terminal into raw mode. This is needed to be able to read a single key hit without and echo. 
/// @return a integer depending on success or failure. 
int rawSetup();

/// @brief  Reset to the terminal to cooked mode. This is necessary as to prevent any issues on exit. 
void rawDisable();

/// @brief Initiates the start location of the snake.
/// @param void
/// @return the allocated head of a linked list.
snake snakeSetup(void);

/// @brief Initiates the start location of good food.
/// @param void
/// @return A structure.
food foodSetUp(void);

/// @brief Initiates the all values in the array used to visualize the game.  
/// @param struct*
/// @param struct
/// @param char[][]
void boardSetup(snake, food, char[grid_height][grid_width]);

/// @brief Will excute a game loop, it will run until end of the game. This functions calls most of the other logic in this game.
/// @param struct*
/// @param struct
void runGame(snake, food, char[grid_height][grid_width]);

/// @brief Works like set fps, determines how fast the game is rendered and input read. 
void refreshRate(void);

/// @brief Reads a byte representation of a key being hit or pressed.
/// @return returns a integer dec value.  
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
void moveSnake(snake, char, char[grid_height][grid_width]);

/// @brief Check if the snake has devoured the food.
/// @param struct*
/// @param struct
/// @return A struct used by the food logic.
food devourFood(food, snake);

/// @brief Add a new node to the linked list, this is done in order to grow the snake.
/// @param struct**
/// @param struct
void addSnakeParts(snake*, bool);

/// @brief Spawns need food once devoured. 
/// @param struct 
/// @param char[][]
food spawnFood(food, char[grid_height][grid_width]);

/// @brief A check to make sure the snake does not collide with itself. 
/// @param struct 
/// @return A bool depending on collision status. 
bool snakecollision(snake); 

/// @brief A check to make sure the snake does not collide with the boarders. 
/// @param struct 
/// @return A bool depending on collision status. 
bool borderCollision(snake); 

#endif // SNAKE_PROTOTYPES_CONSOLE_H