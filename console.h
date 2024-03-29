#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

enum Input{
	INVALID = -2,
	ESCAPE = -1,
	ENTER = 0,
	UP = 1,
	LEFT = 2,
	DOWN = 3,
	RIGHT = 4,
	HINT = 5
};

//* keys
const char K_ESC = 27;
const char K_ENTER = 13;
const char K_W = 'W';   // up
const char K_w = 'w';   // up
const char K_A = 'A';   // left
const char K_a = 'a';   // left
const char K_S = 'S';   // down
const char K_s = 's';   // down
const char K_D = 'D';   // right
const char K_d = 'd';   // right

//* colors
// background
const string BG_BLACK = "\x1B[0m";     // for background in dark mode
const string BG_WHITE = "\x1B[107m";   // for background in light mode
const string BG_RED = "\x1B[41m";      // for wrong pair
const string BG_YELLOW = "\x1B[43m";   // for selected cell
const string BG_GREEN = "\x1B[42m";    // for correct pair
const string BG_CYAN = "\x1B[46m";     // for cursor
const string BG_GRAY = "\x1B[100m";    // for hint pair

// text
const string TEXT_GREEN = "\x1B[32m";  // for correct path
const string TEXT_BLUE = "\x1B[34m";   // for letters in light mode
const string TEXT_YELLOW = "\x1B[93m"; // for letters in dark mode
const string TEXT_MAGENTA = "\x1B[95m"; // for letters in dark mode
const string TEXT_WHITE = "\x1B[97m";  // for other characters and highlighted cell in dark mode
const string TEXT_BLACK = "\x1B[30m";  // for other characters in light mode

//* box drawing
// single
const char HORIZONTAL_EDGE = 196;      // ─
const char VERTICAL_EDGE = 179;        // │
const char LEFT_DOWN_CORNER = 191;     // ┐
const char RIGHT_UP_CORNER = 192;      // └
const char LEFT_UP_CORNER = 217;       // ┘
const char RIGHT_DOWN_CORNER = 218;    // ┌

//double
const char D_HORIZONTAL_EDGE = 205;      // ═
const char D_VERTICAL_EDGE = 186;        // ║
const char D_LEFT_DOWN_CORNER = 187;     // ╗
const char D_RIGHT_UP_CORNER = 200;      // ╚
const char D_LEFT_UP_CORNER = 188;       // ╝
const char D_RIGHT_DOWN_CORNER = 201;    // ╔

Input getInput();
void goTo(SHORT x, SHORT y);
void changeTextColor(const string bg_color, const string text_color);
// BOOL SetConsoleFontSize(COORD dwFontSize);