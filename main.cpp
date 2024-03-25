#include "board.h"

int main() {
	int height = 5, width = 5;

	board game_board = board(height, width);
	game_board.gameLoop();

	return 0;
}
