/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef SNAKEENUMS_H
#define SNAKEENUMS_H

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

#endif // SNAKEENUMS_H