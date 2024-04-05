#include "console.h"

string Colors::TXT_main_text;
string Colors::TXT_cell_border;
string Colors::TXT_letter;
string Colors::TXT_highlight_letter;
string Colors::TXT_path;
string Colors::TXT_button_drawing;
string Colors::TXT_button_text;
string Colors::TXT_button_highlight_text;
string Colors::TXT_blue;
string Colors::BG_main_bg;
string Colors::BG_cell_cursor;
string Colors::BG_cell_selected;
string Colors::BG_cell_correct;
string Colors::BG_cell_wrong;
string Colors::BG_cell_hint;
string Colors::BG_button_selecting;
string Colors::BG_title;


HWND console = GetConsoleWindow();
bool is_dark_mode, is_sound_on;

//TODO: getting the input from the player
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
	if(!is_sound_on) {		// if sound off
		if (sound == SFX_CORRECT || sound == SFX_WRONG) {
			Sleep(300);
		}
		return;
	}
	switch (sound)	{
		case SFX_MOVE_CURSOR:
			PlaySoundA("sfx\\move_cursor.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		
		case SFX_CORRECT:
			PlaySoundA("sfx\\correct.wav", NULL, SND_FILENAME | SND_SYNC);
			break;
		
		case SFX_WRONG:
			PlaySoundA("sfx\\wrong.wav", NULL, SND_FILENAME | SND_SYNC);
			Sleep(100);
			break;

		case SFX_SELECT:
			PlaySoundA("sfx\\select.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;

		case SFX_WIN:
			PlaySoundA("sfx\\win.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;

		case SFX_START_GAME:
			PlaySoundA("sfx\\game_start.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;

		default:
			break;
	}
}



void setCursorAppearance(bool show) {
	if (show)
		cout << "\33[?25h";	// show cursor
	else
		cout << "\33[?25l";	// hide cursor
}


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

void setColors() {
	bool is_dark_mode;
	ifstream fin("settings.txt");
	fin >> is_dark_mode;
	fin.close();
	if (is_dark_mode) {		// dark mode
		system("color 0f");	// black background
		// text color
		Colors::TXT_main_text 			= TEXT_WHITE;
		Colors::TXT_cell_border 		= TEXT_MAGENTA;
		Colors::TXT_letter 				= TEXT_YELLOW;
		Colors::TXT_highlight_letter 	= TEXT_WHITE;
		Colors::TXT_path 				= TEXT_GREEN;
		Colors::TXT_button_drawing 		= TEXT_WHITE;
		Colors::TXT_button_text			= TEXT_PURPLE;
		Colors::TXT_button_highlight_text = TEXT_WHITE;
		Colors::TXT_blue 				= TEXT_LIGHT_BLUE;

		// background color
		Colors::BG_main_bg 				= BG_BLACK;
		Colors::BG_cell_cursor 			= BG_CYAN;
		Colors::BG_cell_selected 		= BG_ORANGE;
		Colors::BG_cell_correct 		= BG_GREEN;
		Colors::BG_cell_wrong 			= BG_RED;
		Colors::BG_cell_hint 			= BG_PURPLE;
		Colors::BG_button_selecting 	= BG_ORANGE;
		Colors::BG_title 				= BG_CYAN;


	}
	else {					// light mode
		system("color f0");	// white background
		// text color
		Colors::TXT_main_text 			= TEXT_BLACK;
		Colors::TXT_cell_border 		= TEXT_MAGENTA;
		Colors::TXT_letter 				= TEXT_DARK_RED;
		Colors::TXT_highlight_letter 	= TEXT_WHITE;
		Colors::TXT_path 				= TEXT_GREEN;
		Colors::TXT_button_drawing 		= TEXT_BLACK;
		Colors::TXT_button_text			= TEXT_PURPLE;
		Colors::TXT_button_highlight_text = TEXT_WHITE;
		Colors::TXT_blue 				= TEXT_BLUE;

		// background color
		Colors::BG_main_bg 				= BG_WHITE;
		Colors::BG_cell_cursor 			= BG_CYAN;
		Colors::BG_cell_selected 		= BG_ORANGE;
		Colors::BG_cell_correct 		= BG_GREEN;
		Colors::BG_cell_wrong 			= BG_RED;
		Colors::BG_cell_hint 			= BG_PURPLE;
		Colors::BG_button_selecting 	= BG_ORANGE;
		Colors::BG_title 				= BG_CYAN;
	}
}

void setupConsole() {
	ifstream fin("settings.txt");
	fin >> is_dark_mode >> is_sound_on;
	fin.close();

	setColors();
	setConsoleWindow();
	disableMouseInput();
	disableMaximizeConsole();
	setConsoleTitle();
	setCursorAppearance(false);	// hide console cursor
}