#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define CONSOLE_WIDTH 172
#define CONSOLE_HEIGHT 42

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
const char K_BACKSPACE = 8;
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
const char K_R		= 'R';		// shuffle
const char K_r		= 'r';		// shuffle



struct Colors {
	// background
	const string BG_BLACK 		= "\33[0m";     		// for background in dark mode
	const string BG_WHITE 		= "\33[107m";   		// for background in light mode
	const string BG_RED 		= "\33[41m";      		// for wrong pair
	const string BG_YELLOW 		= "\33[43m";			// for title
	const string BG_ORANGE 		= "\33[48;5;208m";		// for selected cell
	const string BG_GREEN 		= "\33[42m";    		// for correct pair
	const string BG_CYAN 		= "\33[46m";     		// for cursor
	const string BG_PURPLE 		= "\33[48;5;93m";   	// for hint pair
	const string BG_PINK	 	= "\33[48;5;199m";		// for shuffle animation

	// text
	const string TEXT_RED		= "\33[31m";
	const string TEXT_GREEN 	= "\33[32m";  			// for correct path
	const string TEXT_BLUE 		= "\33[34m";   			// for letters in light mode
	const string TEXT_LIGHT_BLUE = "\33[38;5;33m";
	const string TEXT_YELLOW 	= "\33[33m"; 			// for letters in dark mode
	const string TEXT_DARK_RED 	= "\33[38;5;88m";
	const string TEXT_ORANGE 	= "\33[38;5;208m";
	const string TEXT_PURPLE	= "\33[38;5;93m";		// for button text
	const string TEXT_MAGENTA 	= "\33[95m"; 			// for cell border
	const string TEXT_WHITE 	= "\33[97m";  			// for other characters and highlighted cell in dark mode
	const string TEXT_BLACK 	= "\33[30m";  			// for other characters in light mode
	const string TEXT_PINK	 	= "\33[38;5;199m";

	// text color
	string TXT_main_text;
	string TXT_cell_border;
	string TXT_letter;
	string TXT_highlight_letter;
	string TXT_path;
	string TXT_button_drawing;
	string TXT_button_text;
	string TXT_button_highlight_text;

	string TXT_blue;
	string TXT_red;

	// background color
	string BG_main_bg;
	string BG_cell_cursor;
	string BG_cell_selected;
	string BG_cell_correct;
	string BG_cell_wrong;
	string BG_cell_hint;
	string BG_button_selecting;
	string BG_title;

	Colors();
};

const Colors colors = Colors();


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
void setTextBold();
void setTextNormal();
void drawBox(int x, int y, int width, int height);

void setCursorAppearance(bool show);
void disableMaximizeConsole();
void setConsoleWindow();
void hideScrollBar();
void setConsoleTitle();
void setupConsole();