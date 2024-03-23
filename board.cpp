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

    ~board(){
        for (int i = 0; i < this->height; i++)
            delete this->letter_board[i];

        delete this->letter_board;

    }

    bool isInGameBoard(Coordinate p){
        return (p.y < this->height && p.y >= 0 && p.x < this->width && p.x >= 0);
    }

    void printBoard(){
        for (int i = 0; i < this->height; i++){
            for (int j = 0; j < this->width; j++){
                cout << this->letter_board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isBoardEmpty(){
        for (int i = 0; i < this->height; i++){
            for (int j = 0; j < this->width; j++){
                if (this->letter_board[i][j] != 0) return 0;
            }
        }
        return 1;
    }

    

};