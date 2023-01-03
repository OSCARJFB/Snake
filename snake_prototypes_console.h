/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB
*/

#ifndef SNAKE_PROTOTYPES_CONSOLE_H
#define SNAKE_PROTOTYPES_CONSOLE_H
#include "snake_structures.h"
#include "snake_enumerations.h"

int rawSetup();
void rawDisable();
snake snakeSetup(void);
food foodSetUp(void);
void boardSetup(snake, food, char[grid_height][grid_width]);
void runGame(snake, food, char[grid_height][grid_width]);
void refreshRate(void);
int _kbhit(void);
int translateByte(char, char);
void renderBoard(char[grid_height][grid_width], int score);
void moveSnake(snake, char, char[grid_height][grid_width]);
food devourFood(food, snake);
void addSnakeParts(snake*, bool);
food spawnFood(food, char[grid_height][grid_width]);
bool snakecollision(snake); 
bool borderCollision(snake); 


#endif // SNAKE_PROTOTYPES_CONSOLE_H