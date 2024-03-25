// #include <iostream>
// #include <windows.h>
// #include <conio.h>
// #include <stdlib.h>
// #include <string>
// #include <cstring>
// #include <math.h>
// #include <time.h>

// using namespace std;

// enum Direction{
//     UP = 0, RIGHT = 1, LEFT = 2, DOWN = 3, NEUTRAL = 4
// };

// struct Vector {
//     int x;
//     int y;

//     bool operator==(const Vector &a) const{
//         return (x == a.x && y == a.y);
//     }

//     bool operator!=(const Vector &a) const{
//         return !(x == a.x && y == a.y);
//     }
// };

// struct Coordinate{
//     int x;
//     int y;

//     bool operator==(const Coordinate &a) const{
//         return (x == a.x && y == a.y);
//     }

//     bool operator!=(const Coordinate &a) const{
//         return !(x == a.x && y == a.y);
//     }

//     Coordinate& operator=(const Coordinate &a)
//     {
//         x = a.x;
//         y = a.y;
//         return *this;
//     }

//     Coordinate operator+(const Coordinate &a) const{
//         Coordinate result;
//         result.x = x + a.x;
//         result.y = y + a.y;

//         return result;
//     }

//     Vector operator-(const Coordinate &a) const{
//         Vector result;
//         result.x = x - a.x;
//         result.y = y - a.y;

//         return result;
//     }
// };

// //* Stack implementation
// struct Node{
//     Coordinate data;
//     Node* pNext;
// };

// struct Stack{
//     Node* pHead = NULL;
// };

// bool isStackEmpty(Stack stack);
// bool pop(Stack &stack, Coordinate &data);
// void push(Stack &stack, Coordinate data);

// //* Queue Implementation

// struct Queue{
//     Node* pHead = NULL;
//     Node* pTail = NULL;
// };

// void push(Queue &queue, Coordinate data);
// void pop(Queue &queue);
// bool isQueueEmpty(Queue queue);
// void printQueue(Queue queue);
// Coordinate front(Queue queue);

// //* back end
// bool findPath(char** display_board, int height, int width, Queue &path, Coordinate start, Coordinate end);
// bool findPathCall(int height, int width, bool** visited, Stack &stack, Direction cur_dir, short turn, Coordinate start, Coordinate end);
// void printPath(Stack stack);

// //* front end
// bool isInGameBoard(int height, int width, Coordinate pos);
// char** createGameBoard(int height, int width);
// void printGameBoard(char** game_board, int height, int width);
// void deleteGameBoard(char** &game_board, int height, int width);
// int getInput();
// void moveCursor(Coordinate &cur, int inp, int height, int width);
// void highlightPos(string* display_board, int height, int width, Coordinate pos);
// void dehighlightPos(string* display_board, int height, int width, Coordinate pos);
// string* createDisplayBoard(char** game_board, int height, int width);
// bool deleteDisplayBoardAtPos(char** game_board, string* display_board, int height, int width, Coordinate pos);
// void printDisplayBoard(string* display_board, int height);
// void copyDisplayBoard(string* display_board, string* display_board_path, int height);
// void drawPath(string* display_board_path, int height, int width, Queue &q);
// void gameLoop(char** game_board, string* display_board, int height, int width);
