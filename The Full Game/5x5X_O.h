#ifndef _5X5X_O_H
#define _5X5X_O_H
#include "bits/stdc++.h"
#include "BoardGame_Classes.h"

int _5x5_n_moves;
int _5x5_random_player_counter = 1;

template <typename T>
class X_O_5x5_Board:public Board<T> {
public:
    X_O_5x5_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_5x5_Player : public Player<T> {
public:
    X_O_5x5_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_5x5_Random_Player : public RandomPlayer<T>{
public:
    X_O_5x5_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

///////////////////////// IMPLEMENTATION //////////

#include <bits/stdc++.h>
using namespace std;

// Constructor for X_O_5x5_Board
template <typename T>
X_O_5x5_Board<T>::X_O_5x5_Board() {
    this->rows = this->columns = 5;
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
bool X_O_5x5_Board<T>::update_board(int x, int y, T mark) {
    if (this->n_moves == 24)
    {
        this->n_moves = _5x5_n_moves = 25;
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
        _5x5_n_moves = this->n_moves;

        return true;
    }
    return false;
}

template <typename T>
void X_O_5x5_Board<T>::display_board() {
    if (this->n_moves == 25)
        return;
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (!this->board[i][j])
            {
                cout << "  " << (5*i + j + 1 < 10 ? " " : "") << 5*i + j + 1 << "   | ";
            }
            else
            {
                cout << "   "  << this->board[i][j] << "   | ";
            }
        }
        cout << "\n----------------------------------------------";
    }
    cout << endl;
}

template <typename T>
bool X_O_5x5_Board<T>::is_win() {
    auto isValid = [&](int x , int y) -> bool{
        return x >= 0 && x < this->rows && y >= 0 && y < this->columns;
    };

    const int dx[] = {0 , 1 , 1 , -1};
    const int dy[] = {1 , 1 , 0 , 1};
    int p1 = 0 , p2 = 0;

    auto count = [&](){
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                T symbol = this->board[i][j];
                for (int k = 0; k < 4; ++k) {
                    int nx1 = i + dx[k] , ny1 = j + dy[k];
                    int nx2 = i + 2*dx[k] , ny2 = j + 2*dy[k];
                    if (isValid(nx1 , ny1) && isValid(nx2 , ny2) && this->board[nx1][ny1] == symbol && this->board[nx2][ny2] == symbol && this->board[nx2][ny2] != 0)
                    {
                        if (symbol == 'X')
                        {
                            p1++;
                        }
                        else
                        {
                            p2++;
                        }
                    }
                }
            }
        }
    };

    if (this->n_moves < 24)
    {
        return false;
    }
    else if (this->n_moves == 24)
    {
        count();
        return p2 > p1;
    }
    else
    {
        count();
        return p2 < p1;
    }
}

template <typename T>
bool X_O_5x5_Board<T>::is_draw() {
    return this->n_moves == 25;
}

template <typename T>
bool X_O_5x5_Board<T>::game_is_over() {
    return this->n_moves == 25;
}


// Constructor for X_O_5x5_Player
template <typename T>
X_O_5x5_Player<T>::X_O_5x5_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_5x5_Player<T>::getmove(int& x, int& y) {
    if (_5x5_n_moves == 24)
        return;
    cout << "\nPlease enter your position (1 to 25): ";
    int pos; cin >> pos;
    x = (pos-1) / 5;
    y = (pos-1) % 5;
}

// Constructor for X_O_5x5_Random_Player
template <typename T>
X_O_5x5_Random_Player<T>::X_O_5x5_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player #" + to_string(_5x5_random_player_counter++);
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_5x5_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif //_5X5X_O_H
