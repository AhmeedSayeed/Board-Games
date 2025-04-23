#ifndef PYRAMIC_X_O_H
#define PYRAMIC_X_O_H

#include <bits\stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class Pyramic_X_O_Board : public Board <T> {
public:
    Pyramic_X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Pyramic_X_O_Player : public Player <T> {
public:
    Pyramic_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};


template <typename T>
class Pyramic_X_O_Random_Player : public RandomPlayer <T> {
public:
    Pyramic_X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};


// ----- Pyramic_X_O_Board Implementation -----

template <typename T>
Pyramic_X_O_Board<T>::Pyramic_X_O_Board()
{
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; ++i)
    {
        this->board[i] = new char[this->columns];
    }
    int cnt = 1;
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 2-i; j <= 2+i; ++j)
        {
            this->board[i][j] = '0' + cnt++;
        }
    }
}


template <typename T>
bool Pyramic_X_O_Board<T>::update_board(int x, int y, T symbol) {
    if(((x == 0 && y == 2) || (x == 1 && y >= 1 && y <= 3) || (x == 2 && y >= 0 && y <= 5)) && this->board[x][y] >= '1' && this->board[x][y] <= '9')
    {
        this->board[x][y] = symbol;
        this->n_moves++;
        return 1;
    }
    return 0;
}


template <typename T>
void Pyramic_X_O_Board<T>::display_board()
{
    cout << "---------------------\n";
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->columns; ++j)
        {
            if(j >= 2-i && j <= 2+i)
            {
                if(j == 2-i)
                    cout << "|";
                cout << " " << this->board[i][j] << " |";
            }
            else
            {
                cout << string(4,' ');
            }
        }
        cout << endl;
    }
    cout << "---------------------\n";
}


template <typename T>
bool Pyramic_X_O_Board<T>::is_win() {
    // Check Diagonals
    if(this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0] && this->board[0][2] > '9')
        return 1;
    if(this->board[0][2] == this->board[1][3] && this->board[0][2] == this->board[2][4] && this->board[0][2] > '9')
        return 1;

    // Check Columns
    if(this->board[0][2] == this->board[1][2] && this->board[0][2] == this->board[2][2] && this->board[0][2] > '9')
        return 1;

    // Check Rows
    if(this->board[1][1] == this->board[1][2] && this->board[1][1] == this->board[1][3] && this->board[1][1] > '9')
        return 1;
    for (int i = 0; i < 3; ++i)
    {
        bool eq = 1;
        for (int j = i+1; j < i+3; ++j)
        {
            if(this->board[2][j] != this->board[2][i])
                eq = 0;
        }
        if(eq)
            return 1;
    }
    return 0;
}


template <typename T>
bool Pyramic_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}


template <typename T>
bool Pyramic_X_O_Board<T>::game_is_over() {
    return (is_win() || is_draw());
}

// ----- Pyramic_X_O_Player Implementation -----

template <typename T>
Pyramic_X_O_Player<T>::Pyramic_X_O_Player(string name, T symbol) : Player<T>(name,symbol){}

template <typename T>
void Pyramic_X_O_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease, enter a number of an empty cell:\n";
    int i;
    cin >> i;
    if(i == 1)
        x = 0 , y = 2;
    else if(i >= 2 && i <= 4)
        x = 1 , y = i - 1;
    else
        x = 2 , y = i - 5;
}


// ----- Pyramic_X_O_Random_Player Implementation -----

template <typename T>
Pyramic_X_O_Random_Player<T>::Pyramic_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}


template <typename T>
void Pyramic_X_O_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % 3;
    y = rand() % 5;
}




#endif //PYRAMIC_X_O_H
