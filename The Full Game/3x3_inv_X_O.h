#ifndef _3X3_INV_X_O_H
#define _3X3_INV_X_O_H

#include "BoardGame_Classes.h"

bool winner;
int inv_3x3_n_moves;
int inv_3x3_random_player_counter = 1;

template <typename T>
class X_O_3x3_inv_Board:public Board<T> {
public:
    X_O_3x3_inv_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_3x3_inv_Player : public Player<T> {
public:
    X_O_3x3_inv_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_3x3_inv_Random_Player : public RandomPlayer<T>{
public:
    X_O_3x3_inv_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


///////////////////////// IMPLEMENTATION //////////

#include <bits/stdc++.h>
using namespace std;

// Constructor for X_O_3x3_inv_Board
template <typename T>
X_O_3x3_inv_Board<T>::X_O_3x3_inv_Board() {
    this->rows = this->columns = 3;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = static_cast<char *>(new char[this->columns]);
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_3x3_inv_Board<T>::update_board(int x, int y, T mark) {
    if (winner)
    {
        inv_3x3_n_moves++;
        return true;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        inv_3x3_n_moves = this->n_moves;
        return true;
    }
    return false;
}



template <typename T>
void X_O_3x3_inv_Board<T>::display_board() {
    if (winner)
    {
        return;
    }
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (!this->board[i][j])
            {
                cout << "  " << 3*i + j + 1 << "   | ";
            }
            else
            {
                cout << "  " << this->board[i][j] << "   | ";
            }
        }
        cout << "\n-------------------------";
    }
    cout << endl;
}

template <typename T>
bool X_O_3x3_inv_Board<T>::is_win() {

    if (winner && inv_3x3_n_moves != this->n_moves)
    {
        return true;
    }

    auto isValid = [&](int x , int y) -> bool{
        return x >= 0 && x < this->rows && y >= 0 && y < this->columns;
    };

    const int dx[] = {0 , 1 , 1 , -1};
    const int dy[] = {1 , 1 , 0 , 1};

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            T symbol = this->board[i][j];
            for (int k = 0; k < 4; ++k) {
                int nx1 = i + dx[k] , ny1 = j + dy[k];
                int nx2 = i + 2*dx[k] , ny2 = j + 2*dy[k];
                if (isValid(nx1 , ny1) && isValid(nx2 , ny2) && this->board[nx1][ny1] == symbol && this->board[nx2][ny2] == symbol && this->board[nx2][ny2] != 0)
                {
                    winner = true;
                    return false;
                }
            }
        }
    }
    return false;
}

template <typename T>
bool X_O_3x3_inv_Board<T>::is_draw() {
    return !is_win() && this->n_moves == (winner ? 10 : 9);
}

template <typename T>
bool X_O_3x3_inv_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


// Constructor for X_O_3x3_inv_Player
template <typename T>
X_O_3x3_inv_Player<T>::X_O_3x3_inv_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_3x3_inv_Player<T>::getmove(int& x, int& y) {
    if (winner)
    {
        return;
    }
    cout << "\nPlease enter your position (1 to 9): ";
    int pos; cin >> pos;
    x = (pos-1) / 3;
    y = (pos-1) % 3;
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_3x3_inv_Random_Player<T>::X_O_3x3_inv_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player #" + to_string(inv_3x3_random_player_counter++);
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_3x3_inv_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


#endif //_3X3_INV_X_O_H
