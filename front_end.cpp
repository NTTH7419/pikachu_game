#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h> 

using namespace std;

struct Coordinate {
	int x, y;
};

bool isLegitPos(int height, int width, Coordinate pos) {
	if (pos.x <= 0 || pos.y <= 0 || pos.x >= width - 1 || pos.y >= height - 1) return 0;
	return 1;
}


void createGameBoard(char** &game_board, int height, int width) {
	srand(time(0) + rand());
	game_board = new char*[height];
	for (int i = 0; i < height; i++) {
		game_board[i] = new char[width];
		for (int j = 0; j < width; j++) {
			if (i * j == 0 || i == height - 1 || j == width - 1) game_board[i][j] = 0;
			else game_board[i][j] = 65 + rand() % 5;
		}
	}
}

void printGameBoard(char** game_board, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << game_board[i][j] << ' ';
		}
		cout << endl;
	}
}

void deleteGameBoard(char** &game_board, int height, int width) {
	for (int i = 0; i < height; i++) {
		delete[] game_board[i];
	}
	delete[] game_board;
}

int getInput() {
	int c = getch();
	if (c == 27) return -1; 	// ESC
	if (c == 13) return 0; 		// ENTER
	if (c == 'W' or c == 'w') return 1;
	if (c == 'A' or c == 'a') return 2;
	if (c == 'S' or c == 's') return 3;
	if (c == 'D' or c == 'd') return 4;
	else return -2;
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
	if (!isLegitPos(height, width, cur)) cur = prev;
}

void highlightPos(string* display_board, int height, int width, Coordinate pos) {
	if (!isLegitPos(height, width, pos)) return;
	display_board[4 * pos.y + 1][10 * pos.x + 1] = '#';
	display_board[4 * pos.y + 2][10 * pos.x + 1] = '#';
	display_board[4 * pos.y + 3][10 * pos.x + 1] = '#';
}

void dehighlightPos(string* display_board, int height, int width, Coordinate pos) {
	if (!isLegitPos(height, width, pos)) return;
	display_board[4 * pos.y + 1][10 * pos.x + 1] = ' ';
	display_board[4 * pos.y + 2][10 * pos.x + 1] = ' ';
	display_board[4 * pos.y + 3][10 * pos.x + 1] = ' ';
}

string* createDisplayBoard(char** game_board, int height, int width) {
	string *display_board = new string[height * 4 + 1] {};
	int line = 0;

	// top outline
	string blank_line = string(width * 10 + 1, ' ');
	for (int i = 0; i < 4; i++) {
		display_board[line++] = blank_line;
	}

	string row_sep = string(10, ' ') + string((width - 2) * 10 + 1, '-') + string(10, ' ');	// row separator
	display_board[line++] = row_sep;	// line 0

	// create similar line
	string similar_line;
	similar_line = string(10, ' ') + '|';
	for (int i = 1; i < width - 1; i++) {
		similar_line += string(9, ' ') + '|';
	}
	similar_line += string(10, ' ');

	for (int i = 1; i < height - 1; i++) {
		display_board[line++] = similar_line;	// line 4i + 1

		display_board[line] = similar_line;		// line 4i + 2
		for (int j = 1; j < width - 1; j++) {
			display_board[line].replace(10 * j + 5, 1, 1, game_board[i][j]);	// substitute the character in
		}
		line++;

		display_board[line++] = similar_line;	// line 4i + 3
		display_board[line++] = row_sep;		// line 4i + 4
	}

	// bottom outline
	for (int i = 0; i < 4; i++) {
		display_board[line++] = blank_line;
	}

	return display_board;
}

bool deleteBoardAtPos(char** game_board, string* display_board, int height, int width, Coordinate pos) {
	if (!isLegitPos(height, width, pos)) return 0;


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
	for(int i = 0; i < 4 * height; i++) {
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


int main() {
	int height = 7, width = 15;
	char** game_board;
	createGameBoard(game_board, height, width);
	// printGameBoard(game_board, height, width);
	string* display_board = createDisplayBoard(game_board, height, width);
	printDisplayBoard(display_board, height);

	// Coordinate cur
	// for (int i = 0; i < (height - 2) * (width - 2); i++) {
	// 	cin >> cur.x >> cur.y;
	// 	if (x == -1 || y == -1) break;
	// 	deleteBoardAtPos(game_board, display_board, height, width, cur);
	// 	printDisplayBoard(display_board, height);
	// }

	Coordinate cur = {1, 1};
	highlightPos(display_board, height, width, cur);
	printDisplayBoard(display_board, height);
	int inp = 0;
	while (inp != -1) {
		inp = getInput();
		if (inp > 0) {
			dehighlightPos(display_board, height, width, cur);
			moveCursor(cur, inp, height, width);
			highlightPos(display_board, height, width, cur);
			printDisplayBoard(display_board, height);
		}
		else if (inp == 0) {
			deleteBoardAtPos(game_board, display_board, height, width, cur);
			printDisplayBoard(display_board, height);
		}
	}

	deleteGameBoard(game_board, height, width);
	delete[] display_board;

	return 0;
}