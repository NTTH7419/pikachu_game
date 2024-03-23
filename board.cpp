#include "pikachu.h"

struct board{
    char** letter_board;
    int height;
    int width;

    board(int height, int width){
        this->height = height;
        this->width = width;

        this->letter_board = new char*[height + 2];
        for (int i = 0; i < height; i++)
            this->letter_board[i] = new char[width + 2];
    }

    ~board(){
        for (int i = 0; i < this->height + 2; i++)
            delete this->letter_board[i];

        delete this->letter_board;

    }

    bool isInGameBoard(Coordinate p){
        return (p.y < this->height + 1 && p.y >= 1 && p.x < this->width + 1 && p.x >= 1);
    }

    void printBoard(){
        for (int i = 0; i < this->height + 2; i++){
            for (int j = 0; j < this->width + 2; j++){
                cout << this->letter_board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isBoardEmpty(){
        for (int i = 1; i < this->height + 1; i++){
            for (int j = 1; j < this->width + 1; j++){
                if (this->letter_board[i][j] != 0) return 0;
            }
        }
        return 1;
    }



};