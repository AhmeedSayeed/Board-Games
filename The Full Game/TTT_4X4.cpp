#include "TTT_4X4.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// TTT_4X4 class implementation

TTT_4X4::TTT_4X4() {
    n_moves = 0;
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = -1;
        }
    }
    this->n_moves = 0;
    board[0][0] = 'O';
    board[0][2] = 'O';
    board[0][1] = 'X';
    board[0][3] = 'X';
    board[3][0] = 'X';
    board[3][2] = 'X';
    board[3][1] = 'O';
    board[3][3] = 'O';
}
bool TTT_4X4::check_board(int x, int y ,char symbol){
    if(board[x][y] == symbol)
        return true;
    return false;
}
bool TTT_4X4::update_board(int x, int y, char symbol) {
    if(symbol == ' '){
        board[x][y] = -1;
        return true;
    }
    if(symbol == 'C'){
        if(board[x][y] == -1)
            return true;
    }
    if(symbol > 'Z'){
        if(board[x][y] == symbol - 'Z'){
            return true;
        }
        return false;
    }
    if (y < 0 || y >= 4 || x <0 || x >= 4) {
        return false; // Column out of bounds
    }

    if (board[x][y] == -1) {
        board[x][y] = symbol;
        n_moves++;
        return true;
    }

    return false; // Column is full
}
void TTT_4X4::display_board() {
    cout << "Current Board:\n";
    for (int i = 0; i < rows; ++i) {
        cout << "+-----+-----+-----+-----+\n";
        for (int j = 0; j < columns; ++j) {
            cout << "|";
            if (board[i][j] == -1)
                cout << setw(3) << "-";
            else
                cout << setw(3) << (char)board[i][j];
            cout << "  ";
        }
        cout << "|\n";
    }
    cout << "+-----+-----+-----+-----+\n";
}

bool TTT_4X4::is_win() {
    for (int i = 0; i < 4; i++) {
        // Horizontal
        if ((board[i][0] != -1 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) || (board[i][1] != -1 && board[i][1] == board[i][2] && board[i][2] == board[i][3])) return true;
        // Vertical
        if ((board[0][i] != -1 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) || (board[1][i] != -1 && board[1][i] == board[2][i] && board[2][i] == board[3][i])) return true;
    }
    // Diagonals
    if (board[0][0] != -1 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[1][1] != -1 && board[1][1] == board[2][2] && board[2][2] == board[3][3]) return true;
    if (board[0][3] != -1 && board[0][3] == board[1][2] && board[1][2] == board[2][1]) return true;
    if (board[1][2] != -1 && board[1][2] == board[2][1] && board[2][1] == board[3][0]) return true;
    if (board[0][1] != -1 && board[0][1] == board[1][2] && board[1][2] == board[2][3]) return true;
    if (board[1][0] != -1 && board[1][0] == board[2][1] && board[2][1] == board[3][2]) return true;
    if (board[0][2] != -1 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    if (board[1][3] != -1 && board[1][3] == board[2][2] && board[2][2] == board[3][1]) return true;


    return false;
}


bool TTT_4X4::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool TTT_4X4::game_is_over() {
    return is_win() || is_draw();
}

// TTT_4X4Player class implementation

TTT_4X4Player::TTT_4X4Player(string n, char symbol)

        : Player<char>(n, symbol){
    this->symbol = symbol;
}
bool TTT_4X4Player::is_in_cell(int x, int y){
    if(boardPtr->update_board(x, y, symbol + 'Z')){
        return true;
    }
    return false;
}
bool TTT_4X4Player::is_valid(int x, int y, int w, int z){
    // 1. Check if source and destination coordinates are within bounds
    if (x < 0 || x >= 4 || y < 0 || y >= 4 || w < 0 || w >= 4 || z < 0 || z >= 4) {
        return false;
    }
    // 3. Ensure the destination cell is empty
    if (!(boardPtr->update_board(w, z , 'C'))) {
        return false;
    }

    // 4. Ensure the move is horizontal or vertical (not diagonal)
    //    The Manhattan distance must be exactly 1
    if (abs(x - w) + abs(y - z) != 1) {
        return false;
    }
    // If all checks pass, the move is valid
    return true;
}
void TTT_4X4Player::getmove(int& x, int& y) {
    int w = 0; int z = 0;
    cout << name << ", enter row(0-3) and column (0-3) of the piece you want to move: ";
    cin >> w >> z;
    while((w > 3 || w < 0 || z > 3 || z < 0) || !is_in_cell(w,z)){
        cout << name << ", Please enter a valid input. The cell you picked doesn't have your symbol(" << char(symbol) <<"): ";
        cin >> w >> z;
    }
    cout << name << ", enter row(0-3) and column (0-3) of the cell you want to move your piece to: ";
    cin >> x >> y;
    while(x > 3 || x < 0 || y > 3 || y < 0){
        cout << name << ", Invalid input please enter row(0-3) and column (0-3) of the cell you want to move your piece to: ";
        cin >> x >> y;
    }
    while(!is_valid(w,z,x,y)){
        cout << name << ", Please enter a valid input. The cell you picked to move to is invalid: ";
        cin >> x >> y;
    }
    boardPtr->update_board(w, z, ' ');
}

TTT_4X4RandomPlayer::TTT_4X4RandomPlayer(string name , char symbol) : RandomPlayer<char>(symbol) {
    this->name = name;
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

bool TTT_4X4RandomPlayer::is_in_cell(int x, int y){
    if(boardPtr->update_board(x, y, symbol + 'Z')){
        return true;
    }
    return false;
}
bool TTT_4X4RandomPlayer::is_valid(int x, int y, int w, int z){
    // 1. Check if source and destination coordinates are within bounds
    if (x < 0 || x >= 4 || y < 0 || y >= 4 || w < 0 || w >= 4 || z < 0 || z >= 4) {
        return false;
    }
    // 3. Ensure the destination cell is empty
    if (!(boardPtr->update_board(w, z , 'C'))) {
        return false;
    }

    // 4. Ensure the move is horizontal or vertical (not diagonal)
    //    The Manhattan distance must be exactly 1
    if (abs(x - w) + abs(y - z) != 1) {
        return false;
    }
    // If all checks pass, the move is valid
    return true;
}

void TTT_4X4RandomPlayer::getmove(int& x, int& y) {
    int w = 0; int z = 0;
    w = rand() % 4;
    z = rand() % 4;
    while(!is_in_cell(w, z)){
        w = rand() % 4;
        z = rand() % 4;
    }
    y = rand() % 4;
    x = rand() % 4;
    while(!is_valid(w, z, x , y)){
        y = rand() % 4;
        x = rand() % 4;
    }
    boardPtr->update_board(w, z, ' ');
    cout << this->name << " chooses the piece at: (" << w << "," << z << ") and moved it to: (" << x << "," << y << ")." << endl;
}