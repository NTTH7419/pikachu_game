#pragma once

// #include "menu.h"
#include "board.h"
#include <iomanip>


//defining the time struct to count time elapsed
struct Time {
	int min, sec;

	void convert(int second) {
		min = second / 60;
		sec = second % 60;
	}

	void displayTime() {
		cout << setfill('0') << setw(2) << min << ':' << setfill('0') << setw(2) << sec;
	}

	bool operator<(Time &t) {
		return (((this->min) * 60 + this->sec) < (((t.min) * 60 + t.sec)));
	}
};


//defining the struct game to manage all the game objects
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

	//TODO: initializing a new game
	void initGame();

	//TODO: the main game loop
	bool gameLoop();		// return 1 if player finished, 0 if player escape

	//TODO: moving to the aftermath after completing a game
	void gameFinished(bool isFinished);

	//TODO: display the game stats
	void displayGameInfo();

	//TODO: move the cursor displayed on screen
	void moveCursor(Coordinate &cur, Input inp);

	//TODO: match two cells at position cur1 and cur2
	bool matchCell(Coordinate cur1, Coordinate cur2);

	//TODO: highlight the two cells available for matching
	void showHint();

	//TODO: change the displayed number of hints left on screen
	void updateRemainHint();

	//TODO: update the score displayed on screen
	void updateScore(int bonus_score);

	//TODO: taking the name of the player
	void inputName(int x, int y);
};


//define a record struct to save the information of the leaderboard
struct Result {
	string name;
	int score;
	Time play_time;

	bool operator>(Result &r) {		// better score, if equal: better play time
		return ((score > r.score) || ((score == r.score) && (play_time < r.play_time)));
	}

	string convertToCSV() {
		return (name + "," + to_string(score) + "," + to_string(play_time.min) + ":" + to_string(play_time.sec));
	};
};

//define the Highscores struct to store the highest results
struct Highscores {
	static vector<Result> records; 	//list of top highscorer

	//TODO: load the highscores from the file
	static void loadHighscores();

	//TODO: update the highscores according to the record
	static void updateHighscores(Result record);

	//TODO: dispaly the highscores on the board
	static void displayHighscores();
};

