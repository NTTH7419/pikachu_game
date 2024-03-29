#include "console.h"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <math.h>
#include <time.h>
#include <random>
#include <vector>
#include <queue>

using namespace std;

enum Direction{
    NORTH = 0, EAST = 1, WEST = 2, SOUTH = 3, NEUTRAL = 4
};

struct Vector {
    int x;
    int y;

    bool operator==(const Vector &a) const{
        return (x == a.x && y == a.y);
    }

    bool operator!=(const Vector &a) const{
        return !(x == a.x && y == a.y);
    }
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

    Vector operator-(const Coordinate &a) const{
        Vector result;
        result.x = x - a.x;
        result.y = y - a.y;

        return result;
    }
};





struct board{
    //* board

    char** letter_board;
    int height;
    int width;


    //* display

    int cell_width = 4;
	int cell_height = 2;
    int x_offset = 0;
    int y_offset = 0;

    board(int height, int width){
        this->height = height;
        this->width = width;

        this->letter_board = new char*[height + 2];
        for (int i = 0; i < height + 2; i++)
            this->letter_board[i] = new char[width + 2] {'\0'};
    }

    ~board(){
        for (int i = 0; i < this->height + 2; i++)
            delete[] this->letter_board[i];

        delete[] this->letter_board;

    }

	void init();
	bool isInBoard(Coordinate p);
	void printBoard();
	bool isBoardEmpty();

    bool isVisited(Coordinate point, vector<Coordinate> path);
    bool bfs(Coordinate start, Coordinate end, vector<Coordinate> &path);
    bool match(Coordinate first, Coordinate second, vector<Coordinate> &path);

	void moveCursor(Coordinate &cur, Input inp);
    void highlightPos(Coordinate pos, const string bg_color, const string text_color);
    void unhighlightPos(Coordinate pos);
    void displayBoard();
    void removeCell(Coordinate pos);
    queue<Coordinate> drawPath(vector<Coordinate> path);
    void deletePath(queue<Coordinate> drawn_pixels);
    void gameLoop();
};
