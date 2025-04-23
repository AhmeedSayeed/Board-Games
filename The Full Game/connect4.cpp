#include "connect4.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// Connect4 class implementation

Connect4::Connect4() {
    n_moves = 0;
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = -1;
        }
    }
}

bool Connect4::update_board(int x, int y, char symbol) {
    if (y < 0 || y >= 7 || x <0 || x > 6) {
        return false; // Column out of bounds
    }

    for (int i = rows - 1; i >= 0; --i) {
        if (board[i][y] == -1) {
            board[i][y] = symbol;
            n_moves++;
            return true;
        }
    }

    return false; // Column is full
}

void Connect4::display_board() {
    cout << "Current Board:\n";
    for (int i = 0; i < rows; ++i) {
        if(i == 0){
        cout << "|  0  |  1  |  2  |  3  |  4  |  5  |  6  |\n";
        }
        cout << "+-----+-----+-----+-----+-----+-----+-----+\n";
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
    cout << "+-----+-----+-----+-----+-----+-----+-----+\n";
}

bool Connect4::is_win() {
    // Horizontal check
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j <= columns - 4; ++j) {
            if (board[i][j] != -1 &&
                board[i][j] == board[i][j + 1] &&
                board[i][j] == board[i][j + 2] &&
                board[i][j] == board[i][j + 3]) {
                return true;
            }
        }
    }

    // Vertical check
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i <= rows - 4; ++i) {
            if (board[i][j] != -1 &&
                board[i][j] == board[i + 1][j] &&
                board[i][j] == board[i + 2][j] &&
                board[i][j] == board[i + 3][j]) {
                return true;
            }
        }
    }

    // Diagonal (top-left to bottom-right) check
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j <= columns - 4; ++j) {
            if (board[i][j] != -1 &&
                board[i][j] == board[i + 1][j + 1] &&
                board[i][j] == board[i + 2][j + 2] &&
                board[i][j] == board[i + 3][j + 3]) {
                return true;
            }
        }
    }

    // Diagonal (top-right to bottom-left) check
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 3; j < columns; ++j) {
            if (board[i][j] != -1 &&
                board[i][j] == board[i + 1][j - 1] &&
                board[i][j] == board[i + 2][j - 2] &&
                board[i][j] == board[i + 3][j - 3]) {
                return true;
            }
        }
    }

    return false;
}


bool Connect4::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool Connect4::game_is_over() {
    return is_win() || is_draw();
}

// Connect4Player class implementation

Connect4Player::Connect4Player(string n, char symbol)
    : Player<char>(n, symbol){
        this->symbol = symbol;
    }

void Connect4Player::getmove(int& x, int& y) {
    cout << name << ", enter column (0-6) to place your piece: ";
    cin >> y;
    x = 5;
}

Connect4RandomPlayer::Connect4RandomPlayer(string name , char symbol) : RandomPlayer<char>(symbol) {
    this->name = name;
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

void Connect4RandomPlayer::getmove(int& x, int& y) {
    y = rand() % 7; // Random column between 0 and 6
    x = 5;

    cout << this->name << " chooses column: " << y << endl;
}