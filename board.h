#pragma once

#include "console.h"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <time.h>
#include <random>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

#define EASY 1
#define MEDIUM 2
#define HARD 3


//Defining the direction for path finding
enum Direction{
    NORTH = 0, EAST = 1, WEST = 2, SOUTH = 3, NEUTRAL = 4
};

//defining a vector to draw the path later on
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


//defining a struct Coordinate for convenience
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


//Defining the linked list for shifting
struct Node{
    char data;
    Node* next;
};


struct List{
    Node* pHead = NULL;
    Node* pTail = NULL;

    void addHead(char data){
        Node* pCur = new Node;
        pCur->data = data;
        pCur->next = pHead;
        pHead = pCur;
        if (pHead->next == NULL) pTail = pHead;
    }

    void printList(){
        Node* pCur = pHead;

        while(pCur){
            cout << pCur->data << " ";
            pCur = pCur->next;
        }
        cout << endl;
    }

    //TODO: moving the removed cell into the last of the list
    void remove(int index){
        Node* pPrev = NULL;
        Node* pTemp = pHead;
        while(index--){
            pPrev = pTemp;
            pTemp = pTemp->next;
        }
        pTemp->data = '#';

        if (pPrev) pPrev->next = pTemp->next;

        else pHead = pTemp->next;

        if (pTemp->next) pTail->next = pTemp;
        
        pTemp->next = NULL;
        pTail = pTemp;
    }
    

    char& operator[](int index){
        Node* pCur = pHead;

        while(index--){
            pCur = pCur->next;
        }

        return pCur->data;
    }

    void del(){
        while(pHead){
            Node* pCur = pHead;
            pHead = pHead->next;
            delete pCur;
        }
        pTail = NULL;
    }
};


//defining the 2D list for shifting
struct Node2D{
    List data;
    Node2D* next;
};


struct List2D{
    Node2D* pHead = NULL;
    Node2D* pTail = NULL;

    void addHead(List data){
        Node2D* pCur = new Node2D;
        pCur->data = data;
        pCur->next = pHead;
        pHead = pCur;
        if (pHead->next == NULL) pTail = pHead;
    }

    void printList(){
        Node2D* pCur = pHead;

        while(pCur){
            pCur->data.printList();
            pCur = pCur->next;
        }
        cout << endl;
    }

    List& operator[](int index){
        Node2D* pCur = pHead;

        while(index--){
            pCur = pCur->next;
        }

        return pCur->data;
    }

    void del(){
        while(pHead){
            Node2D* pCur = pHead;
            pHead = pHead->next;
            delete pCur;
        }
        pTail = pHead;
    }
};


//defining the board struct of the game
struct Board{
    //* board
 
    int height;
    int width;
    int distinct_letter; //number of distinct letters that can be picked 
    bool isArray;      //array implementation or linked list implementation

    char** letter_board;    // array board
    List2D list_board;      // linked list board
    string* background;
    string bg_info;

    //* display

    int cell_width = 10;
	int cell_height = 4;
    int x_offset;
    int y_offset;

    //TODO: setting the difficulty and allocate memory
    Board(int difficulty){
        if (difficulty == EASY) {
			height = 6;
			width = 8;
			distinct_letter = 15;
            isArray = true;
		}
		else if (difficulty == MEDIUM) {
			height = 8;
			width = 10;
			distinct_letter = 20;
            isArray = true;
		}
		else if (difficulty == HARD) {
			height = 8;
			width = 12;
			distinct_letter = 26;
            isArray = false;
		}

        //setting the offset of the board (centerize)
        x_offset = 30 + (141 - (cell_width * (width + 2) + 1)) / 2;
        y_offset = 1 + (41 - (cell_height * (height + 2) + 1)) / 2;

        if (isArray){   // allocate array
            letter_board = new char*[height + 2];
            for (int i = 0; i < height + 2; i++)
                letter_board[i] = new char[width + 2];

            for (int i = 0; i < height + 2; i++){
                for (int j = 0; j < width + 2; j++){
                    letter_board[i][j] = '#';
                }
            }
        }

        else{       // allocate linked list
            List temp;
            for (int i = 0; i < height + 2; i++){
                list_board.addHead(temp);
            }

            for (int i = 0; i < height + 2; i++){
                for (int j = 0; j < width + 2; j++){
                    list_board[i].addHead('#');
                }
            }
        }

        // load background
        background = new string[(height + 2) * cell_height + 1];
        loadBackground(difficulty);
    }

    ~Board(){
        if (isArray) {      // deallocate array
            for (int i = 0; i < height + 2; i++)
                delete[] letter_board[i];

            delete[] letter_board;
        }
        else {      // deallocate linked list
            for (int i = 0; i < height + 2; i++){
                list_board[i].del();
            }
            list_board.del();
        }
        delete[] background;


    }

    //TODO: Initializing the 2D array board
	void initBoard();

    //TODO: Loading the corresponding background
    void loadBackground(int difficulty);

    //TODO: Check if a point p is in the board
	bool isInBoard(Coordinate p);

    //TODO: debug function, print the array board into console
	void printBoard();

    //TODO: check if there is no more cells on the board
	bool isBoardEmpty();

    //TODO: initializing the linked list board
    void initListBoard();

    //TODO: debug function, print the linked list board into console
    void printList();

    //TODO: check if a point has been visited before
    bool isVisited(Coordinate point, vector<Coordinate> path);

    //TODO: path finding function using bfs
    bool bfs(Coordinate start, Coordinate end, vector<Coordinate> &path);

    //TODO: highlight the cell at position pos with color specified below
    void highlightCell(Coordinate pos, string bg_color, string text_color);

    //TODO: unhighlight the cell at position pos
    void unhighlightCell(Coordinate pos);

    //TODO: highlighting the cursor at pos
    void highlightCursor(Coordinate pos);

    //TODO: highlight the selected cell at pos
    void highlightSelected(Coordinate pos);

    //TODO: highlight the correct pair with green color
    void highlightCorrectPair(Coordinate pos1, Coordinate pos2);

    //TODO: highlight the wrong pair with red color
    void highlightWrongPair(Coordinate pos1, Coordinate pos2);

    //TODO: highlight the hinted pair with color purple
    void highlightHintPair(Coordinate pos1, Coordinate pos2);

    //TODO: get the letter of the array board or the linked list board
    char getLetter(Coordinate pos);

    //TODO: check if the letter is not 
    bool isValid(Coordinate pos);

    //TODO: display the letter in the terminal
    void displayLetter();

    //TODO: display the board in the terminal
    void displayBoard();

    //TODO: remove a cell at position pos
    void removeCell(Coordinate pos);

    //TODO: draw the path between the two valid cells
    queue<Coordinate> drawPath(vector<Coordinate> path);

    //TODO: delete the path after displaying
    void deletePath(queue<Coordinate> drawn_pixels);

    //TODO: animating the shuffle effect
    void animateShuffle();
};
