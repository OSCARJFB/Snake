/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef SNAKEENUMS_H
#define SNAKEENUMS_H

enum gridSize
{
    // Grid height.
    HEIGHT = 20,
    // Grid width.
    WIDTH = 20,
};

enum screenSize
{
    // The actual width of the screen.
    SCREEN_WIDTH = 400,
    // The actual height of the screen.
    SCREEN_HEIGHT = 400,
};

enum borderLocation
{
    // Border collision
    LEFT_BORDER = 20,
    // Border collision
    RIGHT_BORDER = 360,
    // Border collision
    TOP_BORDER = 20,
    // Border collision
    BOTTOM_BORDER = 360,
};

enum textProperties
{
    // The size of all text in this game.
    FONT_SIZE = 20,

    // Pause message x position.
    PAUSE_X = 130,
    // Pause message y position.
    PAUSE_Y = 150,

    // Pause message x position.
    GAME_OVER_X = 155,
    // Pause message y position.
    GAME_OVER_Y = 150,

    // Pause message x position.
    SCORE_X = 1,
    // Pause message y position.
    SCORE_Y = 1,
};

#endif // SNAKEENUMS_H