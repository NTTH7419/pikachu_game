#include "board.h"

int main() {
	cout << "\33[?25l";	// hide console cursor
	int height = 5, width = 8;

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