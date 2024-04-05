#include "game.h"

void Game::moveCursor(Coordinate &cur, Input inp) {
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

	
	//correct pair highlighting and deleting
	if (cur1 != cur2 &&		//check if the two coordinates are not the same
		game_board->getLetter(cur1) == game_board->getLetter(cur2) && //check if they have the same representative letter
		game_board->bfs(cur1, cur2, path) //check if there exists a valid path between the two cells
		) {

		//draw the path
		drawn_pixels = game_board->drawPath(path);
		game_board->highlightCorrectPair(cur1, cur2);
		playSFX(SFX_CORRECT);
		Sleep(500);

		game_board->deletePath(drawn_pixels, cur1, cur2);
		
		//delete the cell and shifting (right most element gets deleted first)
		game_board->removeCell(cur1.x < cur2.x ? cur2 : cur1);
		game_board->removeCell(cur1.x < cur2.x ? cur1 : cur2);

		game_board->unhighlightCell(cur1);
		game_board->highlightCursor(cur2);
		return true;
	}

	//incorrect pair highlighting
	else {
		game_board->highlightWrongPair(cur1, cur2);
		playSFX(SFX_WRONG);
		Sleep(500);
		game_board->unhighlightCell(cur1);
		game_board->highlightCursor(cur2);
		return false;
	}
}

void Game::showHint(){
	Coordinate pos1;
	Coordinate pos2;
	if (game_board->findValidPair(pos1, pos2)){
		game_board->highlightHintPair(pos1, pos2);
	}
}

void Game::displayGameInfo() {
	drawBox(1, 1, 29, 18);
	drawBox(1, 19, 29, 23);

	// score
	goTo(5, 4);
	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	cout << "Score: ";
	changeTextColor(Colors::BG_main_bg, Colors::TXT_blue);
	cout << score;

	// hint
	goTo(5, 7);
	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	cout << "Hint: ";
	changeTextColor(Colors::BG_main_bg, TEXT_GREEN);
	cout << hint_remaining;

	// score rules
	goTo(10, 10);
	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	cout << "Score rules";
	goTo(4, 12);
	changeTextColor(Colors::BG_main_bg, TEXT_GREEN);
	cout << "Correct pair +50 pts";
	goTo(4, 13);
	changeTextColor(Colors::BG_main_bg, TEXT_RED);
	cout << "Wrong pair/";
	goTo(6, 14);
	cout << "can't match -20 pts";
	goTo(4, 15);
	changeTextColor(Colors::BG_main_bg, TEXT_PURPLE);
	cout << "Use hint -100 pts";
	// goTo(4, 16);
	// changeTextColor(Colors::BG_main_bg, TEXT_PINK);
	// cout << "Use shuffle -200 pts";

	// play instruction
	goTo(10, 20);
	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	cout << "How to play";

	goTo(4, 22);
	changeTextColor(Colors::BG_main_bg, Colors::TXT_blue);
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
	changeTextColor(Colors::BG_main_bg, TEXT_ORANGE);
	cout << "ENTER to select, ";
	goTo(6, 29);
	cout << "select again to cancel";

	goTo(4, 31);
	changeTextColor(Colors::BG_main_bg, TEXT_PURPLE);
	cout << "H to show hint,";
	goTo(6, 32);
	cout << "you have 3 hints";

	// goTo(4, 34);
	// changeTextColor(Colors::BG_main_bg, TEXT_PINK);
	// cout << "R to shuffle the board";

	goTo(4, 34);
	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	cout << "ESC to return";
	goTo(6, 35);
	cout << "to main menu";
}

void Game::updateScore(int bonus_score) {
	// print score
	changeTextColor(Colors::BG_main_bg, Colors::TXT_blue);
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
		changeTextColor(Colors::BG_main_bg, TEXT_RED);
		cout << bonus_score;
	}
	else {
		changeTextColor(Colors::BG_main_bg, TEXT_GREEN);
		cout << '+' << bonus_score;
	}
}

void Game::updateRemainHint() {
	if (hint_remaining <= 0) {
		goTo(11,7);
		changeTextColor(Colors::BG_main_bg, TEXT_RED);
		cout << hint_remaining;
		goTo(5, 8);
		cout << "No more hint available";
	}
	else {
		goTo(11, 7);
		changeTextColor(Colors::BG_main_bg, TEXT_GREEN);
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
	while (name.find(',') != name.npos || name.size() > 30 || name.size() == 0) {
		goTo(x + 1, y + 1);
		cout << string(50, ' ');
		goTo(x + 31, y + 1);
		cout << D_VERTICAL_EDGE;
		goTo(x + (32 - 25) / 2 , y + 3);
		cout << "Please input a valid name";
		goTo(x + 1, y + 1);
		setCursorAppearance(1);
		getline(cin, name);
		setCursorAppearance(0);
	}
	goTo(x + (32 - 25) / 2 , y + 3);
	cout << string(25, ' ');
}

void Game::initGame() {
	system("cls");
	score = 0;

	if(game_board->isArray)
		game_board->initBoard();
	else
		game_board->initListBoard();

	displayGameInfo();
	drawBox(30, 1, 141, 41);	// game board's box
	Sleep(500);
	game_board->displayBoard();
}

bool Game::gameLoop() {
	clock_t start_time;
	int remaining_cell = board_height * board_width;
	Coordinate cur1, cur2;	// cursor 1 and cursor 2
	Coordinate pos1, pos2;	// position of hint
	Input inp;
	bool cur1_selected = false;

	cur1 = cur2 = {1, 1};
	game_board->highlightCursor(cur1);
	
	start_time = clock();
	while (remaining_cell > 0) {
		

		// shuffle board if there are no valid pairs
		if (!cur1_selected && !game_board->findValidPair(pos1, pos2)){
			game_board->unhighlightCell(cur1);
			game_board->shuffleBoard();
			game_board->animateShuffle();
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
	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	goTo(30 + (141 - (game_board->bg_info).length()) / 2, 38);
	cout << game_board->bg_info;
	goTo(89, 39);
	changeTextColor(Colors::BG_main_bg, TEXT_PINK);
	playSFX(SFX_WIN);
	cout << "Press Enter to continue";
	while(getInput() != Input::ENTER);
	
	// clear screen
	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	for (int i = 0; i < 39; i++) {
		goTo(31, 2 + i);
		cout << string(139, ' ');
	}

	goTo(93, 15);
	changeTextColor(Colors::BG_main_bg, TEXT_YELLOW);
	cout << "Congratulation";

	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	goTo(90, 18);
	cout << "Your score is: ";
	changeTextColor(Colors::BG_main_bg, Colors::TXT_blue);
	cout << score;

	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	goTo(90, 19);
	cout << "Your time is: ";
	changeTextColor(Colors::BG_main_bg, Colors::TXT_blue);
	play_time.displayTime();

	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	goTo(68, 21);
	cout << "Please input your name (maximum 30 characters, no ',' allowed)";
	goTo(88, 22);
	cout << "Press Enter when finished";
	inputName(84, 23);
	
	Highscores::updateHighscores({name, score, play_time});

	goTo(73, 26);
	changeTextColor(Colors::BG_main_bg, TEXT_PINK);
	cout << "Your score is saved. Press ESC to go back to main menu";
	getInput();
	system("cls");
}

vector<Result> Highscores::records;

void Highscores::loadHighscores() {
	Result temp;
	char c;
	ifstream fin("highscores.csv");

	while(getline(fin, temp.name, ',')) {
		fin >> temp.score;
		fin >> c;
		fin >> temp.play_time.min;
		fin >> c;
		fin >> temp.play_time.sec;
		fin.ignore();
		records.push_back(temp);
	}
	fin.close();
}

void Highscores::updateHighscores(Result result) {
	bool isUpdated = false;

	for (int i = 0; i < records.size(); i++) {
		if (result > records[i]) {
			records.insert(records.begin() + i, result);
			isUpdated = true;
			break;
		}
	}

	if (!isUpdated && records.size() < 5) {
		records.push_back(result);
	}
	
	// remove top 6
	if (records.size() > 5) {
		records.pop_back();
	}

	// print score again
	ofstream fout("highscores.csv");
	for (int i = 0; i < records.size(); i++) {
		fout << records[i].convertToCSV() << endl;
	}
	fout.close();
}

void Highscores::displayHighscores() {
	goTo((CONSOLE_WIDTH - 10) / 2, 17);
	changeTextColor(Colors::BG_main_bg, TEXT_GREEN);
	cout << "Highscores";
	changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
	drawBox((CONSOLE_WIDTH - 70) / 2, 20, 70, 13);
	goTo(52, 22);
	cout << string(68, HORIZONTAL_EDGE);
	changeTextColor(Colors::BG_main_bg, Colors::TXT_blue);
	goTo(55, 21);
	cout << "Rank";
	goTo(65, 21);
	cout << "Name";
	goTo(100, 21);
	cout << "Score";
	goTo(110, 21);
	cout << "Time";
	for (int i = 0; i < records.size(); i++) {
		if (i == 0) {
			changeTextColor(Colors::BG_main_bg, TEXT_ORANGE);
		}
		else {
			changeTextColor(Colors::BG_main_bg, Colors::TXT_main_text);
		}
		goTo(55, 23 + 2 * i);
		cout << i + 1;
		goTo(65, 23 + 2 * i);
		cout << records[i].name;
		goTo(100, 23 + 2 * i);
		cout << records[i].score;
		goTo(110, 23 + 2 * i);
		records[i].play_time.displayTime();
	}

	goTo(70, 35);
	changeTextColor(Colors::BG_main_bg, TEXT_PINK);
	cout << "Press ESC to go back to the main menu";
	while(getInput() != Input::ESCAPE);

	for (int i = 17; i <= 35; i++) {
		goTo(50, i);
		cout << string(100, ' ');
	}
}