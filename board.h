#pragma once

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

#define EASY 1
#define MEDIUM 2
#define HARD 3

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


struct Board{
    //* board

    char** letter_board;
    int height;
    int width;
    int distinct_letter;

    string* background;
    string bg_info;

    //* display

    int cell_width = 10;
	int cell_height = 4;
    int x_offset;
    int y_offset;

    Board(int difficulty){
        if (difficulty == EASY) {
			height = 6;
			width = 8;
			distinct_letter = 15;
		}
		else if (difficulty == MEDIUM) {
			height = 8;
			width = 10;
			distinct_letter = 20;
		}
		else if (difficulty == HARD) {
			height = 8;
			width = 12;
			distinct_letter = 26;
		}
        x_offset = 30 + (141 - (cell_width * (width + 2) + 1)) / 2;
        y_offset = 1 + (41 - (cell_height * (height + 2) + 1)) / 2;

        letter_board = new char*[height + 2];
        for (int i = 0; i < height + 2; i++)
            letter_board[i] = new char[width + 2] {'\0'};

        background = new string[(height + 2) * cell_height + 1];
        loadBackground(difficulty);
    }

    ~Board(){
        for (int i = 0; i < height + 2; i++)
            delete[] letter_board[i];

        delete[] letter_board;
        delete[] background;
    }

	void initBoard();
    void loadBackground(int difficulty);
	bool isInBoard(Coordinate p);
	void printBoard();
	bool isBoardEmpty();

    bool isVisited(Coordinate point, vector<Coordinate> path);
    bool bfs(Coordinate start, Coordinate end, vector<Coordinate> &path);

    void highlightCell(Coordinate pos, string bg_color, string text_color);
    void unhighlightCell(Coordinate pos);
    void highlightCursor(Coordinate pos);
    void highlightSelected(Coordinate pos);
    void highlightCorrectPair(Coordinate pos1, Coordinate pos2);
    void highlightWrongPair(Coordinate pos1, Coordinate pos2);
    void highlightHintPair(Coordinate pos1, Coordinate pos2);

    char getLetter(Coordinate pos);
    bool isValid(Coordinate pos);

    void displayLetter();
    void displayBoard();
    void removeCell(Coordinate pos);
    queue<Coordinate> drawPath(vector<Coordinate> path);
    void deletePath(queue<Coordinate> drawn_pixels);
    void animateShuffle();
};
