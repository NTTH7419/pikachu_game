#include "game.h"

void Game::moveCursor(Coordinate &cur, Input inp) {
	playSFX(SFX_MOVE_CURSOR);
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

bool Game::matchCell(Coordinate cur1, Coordinate cur2) {
	vector<Coordinate> path;
	queue<Coordinate> drawn_pixels;

	if (cur1 != cur2 &&
		game_board->getLetter(cur1) == game_board->getLetter(cur2) &&
		game_board->bfs(cur1, cur2, path)
		) {

		
		drawn_pixels = game_board->drawPath(path);
		game_board->highlightCorrectPair(cur1, cur2);
		playSFX(SFX_CORRECT);

		game_board->deletePath(drawn_pixels);
		
		game_board->removeCell(cur1.x < cur2.x ? cur2 : cur1);
		game_board->removeCell(cur1.x < cur2.x ? cur1 : cur2);
		game_board->unhighlightCell(cur1);
		game_board->highlightCursor(cur2);
		return true;
	}
	else {
		game_board->highlightWrongPair(cur1, cur2);
		playSFX(SFX_WRONG);
		Sleep(200);
		game_board->unhighlightCell(cur1);
		game_board->highlightCursor(cur2);
		return false;
	}
}

bool Game::findValidPairs(Coordinate &pos1, Coordinate &pos2) {
	for (int i = 1; i <= board_height; i++){
		for (int j = 1; j <= board_width; j++){
			if (game_board->isValid({j, i})){
				char piece = game_board->getLetter({j, i});
				for (int k = i; k <= board_height; k++){
					for (int l = 0; l <= board_width; l++){
						vector<Coordinate> temp;
						if (game_board->getLetter({l, k}) == piece && !(i == k && j == l) && game_board->bfs({j, i}, {l, k}, temp)){
							pos1 = {j, i};
							pos2 = {l, k};
							return 1;
						}
					}
				} 
			}
		}
	}	

	pos1 = {-1, -1};
	pos2 = {-1, -1};
	return 0;
}

void Game::showHint(){
	Coordinate pos1;
	Coordinate pos2;


	if (findValidPairs(pos1, pos2)){
		game_board->highlightHintPair(pos1, pos2);
	}
}

void Game::displayGameInfo() {
	drawBox(1, 1, 29, 18);
	drawBox(1, 19, 29, 23);

	// score
	goTo(5, 4);
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << "Score: ";
	changeTextColor(colors.BG_main_bg, colors.TXT_blue);
	cout << score;

	// hint
	goTo(5, 7);
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << "Hint: ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_GREEN);
	cout << hint_remaining;

	// score rules
	goTo(10, 10);
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << "Score rules";
	goTo(4, 12);
	changeTextColor(colors.BG_main_bg, colors.TEXT_GREEN);
	cout << "Correct pair +50 pts";
	goTo(4, 13);
	changeTextColor(colors.BG_main_bg, colors.TEXT_RED);
	cout << "Wrong pair/";
	goTo(6, 14);
	cout << "can't match -20 pts";
	goTo(4, 15);
	changeTextColor(colors.BG_main_bg, colors.TEXT_PURPLE);
	cout << "Use hint -100 pts";
	goTo(4, 16);
	changeTextColor(colors.BG_main_bg, colors.TEXT_PINK);
	cout << "Use shuffle -200 pts";

	// play instruction
	goTo(10, 20);
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << "How to play";

	goTo(4, 22);
	changeTextColor(colors.BG_main_bg, colors.TXT_blue);
	cout << "WASD to move cursor:";
	goTo(4, 23);
	cout << "- W: UP";
	goTo(4, 24);
	cout << "- A: LEFT";
	goTo(4, 25);
	cout << "- S: DOWN";
	goTo(4, 26);
	cout << "- D: RIGHT";

	goTo(4, 28);
	changeTextColor(colors.BG_main_bg, colors.TEXT_ORANGE);
	cout << "ENTER to select, ";
	goTo(6, 29);
	cout << "select again to cancel";

	goTo(4, 31);
	changeTextColor(colors.BG_main_bg, colors.TEXT_PURPLE);
	cout << "H to show hint,";
	goTo(6, 32);
	cout << "you have 3 hints";

	goTo(4, 34);
	changeTextColor(colors.BG_main_bg, colors.TEXT_PINK);
	cout << "R to shuffle the board";

	goTo(4, 36);
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << "ESC to return";
	goTo(6, 37);
	cout << "to main menu";
}

void Game::updateScore(int bonus_score) {
	// print score
	changeTextColor(colors.BG_main_bg, colors.TXT_blue);
	goTo(12, 4);
	cout << string(5, ' ');		// clear the previous score
	score += bonus_score;
	goTo(12, 4);
	cout << score;

	// print bonus score
	goTo(12, 5);
	cout << string(5, ' ');		// clear the previous bonus score
	goTo(12, 5);
	if (bonus_score < 0) {
		changeTextColor(colors.BG_main_bg, colors.TEXT_RED);
		cout << bonus_score;
	}
	else {
		changeTextColor(colors.BG_main_bg, colors.TEXT_GREEN);
		cout << '+' << bonus_score;
	}
}

void Game::updateRemainHint() {
	if (hint_remaining <= 0) {
		goTo(11,7);
		changeTextColor(colors.BG_main_bg, colors.TEXT_RED);
		cout << hint_remaining;
		goTo(5, 8);
		cout << "No more hint available";
	}
	else {
		goTo(11, 7);
		changeTextColor(colors.BG_main_bg, colors.TEXT_GREEN);
		cout << hint_remaining;
	}
}

void Game::inputName(int x, int y) {
	name = "";
	int c;
	drawBox(x, y, 32, 3);
	goTo(x + 1, y + 1);
	setCursorAppearance(1);
	getline(cin, name);
	setCursorAppearance(0);
	name = name.substr(0, 30);
}

void Game::initGame() {
	system("cls");
	score = 0;

	if(game_board->is_array)
		game_board->initBoard();
	else
		game_board->initListBoard();

	displayGameInfo();
	drawBox(30, 1, 141, 41);	// game board's box
	Sleep(300);
	game_board->displayBoard();
	// game_board->printList();
}

bool Game::gameLoop() {
	clock_t start_time;
	int remaining_cell = board_height * board_width;
	Coordinate cur1, cur2;	// cursor 1 and cursor 2, 
	Input inp;
	bool cur1_selected = false;

	cur1 = cur2 = {1, 1};
	game_board->highlightCursor(cur1);
	
	start_time = clock();
	while (remaining_cell > 0) {
		Coordinate pos1, pos2;

		// shuffle board if there are no valid pairs
		while (!findValidPairs(pos1, pos2)){
			game_board->unhighlightCell(cur1);
			game_board->unhighlightCell(cur2);
			cur1 = cur2 = {1, 1};
			cur1_selected = false;
			updateScore(-200);
			shuffleBoard();
			game_board->animateShuffle();
			hint_used = false;
			game_board->highlightCursor(cur1);
		
		}

		inp = getInput();

		// invalid input
		if (inp == Input::INVALID) continue;

		// escape
		if (inp == Input::ESCAPE) {
			return 0;
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
			continue;
		}

		// select cell
		if (inp == Input::ENTER) {

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
					// if (cur1.x < cur2.x){
					// 	game_board->shift(cur2);
					// 	game_board->shift(cur1);
					// }

					// else{
					// 	game_board->shift(cur1);
					// 	game_board->shift(cur2);
					// }

					updateScore(50);
				}
				else {
					updateScore(-20);
				}
				cur1 = cur2;
				cur1_selected = false;
				hint_used = false;
			}
			continue;
		}

		// show hint
		if (inp == Input::HINT) {
			if (!hint_used && hint_remaining > 0) {
				hint_remaining -= 1;
				updateRemainHint();
				updateScore(-100);
				showHint();
				hint_used = true;
			}
			continue;
		}

		
	}
	play_time.convert((clock() - start_time) / CLOCKS_PER_SEC);
	game_board->unhighlightCell(cur1);
	return 1;
}

void Game::gameFinished(bool isFinished) {
	if (!isFinished) {		// not finish 
		system("cls");
		return;
	}
	// show info and wait for user
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	goTo(30 + (141 - (game_board->bg_info).length()) / 2, 38);
	cout << game_board->bg_info;
	goTo(89, 39);
	changeTextColor(colors.BG_main_bg, colors.TEXT_PINK);
	playSFX(SFX_WIN);
	cout << "Press Enter to continue";
	while(getInput() != Input::ENTER);
	
	// clear screen
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	for (int i = 0; i < 39; i++) {
		goTo(31, 2 + i);
		cout << string(139, ' ');
	}

	goTo(93, 15);
	changeTextColor(colors.BG_main_bg, colors.TEXT_YELLOW);
	cout << "Congratulation";

	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	goTo(90, 18);
	cout << "Your score is: ";
	changeTextColor(colors.BG_main_bg, colors.TXT_blue);
	cout << score;

	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	goTo(90, 19);
	cout << "Your time is: ";
	changeTextColor(colors.BG_main_bg, colors.TXT_blue);
	play_time.displayTime();

	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	goTo(77, 21);
	cout << "Please input your name (maximum 30 characters)";
	goTo(88, 22);
	cout << "Press Enter when finished";
	inputName(84, 23);
	
	goTo(73, 26);
	changeTextColor(colors.BG_main_bg, colors.TEXT_PINK);
	cout << "Your score is saved. Press ESC to go back to main menu";
	getInput();
	system("cls");
}

void Game::shuffleBoard(){
	srand(time(NULL));


	for (int n = 0; n < board_height * board_width; n++){
		int i = rand() % board_height + 1;
		int j = rand() % board_width + 1;

		int k = rand() % board_height + 1;
		int l = rand() % board_width + 1;

		if (game_board->isValid({j, i}) && game_board->isValid({l, k})){

			if(game_board->is_array)
				swap(game_board->letter_board[i][j], game_board->letter_board[k][l]);
			else
				swap(game_board->list_board[i][j], game_board->list_board[k][l]);
		}
	}
}
