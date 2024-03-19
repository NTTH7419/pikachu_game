#include "pikachu.h"

int main() {
	int height = 5, width = 10;
	char** game_board = createGameBoard(height, width);
	// printGameBoard(game_board, height, width);
	string* display_board = createDisplayBoard(game_board, height, width);

	gameLoop(game_board, display_board, height, width);
	
	deleteGameBoard(game_board, height, width);
	delete[] display_board;

	return 0;
}