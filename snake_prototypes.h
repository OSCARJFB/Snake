/// @brief Initiate game settings. Create a window, set size the size of that window, 
/// @brief target fps and do seed for random value generation.
/// @param void
void gameSetup(void);

/// @brief Initiate start location of the snake. 
/// @param void
/// @return the allocated head of a linked list.
struct snake* snakeSetup(void);

/// @brief Initiate start location of good food. 
/// @param void
/// @return A structure. 
struct food foodSetup(void);

/// @brief Excute the game loop and run until end of the game. 
/// @brief This functions calls most of the other logic in this game. 
/// @param struct*
/// @param struct 
void runGame(struct snake*, struct food);

/// @brief Move the snake according to the direction provided by the integer parameter.
/// @param struct*
/// @param int 
void moveSnake(struct snake*, int);

/// @brief Iterates a linked list and draw each node unto the screen, this will write the snake. 
/// @param struct*
void drawSnake(struct snake*);

/// @brief Draw food that may be devoured by the snake. 
/// @param struct
/// @return A struct built of the parameter either modified or unmodified.
struct food drawFood(struct food); 

/// @brief Draw a border covering the edges of the screen view. 
/// @param void 
void drawBorders(void);

/// @brief Draw a grid covering the background of the screen.
/// @param void 
void drawGrid(void);

/// @brief Draw current score to the screen.
/// @param int 
void drawScore(int);

/// @brief Get user input from the keyboard which can used to steer the movement direction of the snake. 
/// @param int
/// @param bool
/// @return A integer representing the keystroke in ASCII value. 
int snakeDirection(int, bool); 

/// @brief Check if the snake has devoured the food.
/// @param struct*
/// @param struct
/// @return A struct used for food logic. 
struct food devourFood(struct snake*, struct food); 

/// @brief Add a new node to the linked list, this will be done to grow the snake. 
/// @param struct**
/// @param struct
/// @return A struct used for food logic. 
struct food addSnakeParts(struct snake**, struct food);

/// @brief Check if the snake has colided with the wall at the edges of the screen. 
/// @param struct* 
/// @return A bool depending on if collision was detected(true) or not(false). 
bool borderCollision(struct snake*); 

/// @brief Check if the snake has colided with itself.
/// @param struct* 
/// @return A bool depending on if collision was detected(true) or not(false). 
bool bodyCollision(struct snake*);

/// @brief Run if game over.
/// @param void 
/// @return A bool set to true.
bool gameOver(void); 

/// @brief Look for a keystroke = p.
/// @param bool
/// @return A bool set to true or false depending on status of the bool parameter.
bool pauseGame(bool pause); 
