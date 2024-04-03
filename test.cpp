// #pragma comment(lib, "Winmm.lib")
// #include <iostream>
// #include <windows.h>
// #include <conio.h>
// #include <mmsystem.h>
// using namespace std;

// // // bool isCharAtPosition(SHORT x, SHORT y, char& character) {
// // //     COORD xy = { 0, 0 };
// // //     CHAR_INFO ci;
// // //     SMALL_RECT rect = { x, y, x, y };
// // //     if (ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, {1, 1}, xy, &rect)) {
// // //         character = ci.Char.AsciiChar;
// // //         return true;
// // //     }
// // //     return false;
// // // }

// void playSound(int sound) {
// 	PlaySoundA("move_cursor.mp3", NULL, SND_FILENAME | SND_ASYNC);
// 	// mciSendStringA("play \"move_cursor.mp3\"", NULL, 0, NULL);
// }

// int main() {
// 	// for (int i = 62; i < 120; i++) {
// 	// 	cout << char(i);
// 	// 	if (i % 10 == 0) cout << endl;
// 	// }
// 	// char c;
// 	// cout << endl << isCharAtPosition(2, 5, c);
// 	// cout << endl << c;


//     // ...
// 	playSound(1);
// 	_getch();

// 	return 0;
// }