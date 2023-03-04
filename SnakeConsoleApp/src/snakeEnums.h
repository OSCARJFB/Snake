/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef SNAKEENUMS_H
#define SNAKEENUMS_H

enum boardSize
{
    // Width of the game board in x-axis.
    GRID_WIDTH = 22,
    // Width of the game board in y-axis.
    GRID_HEIGHT = 12,
};

enum snakeSpawn
{
    // Spawn x.
    SNAKE_SPAWN_X = 11,
    // Spawn y.
    SNAKE_SPAWN_Y = 6,
};

enum successOrFail
{
    // On success. 
    SUCCESS = 1,
    // On success.
    FAIL = -1,
};

#endif // SNAKEENUMS_H