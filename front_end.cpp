#include "pikachu.h"

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
			display_board[line][10 * j + 5] = game_board[i][j];	// substitute the character in
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

bool deleteDisplayBoardAtPos(char** game_board, string* display_board, int height, int width, Coordinate pos) {
	if (!isInGameBoard(height, width, pos)) return 0;

	game_board[pos.y][pos.x] = 0;	//* sau nay viet ham xoa ben backend roi bo dong nay di
	display_board[4*pos.y + 2][10 * pos.x + 5] = ' ';	// remove character

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
		display_board[4 * pos.y + 1][10 * pos.x] = ' ';
		display_board[4 * pos.y + 2][10 * pos.x] = ' ';
		display_board[4 * pos.y + 3][10 * pos.x] = ' ';
	}

	if (right) {	// check right side
		display_board[4 * pos.y + 1][10 * pos.x + 10] = ' ';
		display_board[4 * pos.y + 2][10 * pos.x + 10] = ' ';
		display_board[4 * pos.y + 3][10 * pos.x + 10] = ' ';
	}

	if (top) display_board[4 * pos.y].replace(10 * pos.x + 1, 9, 9, ' '); 			// check above
	if (bottom) display_board[4 * pos.y + 4].replace(10 * pos.x + 1, 9, 9, ' ');		// check below
	if (top_left && left && top) display_board[4 * pos.y][10 * pos.x] = ' ';			// check left top
	if (top_right && right && top) display_board[4 * pos.y][10 * pos.x + 10] = ' ';		//check right top
	if (bottom_left && left && bottom) display_board[4 * pos.y + 4][10 * pos.x] = ' ';	// check left bottom
	if (bottom_right && right && bottom) display_board[4 * pos.y + 4][10 * pos.x + 10] = ' ';	//check right bottom

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

void copyDisplayBoard(string* display_board, string* display_board_path, int height) {
	for(int i = 0; i < 4 * (height + 2); i++) {
		display_board_path[i] = display_board[i].substr();
	}
}

void drawPath(string* display_board_path, int height, int width, Stack &s) {
	Coordinate prev, curr, next;
	Vector prev_curr, curr_next;
	bool isStart = true , isEnd = false;
	prev = {-1, -1};
	pop(s, curr);
	pop(s, next);

	while (true) {
		prev_curr = curr - prev;
		curr_next = next - curr;
		// cout << prev.x << ' ' << prev.y << "  -  " << curr.x << ' ' << curr.y  << "  -  " << next.x << ' ' << next.y << endl;
		// cout << prev_curr.x << ' ' << prev_curr.y << "  -  " << curr_next.x << ' ' << curr_next.y << endl;
		// cout << isStart << "  -  " << isEnd << endl;

		// huong di
		if (!isEnd) {
			if (curr_next.x == 0) {
				if (curr_next.y < 0) {	// di len
					if (!isStart) {
						display_board_path[4 * curr.y + 1][10 * curr.x + 5] = '|';
						display_board_path[4 * curr.y + 2][10 * curr.x + 5] = '|';
					}
				}
				else {					// di xuong
					display_board_path[4 * curr.y + 4][10 * curr.x + 5] = '|';
					if (!isStart) {
						display_board_path[4 * curr.y + 2][10 * curr.x + 5] = '|';
						display_board_path[4 * curr.y + 3][10 * curr.x + 5] = '|';
					}
				}
			}
			else {
				if (curr_next.x > 0) {	// qua phai
					display_board_path[4 * curr.y + 2].replace(10 * curr.x + 9, 2, 2, '-');
					if (!isStart)
						display_board_path[4 * curr.y + 2].replace(10 * curr.x + 5, 4, 4, '-');
				}
				else {					// qua trai
					display_board_path[4 * curr.y + 2][10 * curr.x + 1] = '-';
					if (!isStart)
						display_board_path[4 * curr.y + 2].replace(10 * curr.x + 2, 4, 4, '-');
				}
			}
		}

		// huong den
		if (!isStart) {
			if (prev_curr.x == 0) {
				if (prev_curr.y > 0) {	// tu tren
					if (!isEnd)
						display_board_path[4 * curr.y + 1][10 * curr.x + 5] = '|';
				}
				else {					// tu duoi
					display_board_path[4 * curr.y + 4][10 * curr.x + 5] = '|';
					if (!isEnd)
						display_board_path[4 * curr.y + 3][10 * curr.x + 5] = '|';
				}
			}
			else {
				if (prev_curr.x < 0) {	// tu phai
					display_board_path[4 * curr.y + 2].replace(10 * curr.x + 9, 2, 2, '-');
					if (!isEnd)
						display_board_path[4 * curr.y + 2].replace(10 * curr.x + 5, 4, 4, '-');
				}
				else {					// tu trai
					display_board_path[4 * curr.y + 2][10 * curr.x + 1] = '-';
					if (!isEnd)
						display_board_path[4 * curr.y + 2].replace(10 * curr.x + 2, 4, 4, '-');
				}
			}
		}

		if (isStart) isStart = false;
		if (isEnd) break;
		prev = curr;
		curr = next;
		isEnd = !pop(s, next);
	}
}

void gameLoop(char** game_board, string* display_board, int height, int width) {
	int n = height * width;
	Coordinate cur1, cur2;
	int inp;
	bool cur1_selected = false;
	Stack stack;

	string *display_board_path = new string[(height + 2) * 4 + 1] {};
	copyDisplayBoard(display_board, display_board_path, height);

	stack.pHead = NULL;
	cur1 = cur2 = {1, 1};
	highlightPos(display_board, height, width, cur1);
	printDisplayBoard(display_board, height);
	
	while (n > 0) {
		inp = getInput();

		// invalid input
		if (inp == -2) continue;

		// escape
		if (inp == -1) break;
		
		// move cursor
		if (inp > 0) {
			if (!cur1_selected) {
				dehighlightPos(display_board, height, width, cur1);
				moveCursor(cur1, inp, height, width);
				highlightPos(display_board, height, width, cur1);
			}
			else {
				if (cur2 != cur1) dehighlightPos(display_board, height, width, cur2);
				moveCursor(cur2, inp, height, width);
				highlightPos(display_board, height, width, cur2);
			}

			printDisplayBoard(display_board, height);
		}

		// select cell
		else {
			cout << cur1_selected << endl;
			if (!cur1_selected) {
				if (game_board[cur1.y][cur1.x] == 0) continue; // if select empty cell
				cur1_selected = true;
				cur2 = cur1;
			}

			// matching
			else {
				if (game_board[cur2.y][cur2.x] == 0) continue;
				if (cur1 != cur2 && game_board[cur1.y][cur1.x] == game_board[cur2.y][cur2.x] 
					&& findPath(game_board, height, width, stack, cur1, cur2)
				) {
					drawPath(display_board_path, height, width, stack);
					printDisplayBoard(display_board_path, height);

					deleteDisplayBoardAtPos(game_board, display_board, height, width, cur1);
					dehighlightPos(display_board, height, width, cur1);
					deleteDisplayBoardAtPos(game_board, display_board, height, width, cur2);
					
					dehighlightPos(display_board, height, width, cur2);
					copyDisplayBoard(display_board, display_board_path, height);
					highlightPos(display_board, height, width, cur2);

					Sleep(1000);
					n -= 2;
					cur1 = cur2;
					printDisplayBoard(display_board, height);
				}
				else {
					if (cur2 != cur1) dehighlightPos(display_board, height, width, cur1);
					cur1 = cur2;
					printDisplayBoard(display_board, height);
				}
				cur1_selected = false;
			}
		}
	}

	delete[] display_board_path;
}
