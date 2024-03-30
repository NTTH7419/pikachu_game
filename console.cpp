#include "console.h"

Input getInput() {
	char inp = _getch();
	if (inp == K_ESC) return Input::ESCAPE;
	if (inp == K_ENTER) return Input::ENTER;
	if (inp == K_W || inp == K_w) return Input::UP;
	if (inp == K_A || inp == K_a) return Input::LEFT;
	if (inp == K_S || inp == K_s) return Input::DOWN;
	if (inp == K_D || inp == K_d) return Input::RIGHT;
	if (inp == K_H || inp == K_h) return Input::HINT;
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

// BOOL SetConsoleFontSize(COORD dwFontSize){
//     HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
//     CONSOLE_FONT_INFOEX info{sizeof(CONSOLE_FONT_INFOEX)};
//     if (!GetCurrentConsoleFontEx(output, false, &info))
//         return false;
//     info.dwFontSize = dwFontSize;
//     return SetCurrentConsoleFontEx(output, false, &info);
// }

void setupConsole() {
	ifstream fin;
	bool is_dark_mode;
	fin.open("settings.txt");
	fin >> is_dark_mode;
	fin.close();
	if (is_dark_mode) system("color 0f");
	else system("color f0");
	
	cout << "\33[?25l";	// hide console cursor
}