/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef SNAKE_ENUMERATIONS_H
#define SNAKE_ENUMERATIONS_H

enum snakeRaylibEnums
{
    /// @brief Grid height.
    HEIGHT = 20,
    /// @brief Grid width.
    WIDTH = 20,

    /// @brief The actual width of the screen.
    SCREEN_WIDTH = 400,
    /// @brief The actual height of the screen.
    SCREEN_HEIGHT = 400,

    /// @brief Border collision
    LEFT_BORDER = 20,
    /// @brief Border collision
    RIGHT_BORDER = 360,
    /// @brief Border collision
    TOP_BORDER = 20,
    /// @brief Border collision
    BOTTOM_BORDER = 360,

    /// @brief Movement direction of food and enemy.
    LEFT_UP = 1,
    /// @brief Movement direction of food and enemy.
    RIGHT_UP = 2,
    /// @brief Movement direction of food and enemy.
    LEFT_DOWN = 3,
    /// @brief Movement direction of food and enemy.
    RIGHT_DOWN = 4,

    /// @brief The size of all text in this game.
    FONT_SIZE = 20,

    /// @brief Pause message x position.
    PAUSE_X = 130,
    /// @brief Pause message y position.
    PAUSE_Y = 150,

    /// @brief Pause message x position.
    GAME_OVER_X = 155,
    /// @brief Pause message y position.
    GAME_OVER_Y = 150,

    /// @brief Pause message x position.
    SCORE_X = 1,
    /// @brief Pause message y position.
    SCORE_Y = 1,
};

enum snakeConsoleEnums
{
    grid_width = 22,
    grid_height = 12,
    snake_spawn = 6,
    ESCAPE_KEY = 27,
};

#endif // SNAKE_ENUMERATIONS_H