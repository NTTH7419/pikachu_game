#pragma once

#include "game.h"
#include "console.h"
#include <fstream>

using namespace std;

#define EASY 1
#define MEDIUM 2
#define HARD 3

struct button {
	string text;
	int x;
	int y;

	int width = 20;
	int height = 3;

	void displayButton();
	void highlightButton(const string bg_color, const string text_color);
	void unhighlightButton();
	void removeButton();
};

struct button_list {
	int x;
	int y;
	int number_of_buttons;
	string button_instruction;
	button *button_arr;

	button_list(string instruction, string* button_text, int n, int pos_x, int pos_y) {
		x = pos_x;
		y = pos_y;
		button_instruction = instruction;
		number_of_buttons = n;
		button_arr = new button[number_of_buttons];
		for (int i = 0; i < number_of_buttons; i++) {
			button_arr[i].text = button_text[i];
			button_arr[i].x = x;
			button_arr[i].y = y + 2 + (button_arr[i].height) * i;
		}
	}

	~button_list() {
		delete[] button_arr;
	}

	void displayButtonList();
	void removeButtonList();
	string selectButton();
};

void displayMainMenu();