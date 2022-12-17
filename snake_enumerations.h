enum game_props
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

    /// @brief Movement direction of food and enemy. 
    LEFT_UP = 1,
    /// @brief Movement direction of food and enemy. 
    RIGHT_UP = 2, 
    /// @brief Movement direction of food and enemy. 
    LEFT_DOWN = 3,
    /// @brief Movement direction of food and enemy. 
    RIGHT_DOWN = 4, 

    /// @brief Array size of all food.  
    ALL_FOOD = 1
};
