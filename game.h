#pragma once

#include "menu.h"
#include "board.h"

struct game {
	board *game_board;
	int board_height;
	int board_width;

	int score;
	string name;

	game(int difficulty) {
		if (difficulty == 1) {
			board_height = 6;
			board_width = 8;
			game_board = new board(board_height, board_width);
		}
		else if (difficulty == 2) {
			board_height = 8;
			board_width = 10;
			game_board = new board(board_height, board_width);
		}
		else if (difficulty == 3) {
			board_height = 8;
			board_width = 12;
			game_board = new board(board_height, board_width);
		}
	}

	~game() {
		delete game_board;
	}
	void initGame();
	void gameLoop();
	void gameFinished();


	void displayGameInfo();
	void moveCursor(Coordinate &cur, Input inp);
	bool matchCell(Coordinate cur1, Coordinate cur2);
	void showHint();
	void updateScore(int bonus_score);
	void shuffle(board* game_board);
};