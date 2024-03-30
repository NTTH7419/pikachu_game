#include "game.h"

void game::displayGameInfo() {
	// temporary
	goTo(5, 10);
	changeTextColor(color.BG_main_bg, color.TXT_highlight_text);
	cout << "Score: 0";
}

void game::moveCursor(Coordinate &cur, Input inp) {
	if (inp == Input::UP) {
		cur.y -= 1;
		if (cur.y <= 0) cur.y = board_height;	// if cursor moves outside of board, it moves to the other side
	}

	else if (inp == Input::LEFT) {
		cur.x -= 1;
		if (cur.x <= 0) cur.x = board_width;	
	}

	else if (inp == Input::DOWN) {
		cur.y += 1;
		if (cur.y > board_height) cur.y = 1;
	}

	else if (inp == Input::RIGHT) {
		cur.x += 1;
		if (cur.x > board_width) cur.x = 1;
	}
}

bool game::matchCell(Coordinate cur1, Coordinate cur2) {
	vector<Coordinate> path;
	queue<Coordinate> drawn_pixels;

	if (cur1 != cur2 &&
		game_board->getLetter(cur1) == game_board->getLetter(cur2) &&
		game_board->match(cur1, cur2, path)) {

		drawn_pixels = game_board->drawPath(path);
		game_board->highlightCorrectPair(cur1, cur2);
		Sleep(500);

		game_board->deletePath(drawn_pixels);
		game_board->removeCell(cur1);
		game_board->removeCell(cur2);
		game_board->unhighlightCell(cur1);
		game_board->highlightCursor(cur2);
		return true;
	}
	else {
		game_board->highlightWrongPair(cur1, cur2);
		Sleep(500);
		game_board->unhighlightCell(cur1);
		game_board->highlightCursor(cur2);
		return false;
	}
}

void game::showHint() {
	// temporary
	Coordinate hint_cell1 = {3, 4};
	Coordinate hint_cell2 = {5, 2};

	// code to find hint here

	game_board->highlightHintPair(hint_cell1, hint_cell2);
	Sleep(500);
	game_board->unhighlightCell(hint_cell1);
	game_board->unhighlightCell(hint_cell2);
}

void game::updateScore(int bonus_score) {
	// temporary
	score += bonus_score;
	goTo(12, 10);
	changeTextColor(color.BG_main_bg, color.TXT_highlight_text);
	cout << score;
}

void game::initGame() {
	system("cls");
	score = 0;
	game_board->initBoard();
	displayGameInfo();
}

void game::gameLoop() {

	int remaining_cell = board_height * board_width;
	Coordinate cur1, cur2;	// cursor 1 and cursor 2, 
	Input inp;
	bool cur1_selected = false;
	bool use_hint = false;
	
	game_board->displayBoard();

	cur1 = cur2 = {1, 1};
	game_board->highlightCursor(cur1);
	
	while (remaining_cell > 0) {
		inp = getInput();

		// invalid input
		if (inp == Input::INVALID) continue;

		// escape
		if (inp == Input::ESCAPE) break;
		
		// move cursor
		if (inp == Input::UP || inp == Input::LEFT || inp == Input::DOWN || inp == Input::RIGHT) {
			if (!cur1_selected) {
				game_board->unhighlightCell(cur1);
				moveCursor(cur1, inp);
				game_board->highlightCursor(cur1);
			}
			else {
				if (cur1 != cur2) game_board->unhighlightCell(cur2);
				else game_board->highlightSelected(cur1);	// if cursor passes though the selected cell, highlight it again
				moveCursor(cur2, inp);
				game_board->highlightCursor(cur2);
			}
		}

		// select cell
		else if (inp == Input::ENTER) {

			// select cell 1
			if (!cur1_selected) {
				if (!game_board->isValid(cur1)) continue; // if select invalid cell (removed cell), do nothing
				game_board->highlightSelected(cur1);
				cur1_selected = true;
				cur2 = cur1;
			}

			// select cell 2
			else {
				if (cur2 == cur1) {		// deselect cell 1
					game_board->highlightCursor(cur2);
					cur1_selected = false;
					continue;
				}
				if (!game_board->isValid(cur2)) continue; // if select empty cell, do nothing

				// matching
				if (matchCell(cur1, cur2)) {
					remaining_cell -= 2;
					updateScore(50);
				}
				else {
					updateScore(-20);
				}
				cur1 = cur2;
				cur1_selected = false;
				use_hint = false;
			}
		}

		// show hint
		else if (inp == Input::HINT) {
			// temporary
			if (!use_hint) {
				updateScore(-100);
				showHint();
				use_hint = true;
				if (!cur1_selected) {
					game_board->highlightCursor(cur1);
				}
				else {
					game_board->highlightSelected(cur1);
					game_board->highlightCursor(cur2);
				}
			}
		}
	}
	game_board->unhighlightCell(cur1);
}

void game::gameFinished() {
	// temporary
	goTo(50, 15);
	cout << "Your score is: " << score;
	goTo(50, 16);
	cout << "Press any key to go back";
	getInput();
	system("cls");
}