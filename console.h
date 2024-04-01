#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

enum Input{
	INVALID 	= -2,
	ESCAPE 		= -1,
	ENTER 		= 0,
	UP 			= 1,
	LEFT 		= 2,
	DOWN 		= 3,
	RIGHT 		= 4,
	HINT 		= 5,
	SHUFFLE     = 6
};


//* keys
const char K_ESC 	= 27;
const char K_ENTER 	= 13;
const char K_W 		= 'W';		// up
const char K_w 		= 'w';		// up
const char K_A 		= 'A';		// left
const char K_a 		= 'a';		// left
const char K_S 		= 'S';		// down
const char K_s 		= 's';		// down
const char K_D 		= 'D';		// right
const char K_d 		= 'd';		// right
const char K_H 		= 'H';		// hint
const char K_h 		= 'h';		// hint
const char K_r		= 'r';		// shuffle
const char K_R		= 'R';		//shuffle



struct game_color {
	private:
	//* colors
		// background
		const string BG_BLACK 		= "\33[0m";     		// for background in dark mode
		const string BG_WHITE 		= "\33[107m";   		// for background in light mode
		const string BG_RED 		= "\33[41m";      		// for wrong pair
		const string BG_YELLOW 		= "\33[43m";			// for title
		const string BG_ORANGE 		= "\33[48;5;208m";		// for selected cell
		const string BG_GREEN 		= "\33[42m";    		// for correct pair
		const string BG_CYAN 		= "\33[46m";     		// for cursor
		const string BG_GRAY 		= "\33[100m";    		// for hint pair

		// text
		const string TEXT_GREEN 	= "\33[32m";  			// for correct path
		const string TEXT_BLUE 		= "\33[34m";   			// for letters in light mode
		const string TEXT_YELLOW 	= "\33[93m"; 			// for letters in dark mode
		const string TEXT_PURPLE	= "\33[38;5;93m";		// for button text
		const string TEXT_MAGENTA 	= "\33[95m"; 			// for cell border
		const string TEXT_WHITE 	= "\33[97m";  			// for other characters and highlighted cell in dark mode
		const string TEXT_BLACK 	= "\33[30m";  			// for other characters in light mode
	
	public:
		// text color
		string TXT_main_text;
		string TXT_highlight_text;
		string TXT_cell_border;
		string TXT_letter;
		string TXT_highlight_letter;
		string TXT_path;
		string TXT_button_drawing;
		string TXT_button_text;
		string TXT_button_highlight_text;

		// background color
		string BG_main_bg;
		string BG_cell_cursor;
		string BG_cell_selected;
		string BG_cell_correct;
		string BG_cell_wrong;
		string BG_cell_hint;
		string BG_button_selecting;
		string BG_title;

		game_color() {
			bool is_dark_mode;
			ifstream fin;
			fin.open("settings.txt");
			fin >> is_dark_mode;
			fin.close();
			if (is_dark_mode) {		// dark mode
				// text color
				TXT_main_text 			= TEXT_WHITE;
				TXT_highlight_text 		= TEXT_BLUE;
				TXT_cell_border 		= TEXT_MAGENTA;
				TXT_letter 				= TEXT_YELLOW;
				TXT_highlight_letter 	= TEXT_WHITE;
				TXT_path 				= TEXT_GREEN;
				TXT_button_drawing 		= TEXT_WHITE;
				TXT_button_text			= TEXT_PURPLE;
				TXT_button_highlight_text = TEXT_WHITE;

				// background color
				BG_main_bg 				= BG_BLACK;
				BG_cell_cursor 			= BG_CYAN;
				BG_cell_selected 		= BG_ORANGE;
				BG_cell_correct 		= BG_GREEN;
				BG_cell_wrong 			= BG_RED;
				BG_cell_hint 			= BG_GRAY;
				BG_button_selecting 	= BG_ORANGE;
				BG_title 				= BG_CYAN;


			}
			else {					// light mode
				// text color
				TXT_main_text 			= TEXT_BLACK;
				TXT_highlight_text 		= TEXT_BLUE;
				TXT_cell_border 		= TEXT_MAGENTA;
				TXT_letter 				= TEXT_BLUE;
				TXT_highlight_letter 	= TEXT_WHITE;
				TXT_path 				= TEXT_GREEN;
				TXT_button_drawing 		= TEXT_BLACK;
				TXT_button_text			= TEXT_PURPLE;
				TXT_button_highlight_text = TEXT_WHITE;

				// background color
				BG_main_bg 				= BG_WHITE;
				BG_cell_cursor 			= BG_CYAN;
				BG_cell_selected 		= BG_ORANGE;
				BG_cell_correct 		= BG_GREEN;
				BG_cell_wrong 			= BG_RED;
				BG_cell_hint 			= BG_GRAY;
				BG_button_selecting 	= BG_ORANGE;
				BG_title 				= BG_CYAN;
			}
		}
};

const game_color color = game_color();

//* box drawing
// single
const char HORIZONTAL_EDGE 		= 196;		// ─
const char VERTICAL_EDGE 		= 179;		// │
const char LEFT_DOWN_CORNER 	= 191;		// ┐
const char RIGHT_UP_CORNER 		= 192;		// └
const char LEFT_UP_CORNER 		= 217;		// ┘
const char RIGHT_DOWN_CORNER 	= 218;		// ┌

//double
const char D_HORIZONTAL_EDGE 	= 205;		// ═
const char D_VERTICAL_EDGE 		= 186;		// ║
const char D_LEFT_DOWN_CORNER 	= 187;		// ╗
const char D_RIGHT_UP_CORNER 	= 200;		// ╚
const char D_LEFT_UP_CORNER 	= 188;		// ╝
const char D_RIGHT_DOWN_CORNER 	= 201;		// ╔

Input getInput();
void goTo(SHORT x, SHORT y);
void changeTextColor(string bg_color, string text_color);
// BOOL SetConsoleFontSize(COORD dwFontSize);
void setupConsole();