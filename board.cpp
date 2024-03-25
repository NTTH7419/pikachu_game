#include "board.h"


//* Queue Implementation

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
    return queue.pHead->data;
}

void printQueue(Queue queue){
    while(queue.pHead){
        cout << queue.pHead->data.x << " " << queue.pHead->data.y << endl;
        queue.pHead = queue.pHead->pNext;
    }
}



int getInput() {
	char inp = getch();
	if (inp == K_ESC) return -1; 	// ESC
	if (inp == K_ENTER) return 0; 		// ENTER
	if (inp == K_W || inp == K_w) return 1;
	if (inp == K_A || inp == K_a) return 2;
	if (inp == K_S || inp == K_s) return 3;
	if (inp == K_D || inp == K_d) return 4;
	return -2;	// other input
}

void goTo(SHORT x, SHORT y) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = x;
    Position.Y = y;

	SetConsoleCursorPosition(hStdout, Position);
}

// change background and text color
void changeTextColor(const string bg_color, const string text_color) {
	cout << bg_color << text_color;
}


void board::init() {
	srand(time(0) + rand());
	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			if (i * j == 0 || i == height + 1 || j == width + 1) letter_board[i][j] = 0;
			else letter_board[i][j] = 65 + rand() % 5;
		}
	}
}

bool board::isInBoard(Coordinate p){
    return !(p.x <= 0 || p.y <= 0 || p.y >= height + 1 || p.x >= width + 1);
}

void board::printBoard(){
    for (int i = 0; i < height + 2; i++){
        for (int j = 0; j < width + 2; j++){
            cout << letter_board[i][j] << " ";
        }
        cout << endl;
    }
}

bool board::isBoardEmpty(){
    for (int i = 1; i < height + 1; i++){
        for (int j = 1; j < width + 1; j++){
            if (letter_board[i][j] != 0) return 0;
        }
    }
    return 1;
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
        // cout << cur_point.x << " " << cur_point.y << " " << point_info[cur_point.y][cur_point.x].cur_dir << " " << point_info[cur_point.y][cur_point.x].turn_cnt << endl; 

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

bool board::findPath(Queue &path, Coordinate start, Coordinate end){
    bool** visited = new bool*[height + 2];
    for (int i = 0; i < height + 2; i++)
        visited[i] = new bool[width + 2] {false};
    for (int i = 0; i < height + 2; i++){
        for (int j = 0; j < width + 2; j++){
            visited[i][j] = letter_board[i][j] != '\0';
        }
    }

    if (bfs(height, width, visited, path, start, end)){
        // cout << "FUCK YOU" << endl;
        return 1;
    }
    else{
        // cout << "HUHU BUGGED" << endl;
        return 0;
    }

    for (int i = 0; i < height + 2; i++)
        delete[] visited[i];
    
    delete[] visited;
    return 0;
}


void board::moveCursor(Coordinate &cur, int inp) {
	if (inp == 1) {
		cur.y -= 1;
		if (cur.y <= 0) cur.y = height;	// if cursor moves outside of board, it moves to the other side
	}
	else if (inp == 2) {
		cur.x -= 1;
		if (cur.x <= 0) cur.x = width;	
	}
	else if (inp == 3) {
		cur.y += 1;
		if (cur.y > width) cur.y = 1;
	}
	else if (inp == 4) {
		cur.x += 1;
		if (cur.x > height) cur.x = 1;
	}
}

void board::highlightPos(Coordinate pos, const string bg_color, const string text_color) {
	changeTextColor(bg_color, text_color);
	for (int i = 1; i <= cell_height; i++) {
		goTo(x_offset + (cell_width + 1) * pos.x + 1,
			 y_offset + (cell_height + 1) * pos.y + i);
		cout << string(cell_width, ' ');
	}
	goTo(x_offset + (cell_width + 1) * pos.x + (cell_width + 1) / 2,
		 y_offset + (cell_height + 1) * pos.y + (cell_height + 1) / 2);
		cout << letter_board[pos.y][pos.x];
	changeTextColor(BG_BLACK, TEXT_WHITE);
}

void board::unhighlightPos(Coordinate pos) {
	highlightPos(pos, BG_BLACK, TEXT_YELLOW);
}

void board::displayBoard() {

	changeTextColor(BG_BLACK, TEXT_WHITE);
	
	// row separator
	string row_sep;
	row_sep = ' ';
	for (int i = 0; i < width; i++) {
		row_sep += string(cell_width, HORIZONTAL_EDGE) + ' ';
	}

	// create spliter line
	string spliter_line;
	spliter_line = '|';
	for (int i = 0; i < width; i++) {
		spliter_line += string(cell_width, ' ') + '|';
	}

	// draw board
	int line = 0;
	goTo(x_offset + (cell_width + 1), y_offset + (cell_height + 1));	// offset + outline
	cout << row_sep;
	line++;
	Sleep(50);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < cell_height; j++) {
			goTo(x_offset + (cell_width + 1), y_offset + (cell_height + 1) + line++);	// offset + outline + line_number
			cout << spliter_line;
			Sleep(50);
		}
		goTo(x_offset + cell_width + 1, y_offset + (cell_height + 1) + line++);
		cout << row_sep;
		Sleep(50);
	}

	// put letters in
	changeTextColor(BG_BLACK, TEXT_YELLOW);
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			goTo(x_offset + j * (cell_width + 1) + (cell_width + 1) / 2,
				 y_offset + i * (cell_height + 1) + (cell_height + 1) / 2);	// offset + cell pos + letter pos in cell
			cout << letter_board[i][j];
			Sleep(50);
		}
	}
	changeTextColor(BG_BLACK, TEXT_WHITE);
}

void board::removeCell(Coordinate pos) {
	if (!isInBoard(pos)) return;

	letter_board[pos.y][pos.x] = 0;

	goTo(x_offset + pos.x * (cell_width + 1) + (cell_width + 1) / 2,
		 y_offset + pos.y * (cell_height + 1) + (cell_height + 1) / 2);

	cout << ' ';

	bool left, right, top, bottom; // to check if exist/ empty
	left = !letter_board[pos.y][pos.x - 1];
	right = !letter_board[pos.y][pos.x + 1];
	top = !letter_board[pos.y - 1][pos.x];
	bottom = !letter_board[pos.y + 1][pos.x];

	changeTextColor(BG_BLACK, TEXT_WHITE);
	if (left) {		// check left side
		for (int i = 1; i <= cell_height; i++) {
			goTo(x_offset + (cell_width + 1) * pos.x,
				 y_offset + (cell_height + 1) * pos.y + i);
			cout << ' ';
		}
	}

	if (right) {	// check right side
		for (int i = 1; i <= cell_height; i++) {
			goTo(x_offset + (cell_width + 1) * pos.x + cell_width,
				 y_offset + (cell_height + 1) * pos.y + i);
			cout << ' ';
		}
	}

	if (top) {		// check above
		goTo(x_offset + (cell_width + 1) * pos.x + 1,
			 y_offset + (cell_height + 1) * pos.y);
		cout << string(cell_width, ' ');
	}

	if (bottom) {	// check below
		goTo(x_offset + (cell_width + 1) * pos.x + 1,
			 y_offset + (cell_height + 1) * pos.y + cell_height);
		cout << string(cell_width, ' ');
	}
}

void board::drawPath(Queue &q) {
	Coordinate prev, curr, next;
	Vector prev_curr, curr_next;
	bool isStart = true , isEnd = false;
	bool left, right, up, down;
	prev = {-1, -1};
	curr = front(q); pop(q);
	next = front(q); pop(q);


	while(1) {
		left = right = up = down = false;
		prev_curr = curr - prev;
		curr_next = next - curr;
		
		// huong di
		if (!isEnd) {
			if (curr_next.x == 0) {
				if (curr_next.y < 0) 	// di len
					up = true;
				else 					// di xuong
					down = true;
			}
			else {
				if (curr_next.x > 0) 	// qua phai
					right = true;
				else 					// qua trai
					left = true;
			}
		}

		// huong den
		if (!isStart) {
			if (prev_curr.x == 0) {
				if (prev_curr.y > 0)	// tu tren
					up = true;
				else					// tu duoi
					down = true;
			}
			else {
				if (prev_curr.x < 0)	// tu phai
					right = true;
				else					// tu trai
					left = true;
			}
		}

		// draw path
		changeTextColor(BG_BLACK, TEXT_GREEN);
		if (left) {
			goTo(x_offset + (cell_width + 1) * curr.x + 1,
				 y_offset + (cell_height + 1) * curr.y + (cell_height + 1) / 2);
			if (!isStart && !isEnd) cout << string((cell_width + 1) / 2, HORIZONTAL_EDGE);
			else cout << HORIZONTAL_EDGE;
		}

		if (right) {
			if (!isStart && !isEnd) {
				goTo(x_offset + (cell_width + 1) * curr.x + (cell_width + 1) / 2,
					 y_offset + (cell_height + 1) * curr.y + (cell_height + 1) / 2);
				cout << string((cell_width + 1) / 2 + 1, HORIZONTAL_EDGE);	
			}
			else {
				goTo(x_offset + (cell_width + 1) * curr.x + cell_width,
					 y_offset + (cell_height + 1) * curr.y + (cell_height + 1) / 2);
				cout << HORIZONTAL_EDGE << HORIZONTAL_EDGE;
			}
		}

		if (up) {
			if(!isStart && !isEnd) {
				for (int i = 1; i <= (cell_height + 1) / 2; i++) {
					goTo(x_offset + (cell_width + 1) * curr.x + (cell_width + 1) / 2,
						 y_offset + (cell_height + 1) * curr.y + i);
					cout << VERTICAL_EDGE;
				}
			}
		}

		if (down) {
			goTo(x_offset + (cell_width + 1) * curr.x + (cell_width + 1) / 2,
				 y_offset + (cell_height + 1) * curr.y + (cell_height + 1));
			cout << VERTICAL_EDGE;
			if(!isStart && !isEnd) {
				for (int i = (cell_height + 1) / 2; i <= cell_height; i++) {
					goTo(x_offset + (cell_width + 1) * curr.x + (cell_width + 1) / 2,
						 y_offset + (cell_height + 1) * curr.y + i);
					cout << VERTICAL_EDGE;
				}
			}
		}

		if (!isStart && !isEnd) {
			if (left && up) {
				goTo(x_offset + (cell_width + 1) * curr.x + (cell_width + 1) / 2,
					 y_offset + (cell_height + 1) * curr.y + (cell_height + 1) / 2);
				cout << LEFT_UP_CORNER;
			}
			else if (left && down) {
				goTo(x_offset + (cell_width + 1) * curr.x + (cell_width + 1) / 2,
					 y_offset + (cell_height + 1) * curr.y + (cell_height + 1) / 2);
				cout << LEFT_DOWN_CORNER;
			}
			else if (right && up) {
				goTo(x_offset + (cell_width + 1) * curr.x + (cell_width + 1) / 2,
					 y_offset + (cell_height + 1) * curr.y + (cell_height + 1) / 2);
				cout << RIGHT_UP_CORNER;
			}
			else if (right && down) {
				goTo(x_offset + (cell_width + 1) * curr.x + (cell_width + 1) / 2,
					 y_offset + (cell_height + 1) * curr.y + (cell_height + 1) / 2);
				cout << RIGHT_DOWN_CORNER;
			}
		}

		if (isStart) isStart = false;
		if (isEnd) break;
		prev = curr;
		curr = next;
		isEnd = isQueueEmpty(q);
		if (!isEnd) {
			next = front(q); pop(q);
		}
	}
}

void board::gameLoop() {

	init();

	int n_cells = height * width;
	Coordinate cur1, cur2;
	int inp;
	bool cur1_selected = false;
	displayBoard();

	Queue path;
	cur1 = cur2 = {1, 1};
	highlightPos(cur1, BG_CYAN, TEXT_WHITE);
	
	while (n_cells > 0) {
		inp = getInput();

		// invalid input
		if (inp == -2) continue;

		// escape
		if (inp == -1) break;
		
		// move cursor
		if (inp > 0) {
			if (!cur1_selected) {
				unhighlightPos(cur1);
				moveCursor(cur1, inp);
				highlightPos(cur1, BG_CYAN, TEXT_WHITE);
			}
			else {
				if (cur2 != cur1) unhighlightPos(cur2);
				else highlightPos(cur1, BG_YELLOW, TEXT_WHITE);
				moveCursor(cur2, inp);
				highlightPos(cur2, BG_CYAN, TEXT_WHITE);
			}
		}

		// select cell
		else {
			if (!cur1_selected) {
				if (letter_board[cur1.y][cur1.x] == 0) continue; // if select empty cell
				highlightPos(cur1, BG_YELLOW, TEXT_WHITE);
				cur1_selected = true;
				cur2 = cur1;
			}

			// matching
			else {
				if (cur2 == cur1) {		// deselect cell
					cur1_selected = false;
					continue;
				}
				if (letter_board[cur2.y][cur2.x] == 0) continue;
				if (cur1 != cur2 && letter_board[cur1.y][cur1.x] == letter_board[cur2.y][cur2.x] 
					&& findPath(path, cur1, cur2)
				) {
					drawPath(path);	//* Nho chuyen xuong
					highlightPos(cur1, BG_GREEN, TEXT_WHITE);
					highlightPos(cur2, BG_GREEN, TEXT_WHITE);
					Sleep(500);

					unhighlightPos(cur1);
					unhighlightPos(cur2);
					removeCell(cur1);
					removeCell(cur2);

					n_cells -= 2;
					cur1 = cur2;
				}
				else {
					highlightPos(cur1, BG_RED, TEXT_WHITE);
					highlightPos(cur2, BG_RED, TEXT_WHITE);
					Sleep(500);
					unhighlightPos(cur1);
					highlightPos(cur2, BG_CYAN, TEXT_WHITE);
					cur1 = cur2;
				}
				cur1_selected = false;
			}
		}
	}
}