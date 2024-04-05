#pragma once
#pragma comment(lib, "Winmm.lib")

#include <iostream>
#include <windows.h>	// for console configuaration and playing sound
#include <conio.h>		// for get input
#include <string>
#include <fstream>
#include <mmsystem.h>

using namespace std;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define CONSOLE_WIDTH 172
#define CONSOLE_HEIGHT 42

#define SFX_CORRECT 1
#define SFX_WRONG 2
#define SFX_SELECT 3
#define SFX_MOVE_CURSOR 4
#define SFX_WIN 5
#define SFX_START_GAME 6

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

struct Colors {

	// text color
	static string TXT_main_text;
	static string TXT_cell_border;
	static string TXT_letter;
	static string TXT_highlight_letter;
	static string TXT_path;
	static string TXT_button_drawing;
	static string TXT_button_text;
	static string TXT_button_highlight_text;

	static string TXT_blue;

	// background color
	static string BG_main_bg;
	static string BG_cell_cursor;
	static string BG_cell_selected;
	static string BG_cell_correct;
	static string BG_cell_wrong;
	static string BG_cell_hint;
	static string BG_button_selecting;
	static string BG_title;
};


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

//TODO: get player input
Input getInput();

//TODO: moving the cursor to a desired position
void goTo(SHORT x, SHORT y);

//TODO: change the text color
void changeTextColor(string bg_color, string text_color);

//TODO: draw the box of an object on console
void drawBox(int x, int y, int width, int height);

//TODO: get the charactet at a position
char getCharAtPosition(SHORT x, SHORT y);

//TODO: play sound effect
void playSFX(int sound);

//TODO: hide/show the cursor
void setCursorAppearance(bool show);

//TODO: disabling windows terminal resizing
void disableMaximizeConsole();

//TODO: resizing and positioning the window console
void setConsoleWindow();

//TODO: disable the mouse input from the player
void disableMouseInput();

//TODO: set the console title
void setConsoleTitle();

//TODO: setting up the windows terminal
void setupConsole();