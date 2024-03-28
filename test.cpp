#include <iostream>
#include <windows.h>

using namespace std;

bool isCharAtPosition(SHORT x, SHORT y, char& character) {
    COORD xy = { 0, 0 };
    CHAR_INFO ci;
    SMALL_RECT rect = { x, y, x, y };
    if (ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, {1, 1}, xy, &rect)) {
        character = ci.Char.AsciiChar;
        return true;
    }
    return false;
}

// int main() {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     SMALL_RECT windowSize = {0, 0, 720, 720}; // Set the desired width (79) and height (24)

//     SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
// 	int a;
//     cout << "Hello World";
// 	cin >> a;

//     return 0;
// }

// int main() {
// 	for (int i = 0; i < 256; i++) {
// 		cout << i << ' ' << char(i) << endl;
// 	}


// 	return 0;
// }
