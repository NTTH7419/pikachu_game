#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <math.h>
#include <time.h>

using namespace std;

enum Direction{
    UP = 0, RIGHT = 1, LEFT = 2, DOWN = 3, NEUTRAL = 4
};

struct Coordinate{
    int x;
    int y;

    bool operator==(const Coordinate &a) const{
        return (x == a.x && y == a.y);
    }

    bool operator!=(const Coordinate &a) const{
        return !(x == a.x && y == a.y);
    }

    Coordinate& operator=(const Coordinate &a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }

    Coordinate operator+(const Coordinate &a) const{
        Coordinate result;
        result.x = x + a.x;
        result.y = y + a.y;

        return result;
    }
};

//* Stack implementation
struct Node{
    Coordinate data;
    Node* pNext;
};

struct Stack{
    Node* pHead;
};

bool isStackEmpty(Stack stack);
void pop(Stack &stack);
void push(Stack &stack, Coordinate data);

bool findPath(char** display_board, int height, int width, Stack &stack, Coordinate start, Coordinate end);
bool findPathCall(int height, int width, bool** visited, Stack &stack, Direction cur_dir, short turn, Coordinate start, Coordinate end);

void printPath(Stack stack);