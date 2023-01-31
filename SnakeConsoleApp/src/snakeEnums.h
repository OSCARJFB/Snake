/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef SNAKEENUMS_H
#define SNAKEENUMS_H

enum boardSize
{
    /// @brief Width of the game board in x-axis.
    GRID_WIDTH = 22,
    /// @brief width of the game board in y-axis.
    GRID_HEIGHT = 12,
};

enum snakeSpawn
{
    /// @brief Spawn x.
    SNAKE_SPAWN_X = 11,
    /// @brief Spawn y.
    SNAKE_SPAWN_Y = 6,
};

enum successOrFail
{
    /// @brief On success.
    SUCCESS = 1,
    /// @brief On success.
    FAIL = -1,
};

#endif // SNAKEENUMS_H