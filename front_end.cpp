#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h> 

using namespace std;

struct Coordinate{
    int x;
    int y;

    bool operator==(const Coordinate &a) const{
        return (x == a.x && y == a.y);
    }

    bool operator!=(const Coordinate &a) const{
        return !(x == a.x && y == a.y);
    }

    Coordinate& operator=(const Coordinate &a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }

    Coordinate operator+(const Coordinate &a) const{
        Coordinate result;
        result.x = x + a.x;
        result.y = y + a.y;

        return result;
    }
};

bool isInGameBoard(int height, int width, Coordinate pos) {
	if (pos.x <= 0 || pos.y <= 0 || pos.y >= height + 1 || pos.x >= width + 1) return 0;
	return 1;
}


char** createGameBoard(int height, int width) {
	srand(time(0) + rand());
	char** game_board = new char*[height + 2];
	for (int i = 0; i < height + 2; i++) {
		game_board[i] = new char[width + 2];
		for (int j = 0; j < width + 2; j++) {
			if (i * j == 0 || i == height + 1 || j == width + 1) game_board[i][j] = 0;
			else game_board[i][j] = 65 + rand() % 5;
		}
	}
	return game_board;
}

void printGameBoard(char** game_board, int height, int width) {
	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			cout << game_board[i][j] << ' ';
		}
		cout << endl;
	}
}

void deleteGameBoard(char** &game_board, int height, int width) {
	for (int i = 0; i < height + 2; i++) {
		delete[] game_board[i];
	}
	delete[] game_board;
}

int getInput() {
	int c = getch();
	if (c == 27) return -1; 	// ESC
	if (c == 13) return 0; 		// ENTER
	if (c == 'W' || c == 'w') return 1;
	if (c == 'A' || c == 'a') return 2;
	if (c == 'S' || c == 's') return 3;
	if (c == 'D' || c == 'd') return 4;
	return -2;
}

void moveCursor(Coordinate &cur, int inp, int height, int width) {
	Coordinate prev = cur;
	switch (inp) {
		case 1:
			cur.y -= 1;
			break;

		case 2:
			cur.x -= 1;
			break;
		
		case 3:
			cur.y += 1;
			break;
		
		case 4:
			cur.x += 1;
			break;
		
		default:
			break;
	}
	if (!isInGameBoard(height, width, cur)) cur = prev;
}

void highlightPos(string* display_board, int height, int width, Coordinate pos) {
	if (!isInGameBoard(height, width, pos)) return;
	display_board[4 * pos.y + 1][10 * pos.x + 1] = '#';
	display_board[4 * pos.y + 2][10 * pos.x + 1] = '#';
	display_board[4 * pos.y + 3][10 * pos.x + 1] = '#';
}

void dehighlightPos(string* display_board, int height, int width, Coordinate pos) {
	if (!isInGameBoard(height, width, pos)) return;
	display_board[4 * pos.y + 1][10 * pos.x + 1] = ' ';
	display_board[4 * pos.y + 2][10 * pos.x + 1] = ' ';
	display_board[4 * pos.y + 3][10 * pos.x + 1] = ' ';
}

string* createDisplayBoard(char** game_board, int height, int width) {
	string *display_board = new string[(height + 2) * 4 + 1] {};
	int line = 0;

	// top outline
	string blank_line = string((width + 2) * 10 + 1, ' ');
	for (int i = 0; i < 4; i++) {
		display_board[line++] = blank_line;
	}

	string row_sep = string(10, ' ') + string(width * 10 + 1, '-') + string(10, ' ');	// row separator
	display_board[line++] = row_sep;	// line 0

	// create spliter line
	string spliter_line;
	spliter_line = string(10, ' ') + '|';
	for (int i = 1; i < width + 1; i++) {
		spliter_line += string(9, ' ') + '|';
	}
	spliter_line += string(10, ' ');

	for (int i = 1; i < height + 1; i++) {
		display_board[line++] = spliter_line;	// line 4i + 1

		display_board[line] = spliter_line;		// line 4i + 2
		for (int j = 1; j < width + 1; j++) {
			display_board[line].replace(10 * j + 5, 1, 1, game_board[i][j]);	// substitute the character in
		}
		line++;

		display_board[line++] = spliter_line;	// line 4i + 3
		display_board[line++] = row_sep;		// line 4i + 4
	}

	// bottom outline
	for (int i = 0; i < 4; i++) {
		display_board[line++] = blank_line;
	}

	return display_board;
}

bool deleteBoardAtPos(char** game_board, string* display_board, int height, int width, Coordinate pos) {
	if (!isInGameBoard(height, width, pos)) return 0;


	game_board[pos.y][pos.x] = 0;
	display_board[4*pos.y + 2].replace(10 * pos.x + 5, 1, 1, ' ');	// remove character

	bool left, right, top, bottom, top_left, top_right, bottom_left, bottom_right; // to check if exist/ empty
	left = !game_board[pos.y][pos.x - 1];
	right = !game_board[pos.y][pos.x + 1];
	top = !game_board[pos.y - 1][pos.x];
	bottom = !game_board[pos.y + 1][pos.x];
	top_left = !game_board[pos.y - 1][pos.x - 1];
	top_right = !game_board[pos.y - 1][pos.x + 1];
	bottom_left = !game_board[pos.y + 1][pos.x - 1];
	bottom_right = !game_board[pos.y + 1][pos.x + 1];

	if (left) {		// check left side
		display_board[4 * pos.y + 1].replace(10 * pos.x, 1, 1, ' ');
		display_board[4 * pos.y + 2].replace(10 * pos.x, 1, 1, ' ');
		display_board[4 * pos.y + 3].replace(10 * pos.x, 1, 1, ' ');
	}

	if (right) {	// check right side
		display_board[4 * pos.y + 1].replace(10 * pos.x + 10, 1, 1, ' ');
		display_board[4 * pos.y + 2].replace(10 * pos.x + 10, 1, 1, ' ');
		display_board[4 * pos.y + 3].replace(10 * pos.x + 10, 1, 1, ' ');
	}

	if (top) display_board[4 * pos.y].replace(10 * pos.x + 1, 9, 9, ' '); 			// check above
	if (bottom) display_board[4 * pos.y + 4].replace(10 * pos.x + 1, 9, 9, ' ');		// check below
	if (top_left && left && top) display_board[4 * pos.y].replace(10 * pos.x, 1, 1, ' ');			// check left top
	if (top_right && right && top) display_board[4 * pos.y].replace(10 * pos.x + 10, 1, 1, ' ');	//check right top
	if (bottom_left && left && bottom) display_board[4 * pos.y + 4].replace(10 * pos.x, 1, 1, ' ');	// check left bottom
	if (bottom_right && right && bottom) display_board[4 * pos.y + 4].replace(10 * pos.x + 10, 1, 1, ' ');	//check right bottom

	return 1;
}

void printDisplayBoard(string* display_board, int height) {
	system("cls");

	HANDLE console_color; 
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

	string line;
	int idx = 0;
	for(int i = 0; i < 4 * (height + 2); i++) {
		line = display_board[i];
		if (i % 4 == 0) cout << line;
		else {
			idx = line.find('#');
			if (idx != line.npos) {
				while (idx != line.npos) {
					SetConsoleTextAttribute(console_color, 15);
					cout << line.substr(0, idx);
					line.erase(0, idx);
					line[0] = ' ';
					SetConsoleTextAttribute(console_color, 240);
					cout << line.substr(0, 9);
					line.erase(0, 9);
					SetConsoleTextAttribute(console_color, 15);
					idx = line.find('#');
				}
				cout << line;
			}
			else cout << line;
		}
		cout << endl;
	}
}

void gameLoop(char** game_board, string* display_board, int height, int width) {
	int n = height * width;
	Coordinate cur1, cur2;
	int inp;
	cur1 = {1, 1};
	highlightPos(display_board, height, width, cur1);
	printDisplayBoard(display_board, height);
	while (n > 0) {
		do {
			inp = getInput();
		} while (inp == -2);

		while (inp > 0) {
			dehighlightPos(display_board, height, width, cur1);
			moveCursor(cur1, inp, height, width);
			highlightPos(display_board, height, width, cur1);
			printDisplayBoard(display_board, height);
			do {
				inp = getInput();
			} while (inp == -2);
		}

		if (inp == -1) break;

		cur2 = cur1;

		do {
			inp = getInput();
		} while (inp == -2);

		while (inp > 0) {
			if (cur2 != cur1) dehighlightPos(display_board, height, width, cur2);
			moveCursor(cur2, inp, height, width);
			highlightPos(display_board, height, width, cur2);
			printDisplayBoard(display_board, height);
			do {
				inp = getInput();
			} while (inp == -2);
		}

		if (inp == -1) break;

		if (game_board[cur1.y][cur1.x] == game_board[cur2.y][cur2.x] && cur1 != cur2 && true) {
			deleteBoardAtPos(game_board, display_board, height, width, cur1);
			dehighlightPos(display_board, height, width, cur1);
			deleteBoardAtPos(game_board, display_board, height, width, cur2);
			n -= 2;
			cur1 = cur2;
			printDisplayBoard(display_board, height);
		}
		else {
			if (cur2 != cur1) dehighlightPos(display_board, height, width, cur1);
			cur1 = cur2;
			printDisplayBoard(display_board, height);
		}
	}
}

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