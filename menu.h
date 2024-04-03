#pragma once

#include "game.h"
// #include "console.h"
#include <fstream>

using namespace std;

struct Button {
	string option;
	int x, y;		// top left position of the button on screen

	static const int width = 25, height = 3;		// size of the button

	void displayButton();
	void highlightButton(const string bg_color, const string text_color);
	void unhighlightButton();
	void removeButton();
};

struct Options_list {
	int x, y;		// top left position of the list on screen
	int number_of_buttons;
	string button_instruction;
	Button *button_arr;

	Options_list(const string instruction, const string button_text[], int n, int pos_x, int pos_y) {
		x = pos_x;
		y = pos_y;
		button_instruction = instruction;
		number_of_buttons = n;
		button_arr = new Button[number_of_buttons];
		for (int i = 0; i < number_of_buttons; i++) {
			button_arr[i].option = button_text[i];
			button_arr[i].x = x;
			button_arr[i].y = y + 2 + (button_arr[i].height) * i;
		}
	}

	~Options_list() {
		delete[] button_arr;
	}

	void displayOptionsList();
	void removeOptionsList();
	string selectOption();
};

struct Menu {
	int title_x = (CONSOLE_WIDTH - 76) / 2;
	int title_y = 5;
	int list_x = (CONSOLE_WIDTH - Button::width) / 2;
	int list_y = 17;
	string* title;
	int title_height;
	int title_width;
	string player_selection;

	const string main_menu_options[5] {"Play", "Highscores", "Infos", "Settings", "Quit Game"};
	const string difficuty_options[4] {"Easy", "Medium", "Hard", "Back"};
	const string quit_confirm[2] {"Yes", "No"};
	const string setting_options[2] {"Theme", "Sound"};

	const string welcome = "Welcome to Pokemon++, a matching game on console";
	const string difficulty_instruction = "Choose difficulty:";
	const string quit_instruction = "Quit game?";
	const string setting_instruction = "Set your preferences, please restart game for this to take effect";

	Options_list main_menu = Options_list(welcome, main_menu_options, 5, list_x, list_y);
	Options_list difficulty_menu = Options_list(difficulty_instruction, difficuty_options, 4, list_x, list_y);
	Options_list quit_menu = Options_list(quit_instruction, quit_confirm, 2, list_x, list_y);
	Options_list setting_menu = Options_list(setting_instruction, setting_options, 2, list_x, list_y);

	Menu() {
		loadTitle();
	}

	~Menu() {
		delete[] title;
	}
	void loadTitle();
	void displayTitle();
	void startMenu();

	void startGame(int difficulty);
	void showInfo();
	void showSetting();
};