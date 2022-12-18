/*
	Writen by: Oscar Bergström
*/

/// @brief This linked list keeps track of the snakes body parts.
/// @brief All nodes get a value dependent on how the head traverses the screen. 
struct snake
{
	int x, y;
	struct snake* next;
};

/// @brief This linked list keeps track of the snakes body parts.
/// @brief All nodes get a value dependent on how the head traverses the screen. 
typedef struct snake* snake; 

/// @brief This structure holds the coordinates of food,
/// @brief how much food that has been devoured(score)
/// @brief and also if food is spawned or not. 
struct food
{
	int x, y, direction; 
	int score;
	bool spawned;
};

/// @brief This structure holds the coordinates of food,
/// @brief how much food that has been devoured(score)
/// @brief and also if food is spawned or not.  
typedef struct food food; 