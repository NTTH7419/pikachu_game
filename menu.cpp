#include "menu.h"


void button::displayButton() {
	changeTextColor(BG_BLACK, TEXT_WHITE);
	for (int i = 0; i < height; i++) {
		goTo(x, y + i);
		if (i == 0) {
			cout << D_RIGHT_DOWN_CORNER;
			cout << string(width - 2, D_HORIZONTAL_EDGE);
			cout << D_LEFT_DOWN_CORNER;
		}
		else if (i == height - 1) {
			cout << D_RIGHT_UP_CORNER;
			cout << string(width - 2, D_HORIZONTAL_EDGE);
			cout << D_LEFT_UP_CORNER;
		}
		else {
			cout << D_VERTICAL_EDGE;
			cout << string(width - 2, ' ');
			cout << D_VERTICAL_EDGE;
		}
	}
	changeTextColor(BG_BLACK, TEXT_YELLOW);
	int len = text.length();
	goTo(x + (width - 2 - len) / 2 + (len % 2 == 1) + 1, y + height / 2);
	cout << text;
}

void button::highlightButton(const string bg_color, const string text_color) {
	changeTextColor(bg_color, text_color);
	for (int i = 1; i < height - 1; i++) {
		goTo(x + 1, y + i);
		cout << string(width - 2, ' ');
		cout << endl;
	}
	int len = text.length();
	goTo(x + (width - 2 - len) / 2 + (len % 2 == 1) + 1, y + height / 2);
	cout << text;
	changeTextColor(BG_BLACK, TEXT_WHITE);
}

void button::unhighlightButton() {
	highlightButton(BG_BLACK, TEXT_YELLOW);
}

void button::removeButton() {
	changeTextColor(BG_BLACK, TEXT_WHITE);
	for (int i = 0; i < height; i++) {
		goTo(x, y + i);
		cout << string(width, ' ');
	}
}



string* readTitle(int &title_hight) {
	title_hight = 0;
	string line;
	ifstream fin;
	fin.open("title.txt");
	while(getline(fin, line)) {
		title_hight++;
	}

	fin.close();
	fin.open("title.txt");

	string* title = new string[title_hight];
	for (int i = 0; i < title_hight; i++) {
		getline(fin, title[i]);
	}
	fin.close();
	return title;
}

void printTitle(int x, int y) {
	//read title
	string* title;
	int title_height;
	title = readTitle(title_height);

	// print title
	string line;
	for (int i = 0; i < title_height; i++) {
		goTo(x, y + i);
		line = title[i];
		for (int j = 0; j < line.length(); j++) {
			if (line[j] != '#') {
				cout << BG_BLACK << TEXT_WHITE;
				cout << line[j];
			}
			else {
				cout << BG_CYAN << TEXT_WHITE;
				cout << ' ';
			}
		}
		cout << BG_BLACK << TEXT_WHITE;
		cout << endl;
	}
	delete[] title;
}

void button_list::displayButtonList() {
	int len = button_instruction.length();
	goTo(x + (button_arr[0].width - len) / 2 + (len & 2 == 1), y);
	changeTextColor(BG_BLACK, TEXT_WHITE);
	cout << button_instruction;

	for (int i = 0; i < number_of_buttons; i++) {
		button_arr[i].displayButton();
	}
}


void button_list::removeButtonList() {
	int len = button_instruction.length();
	goTo(x + (button_arr[0].width - len) / 2 + (len & 2 == 1), y);
	changeTextColor(BG_BLACK, TEXT_WHITE);
	cout << string(len, ' ');

	for (int i = 0; i < number_of_buttons; i++) {
		button_arr[i].removeButton();
	}
}

string button_list::selectButton() {
	Input inp;
	int cur = 0;
	button_arr[cur].highlightButton(BG_CYAN, TEXT_WHITE);
	while (1) {
		inp = getInput();

		if (inp == Input::INVALID) continue;

		if (inp == Input::UP) {
			button_arr[cur].unhighlightButton();
			cur -= 1;
			cur = (cur + number_of_buttons) % number_of_buttons;
			button_arr[cur].highlightButton(BG_CYAN, TEXT_WHITE);
		}

		else if (inp == Input::DOWN) {
			button_arr[cur].unhighlightButton();
			cur += 1;
			cur = (cur + number_of_buttons) % number_of_buttons;
			button_arr[cur].highlightButton(BG_CYAN, TEXT_WHITE);
		}

		else if (inp == Input::ENTER) {
			return button_arr[cur].text;
		}
	}
}

void displayMainMenu() {
	printTitle(20, 0);
	int x_offset = 50;	// position of the menu
	int y_offset = 10;
	string selection;

	string* main_menu_text = new string[5] {"Play", "Highscores", "Infos", "Settings", "Quit Game"}; 
	string* difficulty_text = new string[4] {"Easy", "Medium", "Hard", "Back"}; 
	string* quit_text = new string[2] {"Yes", "No"};

	button_list main_menu = button_list("", main_menu_text, 5, x_offset, y_offset);
	button_list difficulty_menu = button_list("Choose difficulty:", difficulty_text, 4, x_offset, y_offset);
	button_list quit_menu = button_list("Quit game ?", quit_text, 2, x_offset, y_offset);

	while (1) {
		main_menu.displayButtonList();
		selection = main_menu.selectButton();
		main_menu.removeButtonList();

		if (selection == "Play") {
			difficulty_menu.displayButtonList();
			selection = difficulty_menu.selectButton();
			difficulty_menu.removeButtonList();

			if (selection == "Back") continue;

			if (selection == "Easy") {
				system("cls");
				board game_board = board(10, 15);
				game_board.gameLoop();
				system("cls");
				printTitle(20, 0);
				continue;
			}

			else if (selection == "Medium") {
				system("cls");
				board game_board = board(15, 20);
				game_board.gameLoop();
				system("cls");
				printTitle(20, 0);
				continue;
			}

			else if (selection == "Hard") {
				system("cls");
				cout << "Hard";
			}

			break;
		}

		else if (selection == "Highscores") {
			system("cls");
			cout << "Highscores";
			break;
		}

		else if (selection == "Infos") {
			system("cls");
			cout << "Infos";
			break;
		}

		else if (selection == "Settings") {
			system("cls");
			cout << "Settings";
			break;
		}

		else if (selection == "Quit Game") {
			quit_menu.displayButtonList();
			selection = quit_menu.selectButton();
			quit_menu.removeButtonList();

			if (selection == "Yes") {
				system("cls");
				break;
			}

			else if (selection == "No") continue;
		}
	}

	delete[] main_menu_text;
	delete[] difficulty_text;
	delete[] quit_text;
}