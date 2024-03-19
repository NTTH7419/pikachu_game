#include "pikachu.h"

void pop(Stack &stack){
    if (stack.pHead){
        Node* pCur = stack.pHead->pNext;
        delete stack.pHead;
        stack.pHead = pCur;
    }
}

void push(Stack &stack, Coordinate data){
    Node* pCur = new Node;
    pCur->data = data;
    pCur->pNext = stack.pHead;
    stack.pHead = pCur;
}

bool isStackEmpty(Stack stack){
    return !stack.pHead;
}

char** createDisplayBoard(int height = 5, int width = 5){
    srand(time(NULL));
    char** display_board = new char*[height + 2];

    for (int i = 0; i < height + 2; i++)
        display_board[i] = new char[width + 2] {'\0'};

    for (int i = 1; i <= height; i++){
        for (int j = 1; j <= width; j++)
            display_board[i][j] = rand() % 5 + 65;
    }

    return display_board;
}

void printDisplayBoard(char** board, int height, int width){
    for (int i = 0; i < height + 2; i++){
        for (int j = 0; j < width + 2; j++)
            cout << board[i][j] << " ";    
        cout << endl;
    }
    cout << endl;
}

void removePiece(char** &board, Coordinate first, Coordinate second){
    board[first.y][first.x] = '\0';
    board[second.y][second.x] = '\0';
}

bool findPathCall(int height, int width, bool** visited, Stack &stack, Direction cur_dir, short turn, Coordinate start, Coordinate end){
    push(stack, start);

    // cout << endl;
    // for (int i = 0; i < height + 2; i++){
    //     for (int j = 0; j < width + 2; j++){
    //         cout << visited[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    if (start == end) return 1;

    Coordinate direction[] = {
        {0, -1},     //up
        {1, 0},     //right
        {-1, 0},    //left
        {0, 1}     //down
    };

    
    for (int i = 0; i < 4; i++){
        Coordinate next_point = start + direction[i];
        //Check if the next point is a valid point to move to
        if (                
            0 <= next_point.y && next_point.y < height + 2 &&
            0 <= next_point.x && next_point.x < width + 2 &&
            !visited[next_point.y][next_point.x]
        ){
            Direction next_dir = (Direction)i;

            if (cur_dir != NEUTRAL && cur_dir != next_dir){
                if (turn == 2) continue;

                else{
                    visited[next_point.y][next_point.x] = true;
                    if (findPathCall(height, width, visited, stack, next_dir, turn + 1, next_point, end)) {
                        return 1;
                    }
                }
            }

            else{
                visited[next_point.y][next_point.x] = true;
                if (findPathCall(height, width, visited, stack, next_dir, turn, next_point, end)){
                    return 1;  
                } 
            }
        }
    }

    pop(stack);
    visited[start.y][start.x] = false;

    return 0;
}

bool findPath(char** game_board, int height, int width, Stack &stack, Coordinate start, Coordinate end){
    bool** visited = new bool*[height + 2];
    for (int i = 0; i < height + 2; i++)
        visited[i] = new bool[width + 2] {false};
    for (int i = 0; i < height + 2; i++){
        for (int j = 0; j < width + 2; j++){
            visited[i][j] = game_board[i][j] != '\0';
        }
    }

    visited[end.y][end.x] = false;

    // for (int i = 0; i < row + 2; i++){
    //     for (int j = 0; j < col + 2; j++){
    //         cout << visited[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    if (findPathCall(height, width, visited, stack, NEUTRAL, 0, start, end)){
        //cout << isStackEmpty(stack) << endl;
        return 1;
    }
    return 0;
}

void printPath(Stack stack){
    while(stack.pHead){
        cout << stack.pHead->data.x << " " << stack.pHead->data.y << endl;
        stack.pHead = stack.pHead->pNext;
    }
}

// Coordinate getInput(){
//     Coordinate input;
//     cin >> input.x >> input.y;

//     return input;
// }

// int main(){
//     int row = 30;
//     int col = 30;
//     char** display_board = createDisplayBoard(row, col);
//     printDisplayBoard(display_board, row ,col);


//     // Coordinate first = {1, 1};
//     // Coordinate second = {49, 48};
//     Stack stack;
//     stack.pHead = NULL;

//     // display_board[2][1] = '\0';
//     // display_board[2][2] = '\0';
//     // display_board[2][3] = '\0';
//     // display_board[2][4] = '\0';
//     // display_board[3][4] = '\0';

//     // findPath(display_board, row, col, stack, first, second);
//     // printPath(stack);
//     //cout << isStackEmpty(stack);

//     while(true){
//         Coordinate start = getInput();
//         if (start.x == 69) break;
//         Coordinate end = getInput();

//         if (display_board[start.y][start.x] == display_board[end.y][end.x]
//             && display_board[start.y][start.x] != '\0'
//             && !(start == end)
//         ){
//             if (findPath(display_board, row, col, stack, start, end)){
//                 removePiece(display_board, start, end);
//             }
//         }
//         printDisplayBoard(display_board, row, col);
//         cout << endl;
//         printPath(stack);
//     }

//     for (int i = 0; i < 5 + 2; i++){
//         delete [] display_board[i];
//     }
//     delete [] display_board;


//     return 0;
// }