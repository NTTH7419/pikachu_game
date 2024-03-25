#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <math.h>
#include <time.h>
#include <vector>
#include <queue>

using namespace std;



//* keys
const char K_ESC = 27;
const char K_ENTER = 13;
const char K_W = 'W';   // up
const char K_w = 'w';   // up
const char K_A = 'A';   // left
const char K_a = 'a';   // left
const char K_S = 'S';   // down
const char K_s = 's';   // down
const char K_D = 'D';   // right
const char K_d = 'd';   // right

//* colors
// background
const string BG_BLACK = "\x1B[0m";     // for background in dark mode
const string BG_WHITE = "\x1B[107m";   // for background in light mode
const string BG_RED = "\x1B[41m";      // for wrong pair
const string BG_YELLOW = "\x1B[43m";   // for selected cell
const string BG_GREEN = "\x1B[42m";    // for correct pair
const string BG_CYAN = "\x1B[46m";     // for cursor
const string BG_GRAY = "\x1B[100m";    // for hint pair

// text
const string TEXT_GREEN = "\x1B[32m";  // for correct
const string TEXT_BLUE = "\x1B[34m";   // for letters in light mode
const string TEXT_YELLOW = "\x1B[93m"; // for letters in dark mode
const string TEXT_WHITE = "\x1B[97m";  // for other characters and highlighted cell in dark mode
const string TEXT_BLACK = "\x1B[30m";  // for other characters in light mode

//* box drawing
const char HORIZONTAL_EDGE = 196;      // ─
const char VERTICAL_EDGE = 179;        // │
const char LEFT_DOWN_CORNER = 191;     // ┐
const char RIGHT_UP_CORNER = 192;      // └
const char LEFT_UP_CORNER = 217;       // ┘
const char RIGHT_DOWN_CORNER = 218;    // ┌




enum Direction{
    UP = 0, RIGHT = 1, LEFT = 2, DOWN = 3, NEUTRAL = 4
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


//* Queue Implementation
struct Node{
    Coordinate data;
    Node* pNext;
};

struct Queue{
    Node* pHead = NULL;
    Node* pTail = NULL;
};

void push(Queue &queue, Coordinate data);
void pop(Queue &queue);
bool isQueueEmpty(Queue queue);
void printQueue(Queue queue);
Coordinate front(Queue queue);






struct board{
    //* board

    char** letter_board;
    int height;
    int width;


    //* display

    int cell_width = 3;
	int cell_height = 1;
    int x_offset = 0;
    int y_offset = 0;

    board(int height, int width){
        this->height = height;
        this->width = width;

        this->letter_board = new char*[height + 2];
        for (int i = 0; i < height + 2; i++)
            this->letter_board[i] = new char[width + 2];
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
    bool findPath(Queue &path, Coordinate start, Coordinate end);

    bool isVisited(Coordinate point, vector<Coordinate> path);
    bool bfs(Coordinate start, Coordinate end, vector<Coordinate> &path);
    bool match(Coordinate first, Coordinate second, vector<Coordinate> &path);

	void moveCursor(Coordinate &cur, int inp);
    void highlightPos(Coordinate pos, const string bg_color, const string text_color);
    void unhighlightPos(Coordinate pos);
    void displayBoard();
    void removeCell(Coordinate pos);
    void drawPath(vector<Coordinate> path);
    void gameLoop();
};

int getInput();
void goTo(SHORT x, SHORT y);
void changeTextColor(const string bg_color, const string text_color);