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
	static const int title_x = (CONSOLE_WIDTH - 76) / 2;
	static const int title_y = 5;
	static const int list_x = (CONSOLE_WIDTH - Button::width) / 2;
	static const int list_y = 17;
	static string* title;
	static int title_height;
	static int title_width;
	static string player_selection;

	static void loadTitle();
	static void displayTitle();
	static void startMenu();

	static void startGame(int difficulty);
	static void showInfo();
	static void showSetting();
};