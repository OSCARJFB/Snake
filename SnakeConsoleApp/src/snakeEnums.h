/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef SNAKEENUMS_H
#define SNAKEENUMS_H

enum snakeConsoleEnums
{
    /// @brief Width of the game board in x-axis.
    grid_width = 22,

    /// @brief width of the game board in y-axis.

    grid_height = 12,
    /// @brief Spawn x.

    snake_spawn_x = 11,
    /// @brief Spawn y.

    snake_spawn_y = 6,
    
    /// @brief Escape key.
    ESCAPE_KEY = 27,

    /// @brief A second in nanoseconds. 
    SECOND = 1000000000,
};

#endif // SNAKEENUMS_H