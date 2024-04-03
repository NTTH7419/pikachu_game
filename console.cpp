#include "console.h"

HWND console = GetConsoleWindow();

Input getInput() {
	char inp = _getch();
	if (inp == K_ESC) return Input::ESCAPE;
	if (inp == K_ENTER) return Input::ENTER;
	if (inp == K_W || inp == K_w) return Input::UP;
	if (inp == K_A || inp == K_a) return Input::LEFT;
	if (inp == K_S || inp == K_s) return Input::DOWN;
	if (inp == K_D || inp == K_d) return Input::RIGHT;
	if (inp == K_H || inp == K_h) return Input::HINT;
	if (inp == K_R || inp == K_r) return Input::SHUFFLE;
	return Input::INVALID;	// other input
}

void goTo(SHORT x, SHORT y) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = x;
    Position.Y = y;

	SetConsoleCursorPosition(hStdout, Position);
}


// change background and text color
void changeTextColor(string bg_color, string text_color) {
	cout << bg_color << text_color;
}

void setTextBold() {
	cout << "\33[1m";
}

void setTextNormal() {
	cout << "\33[0m";
}

void drawBox(int x, int y, int width, int height) {
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
}

void setCursorAppearance(bool show) {
	if (show)
		cout << "\33[?25h";	// show cursor
	else
		cout << "\33[?25l";	// hide cursor
}

// set console size, need Adminstrator
void setConsoleWindow() {
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, r.left, r.top, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
}

void disableMaximizeConsole() {
	DWORD style = GetWindowLong(console, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(console, GWL_STYLE, style);
}

void hideScrollBar() {
	// ShowScrollBar(console, SB_BOTH, 1);
	EnableScrollBar(console, SB_BOTH, ESB_DISABLE_BOTH);
}

void setConsoleTitle() {
	SetConsoleTitleA("Pikachu++");
}

Colors::Colors() {
	bool is_dark_mode;
	ifstream fin("settings.txt");
	fin >> is_dark_mode;
	fin.close();
	if (is_dark_mode) {		// dark mode
		system("color 0f");	// black background
		// text color
		TXT_main_text 			= TEXT_WHITE;
		TXT_cell_border 		= TEXT_MAGENTA;
		TXT_letter 				= TEXT_YELLOW;
		TXT_highlight_letter 	= TEXT_WHITE;
		TXT_path 				= TEXT_GREEN;
		TXT_button_drawing 		= TEXT_WHITE;
		TXT_button_text			= TEXT_PURPLE;
		TXT_button_highlight_text = TEXT_WHITE;
		TXT_red 				= TEXT_RED;
		TXT_blue 				= TEXT_LIGHT_BLUE;

		// background color
		BG_main_bg 				= BG_BLACK;
		BG_cell_cursor 			= BG_CYAN;
		BG_cell_selected 		= BG_ORANGE;
		BG_cell_correct 		= BG_GREEN;
		BG_cell_wrong 			= BG_RED;
		BG_cell_hint 			= BG_PURPLE;
		BG_button_selecting 	= BG_ORANGE;
		BG_title 				= BG_CYAN;


	}
	else {					// light mode
		system("color f0");	// white background
		// text color
		TXT_main_text 			= TEXT_BLACK;
		TXT_cell_border 		= TEXT_MAGENTA;
		TXT_letter 				= TEXT_DARK_RED;
		TXT_highlight_letter 	= TEXT_WHITE;
		TXT_path 				= TEXT_GREEN;
		TXT_button_drawing 		= TEXT_BLACK;
		TXT_button_text			= TEXT_PURPLE;
		TXT_button_highlight_text = TEXT_WHITE;
		TXT_red = TEXT_RED;
		TXT_blue = TEXT_BLUE;

		// background color
		BG_main_bg 				= BG_WHITE;
		BG_cell_cursor 			= BG_CYAN;
		BG_cell_selected 		= BG_ORANGE;
		BG_cell_correct 		= BG_GREEN;
		BG_cell_wrong 			= BG_RED;
		BG_cell_hint 			= BG_PURPLE;
		BG_button_selecting 	= BG_ORANGE;
		BG_title 				= BG_CYAN;
	}
}

void setupConsole() {
	setConsoleWindow();
	hideScrollBar();
	disableMaximizeConsole();
	setConsoleTitle();
	setCursorAppearance(false);	// hide console cursor
}