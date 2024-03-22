#include "pikachu.h"

struct board{
    char** letter_board;
    int height;
    int width;

    board(int height, int width){
        this->height = height;
        this->width = width;

        this->letter_board = new char*[height];
        for (int i = 0; i < height; i++)
            this->letter_board[i] = new char[width];
    }
};