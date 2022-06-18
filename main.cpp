// Author: Oscar Bergström 
// Last edited: 2022-02-24
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>

void randomPos(int*, int*);
bool writeIt(int*, int*, int*, int*, int*);
char translateSnake(int*, int*, char);

int snakeStack[100][2];
int amountStored = 0;
int currentScore; 

int main() {
	
	// Snake head position.
	int headX = 6, headY = 6;
	int scoreX = 8, scoreY = 8;
	int score = 0;
	currentScore = score; 
	bool is_running = true;

	// Key currently pressed. 
	char key_pressed = 's';

	srand(time(NULL));
	while (is_running) {
		system("cls");
		is_running = writeIt(&headX, &headY, &score, &scoreX, &scoreY);
		key_pressed = translateSnake(&headX, &headY, key_pressed);
	}

	return 0;
}

bool writeIt(int* ptr_headX, int* ptr_headY, int* ptr_score, int* ptr_scoreX, int* ptr_scoreY) {

	// Game board.
	char board[12][24];

	// Check if the snake head has passed the game border. 
	if (*ptr_headX == 0) *ptr_headX = 22;
	if (*ptr_headX == 23) *ptr_headX = 1;
	if (*ptr_headY == 0) *ptr_headY = 10;
	if (*ptr_headY == 11) *ptr_headY = 1;

	// Print all graphics.
	for (int i = 0; i < 12; i++) for (int n = 0; n < 24; n++) {
		
		// Border. 
		if (i == 0 || i == 11) board[i][n] = '#';
		if(n == 0 || n == 23) board[i][n] = '#';

		// Print the head and tail.
		if((i != 0 && i != 11) && (n != 0 && n != 23)){
			
			// Empty 
			board[i][n] = ' ';

			// Head.
			board[*ptr_headY][*ptr_headX] = 'D';

			// Tail. 
			for(int tailY = 0; tailY < *ptr_score; tailY++)
				board[snakeStack[tailY][0]][snakeStack[tailY][1]] = 'O';

			// Score
			board[*ptr_scoreY][*ptr_scoreX] = 'X';

			// Point.
			while (*ptr_score > currentScore) {
				randomPos(ptr_scoreX, ptr_scoreY);
				if (board[*ptr_scoreY][*ptr_scoreX] != 'D' && board[*ptr_scoreY][*ptr_scoreX] != 'O') {
					currentScore = *ptr_score;
				}
			}
		}
		std::cout << board[i][n];
		if (n == 23) std::cout << '\n';
	}

	std::cout << "\n" << "Score:" << *ptr_score;

	// Check if head has crossed tail.
	for (int i = 0; i < *ptr_score; i++) {
		if ((snakeStack[i][0] == *ptr_headY) && (snakeStack[i][1] == *ptr_headX)) {
			std::cout << "\n" << "game over" << std::endl;
			system("pause");
			return false;
		}
	}

	// Check if score is collected.
	if (*ptr_headY == *ptr_scoreY && *ptr_headX == *ptr_scoreX) *ptr_score += 1;


	// Snake stack rules. 
	if (amountStored < *ptr_score) {
		snakeStack[amountStored][0] = *ptr_headY;
		snakeStack[amountStored][1] = *ptr_headX;
		amountStored++;
	}
	else  amountStored = 0;

	return true;
}
char translateSnake(int* ptr_headX, int* ptr_headY, char key_pressed) {

	// New key value. 
	char new_key = key_pressed;

	// Get potential new key value. 
	if (_kbhit()) new_key = _getch();

	// Check so that the new key value don't conflict with current flow of the snake head. 
	if (new_key == 'a' && key_pressed != 'd') key_pressed = new_key;
	if (new_key == 'd' && key_pressed != 'a') key_pressed = new_key;
	if (new_key == 'w' && key_pressed != 's') key_pressed = new_key;
	if (new_key == 's' && key_pressed != 'w') key_pressed = new_key;

	// Iterate 100000000 times behover adding to the flow of the snakes movement. 
	for (int i = 0; i <= 100000000; i++) {
		if (i == 100000000) {
			if (key_pressed == 'd') *ptr_headX += 1;
			if (key_pressed == 'w') *ptr_headY -= 1;
			if (key_pressed == 'a') *ptr_headX -= 1;
			if (key_pressed == 's') *ptr_headY += 1;
		}
			
	}

	return key_pressed;
}
void randomPos(int* ptr_scoreX, int* ptr_scoreY) {
	*ptr_scoreX = rand() % 23 + 1;
	*ptr_scoreY = rand() % 10 + 1;
	return;
}
