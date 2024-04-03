#pragma once

// #include "menu.h"
#include "board.h"
#include <iomanip>

struct Time {
	int min, sec;

	void convert(int second) {
		min = second / 60;
		sec = second % 60;
	}

	void displayTime() {
		cout << setfill('0') << setw(2) << min << ':' << setfill('0') << setw(2) << sec;
	}
};

struct Game {
	Board *game_board;
	int board_height;
	int board_width;
	
	int score = 0;
	Time play_time;
	string name;

	bool hint_used = false;
	bool shuffled = false;
	int hint_remaining = 3;

	Game(int difficulty) {
		game_board = new Board(difficulty);
		board_height = game_board->height;
		board_width = game_board->width;
	}

	~Game() {
		delete game_board;
	}
	void initGame();
	void gameLoop();
	void gameFinished();

	void displayGameInfo();
	void moveCursor(Coordinate &cur, Input inp);
	bool matchCell(Coordinate cur1, Coordinate cur2);
	void showHint();
	void updateRemainHint();
	void updateScore(int bonus_score);
	void shuffleBoard();
	void inputName(int x, int y);
};