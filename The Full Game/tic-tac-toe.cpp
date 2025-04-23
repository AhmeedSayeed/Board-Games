#include "tic-tac-toe.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

// TicTacToeNumbers class implementation
vector<vector<int>> used(3, vector<int>(3, -1));
vector<int> used_numbers;
TicTacToeNumbers::TicTacToeNumbers() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = -1;
        }
    }
    n_moves = 0;

}

bool TicTacToeNumbers::update_board(int x, int y, int symbol) {
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != -1)
        return false;

    if(symbol == -10){
        if(board[x][y] == -1){
            return true;
        }
        return false;
    }
    board[x][y] = symbol;
    used_numbers.push_back(symbol);
    n_moves++;
    return true;
}

void TicTacToeNumbers::display_board() {
    cout << "Current Board:\n";
    for (int i = 0; i < rows; ++i) {
        cout << "+-----+-----+-----+\n";
        for (int j = 0; j < columns; ++j) {
            cout << "|";
            if (board[i][j] == -1)
                cout << setw(1) << "(" << i << ","<< j << ")";
            else
                cout << setw(3) << board[i][j] << "  ";
        }
        cout << "|\n";
    }
    cout << "+-----+-----+-----+\n";
}

bool TicTacToeNumbers::is_win() {
    // Check rows, columns, and diagonals
    for (int i = 0; i < rows; ++i)
        if ((board[i][0] != -1 && board[i][1] != -1 && board[i][2] != -1 &&
             board[i][0] + board[i][1] + board[i][2] == 15)){
            for(int z = 0; z < 3; z++){
                for(int y = 0; y < 3; y++){
                    used[z][y] = -1;
                }
            }
            return true;
        }

    for (int j = 0; j < columns; ++j)
        if (board[0][j] != -1 && board[1][j] != -1 && board[2][j] != -1 &&
            (board[0][j] + board[1][j] + board[2][j] == 15)){
            for(int z = 0; z < 3; z++){
                for(int y = 0; y < 3; y++){
                    used[z][y] = -1;
                }
            }
            return true;
        }

    if (board[0][0] != -1 && board[1][1] != -1 && board[2][2] != -1 &&
        board[0][0] + board[1][1] + board[2][2] == 15){
        for(int z = 0; z < 3; z++){
            for(int y = 0; y < 3; y++){
                used[z][y] = -1;
            }
        }
        return true;
    }

    if (board[0][2] != -1 && board[1][1] != -1 && board[2][0] != -1 &&
        board[0][2] + board[1][1] + board[2][0] == 15){

        for(int z = 0; z < 3; z++){
            for(int y = 0; y < 3; y++){
                used[z][y] = -1;
            }
        }
        return true;
    }

    return false;
}

bool TicTacToeNumbers::is_draw() {
    if(n_moves == rows * columns && !is_win()){
        for(int z = 0; z < 3; z++){
            for(int y = 0; y < 3; y++){
                used[z][y] = -1;
            }
        }
    }
    return n_moves == rows * columns && !is_win();
}

bool TicTacToeNumbers::game_is_over() {
    return is_win() || is_draw();
}

// TicTacToeNumbersPlayer class implementation

TicTacToeNumbersPlayer::TicTacToeNumbersPlayer(string n, vector<int> numbers)
        : Player<int>(n, 0), availableNumbers(numbers) {}

void TicTacToeNumbersPlayer::getmove(int& x, int& y) {
    cout << name << "'s turn. Available numbers: ";
    for (int num : availableNumbers)
        cout << num << " ";
    cout << endl;

    int number;
    cout << "Enter a number from your list: ";

    // Input validation for number
    while (true) {
        cin >> number;
        // Check if the input is a single digit and in the available numbers
        if (find(availableNumbers.begin(), availableNumbers.end(), number) == availableNumbers.end()) {
            cout << "Invalid number. Enter a single valid digit from your list: ";
        } else {
            break; // Valid input
        }
    }

    cout << "Enter row (0-2) and column (0-2) to place the number: ";

    // Input validation for row and column
    cin >> x >> y;
    while(!(boardPtr->update_board(x, y , -10))){
        cout << "Cell occupied please enter another cell:";
        cin >> x >> y;
    }

    // Remove the chosen number from the available list
    availableNumbers.erase(find(availableNumbers.begin(), availableNumbers.end(), number));
    symbol = number; // Set the player's symbol
    used_numbers.push_back(symbol);
}

// Random Player Implementation

TicTacToeNumbersRandomPlayer::TicTacToeNumbersRandomPlayer(string n, vector<int> numbers)
        : Player<int>(n, 0), availableNumbers(move(numbers)) {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator
}

void TicTacToeNumbersRandomPlayer::getmove(int& x, int& y) {
    if (availableNumbers.empty()) return; // No numbers left to play

    // Randomly select a number from the available list
    int idx = rand() % availableNumbers.size();
    symbol = availableNumbers[idx];
    availableNumbers.erase(availableNumbers.begin() + idx);
    used_numbers.push_back(symbol);

    // Randomly choose a valid position on the board
    x = rand() % 3;
    y = rand() % 3;
    while(!(boardPtr->update_board(x, y , -10))){
        x = rand() % 3;
        y = rand() % 3;
    }
    cout << name << " placed " << symbol << " at (" << x << ", " << y << ").\n";
}