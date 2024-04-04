#include "console.h"

HWND console = GetConsoleWindow();
bool is_dark_mode, is_sound_on;

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

char getCharAtPosition(SHORT x, SHORT y) {
	char c;
    COORD xy = {0, 0};
    CHAR_INFO ci;
    SMALL_RECT rect = { x, y, x, y };
    if (ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, {1, 1}, xy, &rect)) {
        c = ci.Char.AsciiChar;
        return c;
    }
    return ' ';
}

void playSFX(int sound) {
	if(!is_sound_on) return;	// if sound off
	if (sound == SFX_MOVE_CURSOR)
		PlaySoundA("move_cursor.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (sound == SFX_CORRECT)
		PlaySoundA("correct.wav", NULL, SND_FILENAME | SND_SYNC);
	else if (sound == SFX_WRONG)
		PlaySoundA("wrong.wav", NULL, SND_FILENAME | SND_SYNC);
	else if (sound == SFX_SELECT)
		PlaySoundA("select.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (sound == SFX_WIN)
		PlaySoundA("win.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (sound == SFX_START_GAME)
		PlaySoundA("game_start.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void setCursorAppearance(bool show) {
	if (show)
		cout << "\33[?25h";	// show cursor
	else
		cout << "\33[?25l";	// hide cursor
}

// set console size, need Adminstrator
void setConsoleWindow() {
    MoveWindow(console, 100, 50, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
}

void disableMaximizeConsole() {
	DWORD style = GetWindowLong(console, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(console, GWL_STYLE, style);
}

void disableMouseInput() {
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode); 
	SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
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
	ifstream fin("settings.txt");
	fin >> is_dark_mode >> is_sound_on;
	fin.close();

	setConsoleWindow();
	disableMouseInput();
	disableMaximizeConsole();
	setConsoleTitle();
	setCursorAppearance(false);	// hide console cursor
}