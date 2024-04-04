#include "board.h"



void Board::initBoard() {
	srand(time(0) + rand());
	// int* count = new int[k] {0};

	vector<char> remaining_char;

    for (int i = 1; i <= ceil(height / 2.0); i++){
        for (int j = 1; j <= width; j++){
            char temp = rand() % distinct_letter + 65;
            remaining_char.push_back(temp);
            letter_board[i][j] = temp;
            if (i == ceil(height / 2.0) && j == ceil(width / 2.0) && height % 2 != 0){
				break;            
			}
        }
    }

    for (int i = ceil(height / 2.0); i <= height; i++){
		if (i == ceil(height / 2.0) && height % 2 == 0) i++;
        for (int j = 1; j <= width; j++){
            if (i == ceil(height / 2.0) && j == 1 && height % 2 != 0) j = ceil(width / 2.0) + 1;

            int n = remaining_char.size();

            int index = rand() % n;
            letter_board[i][j] = remaining_char[index];
            remaining_char.erase(remaining_char.begin() + index);
        }
    }

}

void Board::loadBackground(int difficulty) {
	ifstream fin;
	if (difficulty == EASY) {
		fin.open("bg_easy.txt");
		bg_info = "Stonehenge - Art by lgbeard";
	}
	else if (difficulty == MEDIUM) {
		fin.open("bg_medium.txt");
        bg_info = "Tower Bridge - Art by unknown";
	}
	else if (difficulty == HARD) {
		fin.open("bg_hard.txt");
		bg_info = "Taj Mahal - Art by unknown";
	}

	for (int i = 0; i < (height + 2) * cell_height + 1; i++) {
		getline(fin, background[i]);
	}
	fin.close();
}

bool Board::isInBoard(Coordinate p){
    return !(p.x <= 0 || p.y <= 0 || p.y >= height + 1 || p.x >= width + 1);
}

void Board::printBoard(){
    for (int i = 0; i < height + 2; i++){
        for (int j = 0; j < width + 2; j++){
            cout << getLetter({j, i}) << " ";
        }
        cout << endl;
    }
}

bool Board::isBoardEmpty(){
    for (int i = 1; i < height + 1; i++){
        for (int j = 1; j < width + 1; j++){
            if (getLetter({j, i}) != 0) return 0;
        }
    }
    return 1;
}

bool Board::isVisited(Coordinate point, vector<Coordinate> path){
    while(!path.empty()){
        if (point == path.back()) return true;
        path.pop_back();
    }
    return false;
}

bool Board::bfs(Coordinate start, Coordinate end, vector<Coordinate> &path){
    struct CurPoint{
        vector<Coordinate> path;
        Direction cur_dir;
        short turn_cnt;
    };


    //* bfs queue
    queue<CurPoint> q;

    //* store all valid paths from start to end
    queue<vector<Coordinate>> paths;

    Coordinate direction[] = {
        {0, -1},     //up
        {1, 0},     //right
        {-1, 0},    //left
        {0, 1}     //down
    };

    q.push({{start}, NEUTRAL, 0});

    while(!q.empty()){
        Coordinate cur_point = q.front().path.back();
        vector<Coordinate> cur_path = q.front().path;
        Direction cur_dir = q.front().cur_dir;
        int cur_point_turn = q.front().turn_cnt;
        q.pop();

        if (cur_point == end){
            paths.push(cur_path);
            path = cur_path;
            return 1;
        }

        for (int i = 0; i < 4; i++){
            Coordinate next_point = cur_point + direction[i];
            vector<Coordinate> next_path = cur_path;
            Direction next_dir = (Direction)i;   
            short next_point_turn = cur_point_turn;

            if (
                0 <= next_point.y && next_point.y < height + 2 &&
                0 <= next_point.x && next_point.x < width + 2 &&
                (getLetter({next_point.x, next_point.y}) == '#' || next_point == end) &&
                !isVisited(next_point, cur_path)
            ){

                if (cur_dir != NEUTRAL && cur_dir != next_dir){

                    if (cur_point_turn == 2)
                        continue;
                    else
                        next_point_turn = cur_point_turn + 1;
                }

                next_path.push_back(next_point);
                q.push({next_path, next_dir, next_point_turn});
            }
        }

	}

    return 0;
}

void Board::highlightCell(Coordinate pos, string bg_color, string text_color = colors.TXT_highlight_letter) {
	if (isValid(pos)) {
		changeTextColor(bg_color, text_color);
		for (int i = 1; i < cell_height; i++) {
			goTo(x_offset + cell_width * pos.x + 1,
				 y_offset + cell_height * pos.y + i);
			cout << string(cell_width - 1, ' ');
		}
		goTo(x_offset + cell_width * pos.x + cell_width / 2,
			 y_offset + cell_height * pos.y + cell_height / 2);
			cout << getLetter(pos);
	}
	else {		// empty cell, draw background
		changeTextColor(bg_color, colors.TXT_main_text);
		for (int i = 1; i < cell_height; i++) {
			goTo(x_offset + cell_width * pos.x + 1,
				 y_offset + cell_height * pos.y + i);
			cout << background[cell_height * pos.y + i].substr(cell_width * pos.x + 1, cell_width - 1);
		}
	}
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
}

void Board::unhighlightCell(Coordinate pos) {
	highlightCell(pos, colors.BG_main_bg, colors.TXT_letter);
}

void Board::highlightCursor(Coordinate pos) {
	highlightCell(pos, colors.BG_cell_cursor);
}

void Board::highlightSelected(Coordinate pos) {
	highlightCell(pos, colors.BG_cell_selected);
}
void Board::highlightCorrectPair(Coordinate pos1, Coordinate pos2) {
	highlightCell(pos1, colors.BG_cell_correct);
	highlightCell(pos2, colors.BG_cell_correct);
}
void Board::highlightWrongPair(Coordinate pos1, Coordinate pos2) {
	highlightCell(pos1, colors.BG_cell_wrong);
	highlightCell(pos2, colors.BG_cell_wrong);
}
void Board::highlightHintPair(Coordinate pos1, Coordinate pos2) {
	highlightCell(pos1, colors.BG_cell_hint);
	highlightCell(pos2, colors.BG_cell_hint);
}

char Board::getLetter(Coordinate pos) {
	if (is_array)
		return letter_board[pos.y][pos.x];
	
	return list_board[pos.y][pos.x];
}

bool Board::isValid(Coordinate pos) {
	return (getLetter(pos) != '#');
}

void Board::displayLetter() {
	changeTextColor(colors.BG_main_bg, colors.TXT_letter);
	for (int i = 1; i <= width; i++) {
		for (int j = 1; j <= height; j++) {
			goTo(x_offset + i * cell_width + cell_width / 2,
				 y_offset + j * cell_height + cell_height / 2);	// offset + cell pos + letter pos in cell
			cout << getLetter({i, j});
			Sleep(500 / (height * width));
		}
	}
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
}

void Board::displayBoard() {
	playSFX(SFX_START_GAME);

	//* print the game board
	changeTextColor(colors.BG_main_bg, colors.TXT_cell_border);
	
	// row separator
	string row_sep;
	row_sep = ' ';
	for (int i = 0; i < width; i++) {
		row_sep += string(cell_width - 1, HORIZONTAL_EDGE) + ' ';
	}

	// create spliter line
	string spliter_line;
	spliter_line = VERTICAL_EDGE;
	for (int i = 0; i < width; i++) {
		spliter_line += string(cell_width - 1, ' ') + VERTICAL_EDGE;
	}

	// draw board
	int line = 0;
	goTo(x_offset + cell_width, y_offset + cell_height);	// offset + outline
	cout << row_sep;
	line++;
	Sleep(500 / (height * cell_height + 1));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < cell_height - 1; j++) {
			goTo(x_offset + cell_width, y_offset + cell_height + line++);	// offset + outline + line_number
			cout << spliter_line;
			Sleep(500 / (height * cell_height + 1));
		}
		goTo(x_offset + cell_width, y_offset + cell_height + line++);
		cout << row_sep;
		Sleep(500 / (height * cell_height + 1));
	}

	// put letters in
	displayLetter();
}


void Board::removeCell(Coordinate pos) {
	Coordinate cur = pos;
	if (!is_array) {	// go to the last cell in the row
		for (int i = cur.x + 1; i <= width; i++) {
			if (!isValid({i, pos.y})) break;
			pos.x = i;
		}
	}

	// remove the letter and draw background
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	for (int i = 1; i < cell_height; i++) {
		goTo(x_offset + pos.x * cell_width + 1,
			 y_offset + pos.y * cell_height + i);
		cout << background[pos.y * cell_height + i].substr(pos.x * cell_width + 1, cell_width - 1);
	}


	//check if the adjation cell exist
	bool left, right, top, bottom;
	left = !isValid({pos.x - 1, pos.y });
	right = !isValid({pos.x + 1, pos.y});
	top = !isValid({pos.x, pos.y - 1});
	bottom = !isValid({pos.x, pos.y + 1});

	if (left) {		// check left side
		for (int i = 1; i < cell_height; i++) {
			goTo(x_offset + cell_width * pos.x,
				 y_offset + cell_height * pos.y + i);
			cout << background[cell_height * pos.y + i][cell_width * pos.x];
		}
	}

	if (right) {	// check right side
		for (int i = 1; i < cell_height; i++) {
			goTo(x_offset + cell_width * pos.x + cell_width,
				 y_offset + cell_height * pos.y + i);
			cout << background[cell_height * pos.y + i][cell_width * pos.x + cell_width];
		}
	}

	if (top) {		// check above
		goTo(x_offset + cell_width * pos.x + 1,
			 y_offset + cell_height * pos.y);
		cout << background[cell_height * pos.y].substr(cell_width * pos.x + 1, cell_width - 1);
	}

	if (bottom) {	// check below
		goTo(x_offset + cell_width * pos.x + 1,
			 y_offset + cell_height * pos.y + cell_height);
		cout << background[cell_height * pos.y + cell_height].substr(cell_width * pos.x + 1, cell_width - 1);
	}

	if (is_array){
		letter_board[pos.y][cur.x] = '#';
	}
	else{
		list_board[pos.y].remove(cur.x);

		// print the board again
		changeTextColor(colors.BG_main_bg, colors.TXT_letter);
		for (int i = cur.x; i <= width; i++) {
			if (!isValid({i, pos.y})) break;
			goTo(x_offset + i * cell_width + cell_width / 2,
				 y_offset + pos.y * cell_height + cell_height / 2);
			cout << getLetter({i, pos.y});
		}
	}
}

queue<Coordinate> Board::drawPath(vector<Coordinate> path) {
	queue<Coordinate> drawn_pixels;
	Coordinate prev, curr, next;
	Vector prev_curr, curr_next;

	int	x, y; 

	bool isStart = true , isEnd = false;
	bool left, right, up, down;

	prev = {-1, -1};
	curr = path.back(); path.pop_back();
	next = path.back(); path.pop_back();


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
		changeTextColor(colors.BG_main_bg, colors.TXT_path);
		if (left) {
			x = x_offset + cell_width * curr.x + 1;
			y = y_offset + cell_height * curr.y + cell_height / 2;
			goTo(x, y);
			if (!isStart && !isEnd) {
				for (int i = 0; i < cell_width / 2; i++) {
					cout << HORIZONTAL_EDGE;
					drawn_pixels.push({x + i, y});
				}
			}
			else{
				cout << HORIZONTAL_EDGE;
				drawn_pixels.push({x, y});
			}
		}

		if (right) {
			if (!isStart && !isEnd) {
				x = x_offset + cell_width * curr.x + cell_width / 2;
				y = y_offset + cell_height * curr.y + cell_height / 2;
				goTo(x, y);
				for (int i = 0; i < cell_width / 2 + 1; i++) {
					cout << HORIZONTAL_EDGE;
					drawn_pixels.push({x + i, y});
				}
			}
			else {
				x = x_offset + cell_width * curr.x + cell_width - 1;
				y = y_offset + cell_height * curr.y + cell_height / 2;
				goTo(x, y);
				cout << HORIZONTAL_EDGE << HORIZONTAL_EDGE;
				drawn_pixels.push({x, y});
				drawn_pixels.push({x + 1, y});
			}
		}

		if (up) {
			if(!isStart && !isEnd) {
				x = x_offset + cell_width * curr.x + cell_width / 2;
				y = y_offset + cell_height * curr.y;
				for (int i = 1; i <= cell_height / 2; i++) {
					goTo(x, y + i);
					cout << VERTICAL_EDGE;
					drawn_pixels.push({x, y + i});
				}
			}
		}

		if (down) {
			x = x_offset + cell_width * curr.x + cell_width / 2;
			y = y_offset + cell_height * curr.y + cell_height;
			goTo(x, y);
			cout << VERTICAL_EDGE;
			drawn_pixels.push({x, y});
			if(!isStart && !isEnd) {
				x = x_offset + cell_width * curr.x + cell_width / 2;
				y = y_offset + cell_height * curr.y;
				for (int i = cell_height / 2; i < cell_height; i++) {
					goTo(x, y + i);
					cout << VERTICAL_EDGE;
					drawn_pixels.push({x, y + i});
				}
			}
		}

		if (!isStart && !isEnd) {
			if (left && up) {
				goTo(x_offset + cell_width * curr.x + cell_width / 2,
					 y_offset + cell_height * curr.y + cell_height / 2);
				cout << LEFT_UP_CORNER;
			}
			else if (left && down) {
				goTo(x_offset + cell_width * curr.x + cell_width / 2,
					 y_offset + cell_height * curr.y + cell_height / 2);
				cout << LEFT_DOWN_CORNER;
			}
			else if (right && up) {
				goTo(x_offset + cell_width * curr.x + cell_width / 2,
					 y_offset + cell_height * curr.y + cell_height / 2);
				cout << RIGHT_UP_CORNER;
			}
			else if (right && down) {
				goTo(x_offset + cell_width * curr.x + cell_width / 2,
					 y_offset + cell_height * curr.y + cell_height / 2);
				cout << RIGHT_DOWN_CORNER;
			}
		}

		if (isStart) isStart = false;
		if (isEnd) break;
		prev = curr;
		curr = next;
		isEnd = path.empty();
		if (!isEnd) {
			next = path.back(); path.pop_back();
		}
	}
	return drawn_pixels;
}

void Board::deletePath(queue<Coordinate> drawn_pixels) {
	int x, y;
	Coordinate curr;
	changeTextColor(colors.BG_main_bg, colors.TXT_main_text);
	while (!drawn_pixels.empty()) {
		curr = drawn_pixels.front(); drawn_pixels.pop();
		x = curr.x;
		y = curr.y;
		goTo(x, y);
		cout << background[y - y_offset][x - x_offset];
	}
}

void Board::animateShuffle() {
	for (int i = 1; i <= width; i++) {
		for (int j = 1; j <= height; j++) {
			highlightCell({i, j}, colors.BG_PINK, colors.TXT_highlight_letter);
		}
		Sleep(30);
		for (int j = 1; j <= height; j++) {
			unhighlightCell({i, j});
		}
	}
}

void Board::shift(Coordinate pos){
	for (int j = pos.x; j <= width; j++){
		letter_board[pos.y][j] = getLetter({j + 1, pos.y});
		
		unhighlightCell({j, pos.y});
	}
}

void Board::initListBoard(){
	srand(time(NULL) + rand());
	vector<char> remaining_char;

	for (int i = 1; i <= height; i++){
		for (int j = 1; j <= width; j++){
			if (i <= height/2){
				char c = rand() % distinct_letter + 65;
				remaining_char.push_back(c);
				list_board[i][j] = c;
			}

			else{
				int n = remaining_char.size();
				int index = rand() % n;
				list_board[i][j] = remaining_char[index];
				remaining_char.erase(remaining_char.begin() + index);
			}
		}
	}
}

void Board::printList(){
	for (int i = 0; i < height + 2; i++){
		for (int j = 0; j < width + 2; j++){
			cout << list_board[i][j] << " ";
		}
		cout << endl;
	}
}

