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
	int height = game_board->height;
	int width = game_board->width;

	for (int i = 1; i <= height; i++){
		for (int j = 1; j <= width; j++){
			if (game_board->letter_board[i][j] != '\0'){
				char piece = game_board->letter_board[i][j];
				int k = i;
				for (int k = i; k <= height; k++){
					for (int l = 0; l <= width; l++){
						vector<Coordinate> temp;
						if (game_board->letter_board[k][l] == piece && !(i == k && j == l) && game_board->match({j, i}, {l, k}, temp)){
							Coordinate pos1 = {j, i};
							Coordinate pos2 = {l, k};
							game_board->highlightHintPair(pos1, pos2);
							Sleep(500);
							game_board->unhighlightCell(pos1);
							game_board->unhighlightCell(pos2);
							return;
						}
					}
				} 
			}
		}
	}


	
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

		if (inp == Input::SHUFFLE){
			shuffle(game_board);
			continue;
		}
		
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

void game::shuffle(board* game_board){
	srand(time(NULL));

	for (int n = 0; n < game_board->height * game_board->width; n++){
		int i = rand() % game_board->height + 1;
		int j = rand() % game_board->width + 1;

		int k = rand() % game_board->height + 1;
		int l = rand() % game_board->width + 1;

		if (game_board->letter_board[i][j] != '\0' && game_board->letter_board[k][l] != '\0'){
			Coordinate pos1 = {j, i};
			Coordinate pos2 = {l, k};

			swap(game_board->letter_board[i][j], game_board->letter_board[k][l]);
			game_board->unhighlightCell(pos1);
			game_board->unhighlightCell(pos2);
		}
	}

}