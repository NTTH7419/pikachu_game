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

bool isQueueEmpty(Queue queue){
    return !queue.pHead;
}

void push(Queue &queue, Coordinate data){
    Node* pCur = new Node;

    pCur->data = data;
    pCur->pNext = NULL;

    if (queue.pTail){
        queue.pTail->pNext = pCur;
        queue.pTail = pCur;
    }
    else{
        queue.pHead = pCur;
        queue.pTail = pCur;
    }
}

void pop(Queue &queue){
    if(queue.pHead){
        Node* pCur = queue.pHead;
        if (queue.pHead == queue.pTail)
            queue.pTail = queue.pHead->pNext;

        queue.pHead = queue.pHead->pNext;
        delete pCur;
    }
    else
        queue.pTail = queue.pHead;
}

Coordinate front(Queue queue){
    if (!isQueueEmpty(queue))
        return queue.pHead->data;

    return {-1, -1};
}

void printQueue(Queue queue){
    while(queue.pHead){
        cout << queue.pHead->data.x << " " << queue.pHead->data.y << endl;
        queue.pHead = queue.pHead->pNext;
    }
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

bool bfs(int height, int width, bool** visited, Queue &path, Coordinate start, Coordinate end){
    Queue q;
    push(q, start);

    //* setting up all the variables
    Coordinate direction[] = {
        {0, -1},     //up
        {1, 0},     //right
        {-1, 0},    //left
        {0, 1}     //down
    };

    struct CellInfo{
        Direction cur_dir;
        short turn_cnt;
    };

    Coordinate** prev_point = new Coordinate*[height + 2];
    CellInfo** point_info = new CellInfo*[height + 2];

    for (int i = 0; i < height + 2; i++){
        prev_point[i] = new Coordinate[width + 2];
        point_info[i] = new CellInfo[width + 2];
    }

    prev_point[start.y][start.x] = {-1, -1};
    point_info[start.y][start.x] = {NEUTRAL, 0};
    visited[start.y][start.x] = true;
    visited[end.y][end.x] = false;

    Coordinate cur_point;

    while(!isQueueEmpty(q)){
        cur_point = front(q);
        cout << cur_point.x << " " << cur_point.y << " " << point_info[cur_point.y][cur_point.x].cur_dir << " " << point_info[cur_point.y][cur_point.x].turn_cnt << endl; 

        pop(q);

        if (cur_point == end){
            //& backtracking
            cur_point = end;
            
            while(cur_point != prev_point[start.y][start.x]){
                //cout << "looping" << endl;
                push(path, cur_point);
                cur_point = prev_point[cur_point.y][cur_point.x];
            }
            return 1;
        }
        
        //& pathfinding      
        for (int i = 0; i < 4; i++){
            Coordinate next_point = cur_point + direction[i];
            bool isDead = 1;
            //Check if the next point is a valid point to move to
            if (                
                0 <= next_point.y && next_point.y < height + 2 &&
                0 <= next_point.x && next_point.x < width + 2 &&
                !visited[next_point.y][next_point.x]
            ){
                isDead = 0;
                Direction next_dir = (Direction)i;
                point_info[next_point.y][next_point.x].turn_cnt = point_info[cur_point.y][cur_point.x].turn_cnt;

                if (point_info[cur_point.y][cur_point.x].cur_dir != NEUTRAL && point_info[cur_point.y][cur_point.x].cur_dir != next_dir){
                    if (point_info[cur_point.y][cur_point.x].turn_cnt == 2){
                        isDead = true;
                        continue;
                    } 
                    else
                        point_info[next_point.y][next_point.x].turn_cnt = point_info[cur_point.y][cur_point.x].turn_cnt + 1;

                    // visited[next_point.y][next_point.x] = true;
                }

                if (!isDead){
                    visited[next_point.y][next_point.x] = true;
                    point_info[next_point.y][next_point.x].cur_dir = next_dir;
                    prev_point[next_point.y][next_point.x] = cur_point;
                    push(q, next_point);

                }
                else{
                    Coordinate trace_back = cur_point;
                    while(trace_back != start){
                        visited[trace_back.x][trace_back.y] = false;
                        trace_back = prev_point[trace_back.x][trace_back.y];
                    }   
                }
            }


            // if (0 <= next_point.y && next_point.y < height + 2 &&
            //     0 <= next_point.x && next_point.x < width + 2 &&
            //     visited[next_point.y][next_point.x]
            // ){
            //     if (point_info[next_point.y][next_point.x].turn_cnt < point_info[cur_point.y][cur_point.x].turn_cnt) {

            //     }
            // }  
        }
    }


    for (int i = 0; i < height + 2; i++){
        delete[] prev_point[i];
        delete [] point_info[i];
    }
    
    delete[] prev_point;
    delete[] point_info;

    return 0;
}



bool findPath(char** game_board, int height, int width, Queue &path, Coordinate start, Coordinate end){
    bool** visited = new bool*[height + 2];
    for (int i = 0; i < height + 2; i++)
        visited[i] = new bool[width + 2] {false};
    for (int i = 0; i < height + 2; i++){
        for (int j = 0; j < width + 2; j++){
            visited[i][j] = game_board[i][j] != '\0';
        }
    }

    if (bfs(height, width, visited, path, start, end)){
        cout << "FUCK YOU" << endl;
        return 1;
    }
    else{
        cout << "HUHU BUGGED" << endl;
        return 0;
    }

    for (int i = 0; i < height + 2; i++)
        delete[] visited[i];
    
    delete[] visited;
    return 0;
}

void printPath(Stack stack){
    while(stack.pHead){
        cout << stack.pHead->data.x << " " << stack.pHead->data.y << endl;
        stack.pHead = stack.pHead->pNext;
    }
}

// Coordinate GetInput(){
//     Coordinate input;
//     cin >> input.x >> input.y;

//     return input;
// }

// int main(){
//     int height = 5;
//     int width = 5;
//     char** game_board = createDisplayBoard(height, width);
//     printDisplayBoard(game_board, height ,width);

//     bool** visited = new bool*[height + 2];
//     for (int i = 0; i < height + 2; i++)
//         visited[i] = new bool[width + 2] {false};
//     for (int i = 0; i < height + 2; i++){
//         for (int j = 0; j < width + 2; j++){
//             visited[i][j] = game_board[i][j] != '\0';
//         }
//     }


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
//         Coordinate start = GetInput();
//         if (start.x == 69) break;
//         Coordinate end = GetInput();

//         if (game_board[start.y][start.x] == game_board[end.y][end.x]
//             && game_board[start.y][start.x] != '\0'
//             && !(start == end)
//         ){
//             // if (findPath(game_board, height, width, stack, start, end)){
//             //     removePiece(game_board, start, end);
//             // }
//             Queue path;
//             path.pHead = NULL;
//             path.pTail = NULL;
//             for (int i = 0; i < height + 2; i++){
//                 for (int j = 0; j < width + 2; j++){
//                     visited[i][j] = '\0'; //game_board[i][j] != '\0';
//                 }
//             }


//             if (bfs(height, width, visited, path, start, end)){
//                 cout << "matched" << endl;
//                 printQueue(path);
//             }
//         }
//         printDisplayBoard(game_board, height, width);
//         // cout << endl;
//         // printPath(stack);
//     }

//     for (int i = 0; i < 5 + 2; i++){
//         delete [] game_board[i];
//         delete [] visited[i];
//     }
//     delete [] game_board;
//     delete [] visited;


//     return 0;
// }