#include "board.h"

int main() {
	int height = 20, width = 20;

	board game_board = board(height, width);
	game_board.gameLoop();

	return 0;
}


	
/*

	* m * n
	* 2 | m || 2 | n

	t = set();

	! m * n characters
	! (m * n)/2 pairs of characters

	5 * 6 = 30!

	5*6

	1 original valid board



*/