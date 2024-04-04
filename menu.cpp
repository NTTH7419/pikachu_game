#include "menu.h"


void Button::displayButton() {
	changeTextColor(colors.BG_main_bg, colors.TXT_button_drawing);
	drawBox(x, y, width, height);

	changeTextColor(colors.BG_main_bg, colors.TXT_button_text);
	int len = option.length();
	goTo(x + (width - len) / 2, y + height / 2);
	cout << option;
}

void Button::highlightButton(const string bg_color = colors.BG_button_selecting,
							 const string text_color = colors.TXT_button_highlight_text) {
	changeTextColor(bg_color, text_color);
	for (int i = 1; i < height - 1; i++) {
		goTo(x + 1, y + i);
		cout << string(width - 2, ' ');
		cout << endl;
	}
	int len = option.length();
	goTo(x + (width - len) / 2, y + height / 2);
	cout << option;
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
}

void Button::unhighlightButton() {
	highlightButton(colors.BG_main_bg, colors.TXT_button_text);
}

void Button::removeButton() {
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	for (int i = 0; i < height; i++) {
		goTo(x, y + i);
		cout << string(width, ' ');
	}
}


void Menu::loadTitle() {
	title_height = 0;
	title_width = 0;
	string line;
	ifstream fin;

	// read title dimension
	fin.open("title.txt");
	while(getline(fin, line)) {
		title_height++;
		if (line.length() > title_width)
			title_width = line.length();
	}
	fin.close();

	// read title
	fin.open("title.txt");
	title = new string[title_height];
	for (int i = 0; i < title_height; i++) {
		getline(fin, title[i]);
	}
	fin.close();
}

void Menu::displayTitle() {
	string line;
	for (int i = 0; i < title_height; i++) {
		goTo(title_x, title_y + i);
		line = title[i];
		for (int j = 0; j < line.length(); j++) {
			if (line[j] != '#') {
				changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
				cout << line[j];
			}
			else {
				changeTextColor(colors.BG_title, colors.TXT_main_text);
				cout << ' ';
			}
		}
		changeTextColor(colors.BG_main_bg, colors.BG_main_bg);
		cout << endl;
	}
}

void Options_list::displayOptionsList() {
	int len = button_instruction.length();
	goTo(x + (button_arr[0].width - len) / 2 + (len & 2 == 1), y);
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << button_instruction;

	for (int i = 0; i < number_of_buttons; i++) {
		button_arr[i].displayButton();
	}
}


void Options_list::removeOptionsList() {
	int len = button_instruction.length();
	goTo(x + (button_arr[0].width - len) / 2 + (len & 2 == 1), y);
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << string(len, ' ');

	for (int i = 0; i < number_of_buttons; i++) {
		button_arr[i].removeButton();
	}
}

string Options_list::selectOption() {
	displayOptionsList();
	Input inp;
	int cur = 0;
	button_arr[cur].highlightButton();
	while (1) {
		inp = getInput();

		if (inp == Input::INVALID) continue;

		if (inp == Input::UP) {
			playSFX(SFX_MOVE_CURSOR);
			button_arr[cur].unhighlightButton();
			cur -= 1;
			cur = (cur + number_of_buttons) % number_of_buttons;
			button_arr[cur].highlightButton();
		}

		else if (inp == Input::DOWN) {
			playSFX(SFX_MOVE_CURSOR);
			button_arr[cur].unhighlightButton();
			cur += 1;
			cur = (cur + number_of_buttons) % number_of_buttons;
			button_arr[cur].highlightButton();
		}

		else if (inp == Input::ENTER) {
			playSFX(SFX_SELECT);
			removeOptionsList();
			return button_arr[cur].option;
		}
	}
}

void Menu::startGame(int difficulty) {
	Game g = Game(difficulty);
	g.initGame();
	g.gameFinished(g.gameLoop());
}

void Menu::showInfo() {
	goTo(25, 19);
	cout << "Welcome to ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_YELLOW);
	cout << "Pikachu++";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << ", a matching game on console. ";
	cout << "This is a project for Programing Techniques course at ";
	changeTextColor(colors.BG_main_bg, colors.TXT_blue);
	cout << "FIT@HCMUS";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << ".";

	goTo(25, 21);
	cout << "This project is made by ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_RED);
	cout << "Phung Ngoc Tuan";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << " and ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_RED);
	cout << "Ngo Quang Thang";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << ", under the instruction of ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_ORANGE);
	cout << "MSc. Bui Huy Thong";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << " and ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_ORANGE);
	cout << "MSc. Tran Thi Thao Nhi";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << ".";

	goTo(25, 23);
	cout << "Special thanks to ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_GREEN);
	cout << "Nguyen Hoang Minh Tam";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << ", ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_GREEN);
	cout << "Tran Cong Minh";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << " and ";
	changeTextColor(colors.BG_main_bg, colors.TEXT_GREEN);
	cout << "Le Hoang Lam";
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	cout << " for discussions during game development.";

	goTo(70, 27);
	changeTextColor(colors.BG_main_bg, colors.TEXT_PINK);
	cout << "Press ESC to go back to the main menu";
	while(getInput() != Input::ESCAPE);		// wait for player to press ESC
	
	goTo(25, 19);
	cout << string(150, ' ');
	goTo(25, 21);
	cout << string(150, ' ');
	goTo(25, 23);
	cout << string(150, ' ');
	goTo(70, 27);
	cout << string(150, ' ');
}


void Menu::startMenu() {
	displayTitle();

	while (1) {
		player_selection = main_menu.selectOption();

		if (player_selection == "Play") {
			player_selection = difficulty_menu.selectOption();

			if (player_selection == "Back") {
				player_selection = "";
				continue;
			}

			if (player_selection == "Easy") {
				player_selection = "";
				startGame(EASY);
				displayTitle();
				continue;
			}

			else if (player_selection == "Medium") {
				player_selection = "";
				startGame(MEDIUM);
				displayTitle();
				continue;
			}

			else if (player_selection == "Hard") {
				player_selection = "";
				startGame(HARD);
				displayTitle();
				continue;
			}
		}

		else if (player_selection == "Highscores") {
			player_selection = "";
			Highscores::displayHighscores();
			continue;			
		}

		else if (player_selection == "Infos") {
			player_selection = "";
			showInfo();
			continue;
		}

		else if (player_selection == "Settings") {
			showSetting();
			player_selection = "";
			continue;
		}

		else if (player_selection == "Quit Game") {
			player_selection = quit_menu.selectOption();

			if (player_selection == "Yes") {
				player_selection = "";
				system("cls");
				break;
			}

			else if (player_selection == "No") continue;
		}
	}
}

void Menu::showSetting() {

	const string theme_options[2] {"Light", "Dark"};
	Options_list theme_menu = Options_list("Set theme", theme_options, 2, list_x, list_y);
	const string sound_options[2] {"On", "Off"};
	Options_list sound_menu = Options_list("Set sound on/ off", sound_options, 2, list_x, list_y);

	bool is_dark_mode, is_sound_on;
	ifstream fin("settings.txt");
	fin >> is_dark_mode >> is_sound_on;
	fin.close();

	player_selection = setting_menu.selectOption();
	while (player_selection != "Back") {
		if (player_selection == "Theme") {
			player_selection = theme_menu.selectOption();
			if (player_selection == "Light")
				is_dark_mode = 0;
			else if (player_selection == "Dark")
				is_dark_mode = 1;
			player_selection == "";
		}
		else if (player_selection == "Sound") {
			player_selection = sound_menu.selectOption();
			if (player_selection == "On")
				is_sound_on = 1;
			else if (player_selection == "Off")
				is_sound_on = 0;
			player_selection == "";
		}
		player_selection = setting_menu.selectOption();
	}

	ofstream fout("settings.txt");
	fout << is_dark_mode << " " << is_sound_on;
	fout.close();
}