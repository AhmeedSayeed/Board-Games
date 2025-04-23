#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "bits\stdc++.h"
#include "BoardGame_Classes.h"

template <typename T>
class _3x3X_O_Board:public Board<T> {
public:
    _3x3X_O_Board();
    bool update_board(int x , int y , T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    T getcell(int x, int y);
};

template <typename T>
class _3x3X_O_Player : public Player<T> {
public:
    _3x3X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class _3x3X_O_Random_Player : public RandomPlayer<T>{
public:
    _3x3X_O_Random_Player(T symbol);
    void getmove(int &x, int &y);
};


// ----- 3x3_X_O_Tic_Tac_Toe Implementation -----

template <typename T>
_3x3X_O_Board<T>::_3x3X_O_Board()
{
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; ++i)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; ++j)
        {
            this->board[i][j] = '1' + j + (3*i);
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool _3x3X_O_Board<T>::update_board(int x, int y, T symbol) {
    if(x >= 0 && x <= 2 && y >= 0 && y <= 2 && this->board[x][y] >= '1' && this->board[x][y] <= '9')
    {
        this->board[x][y] = symbol;
        this->n_moves++;
        return 1;
    }
    return 0;
}


template <typename T>
void _3x3X_O_Board<T>::display_board()
{
    cout << "\n+---+---+---+\n";
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->columns; ++j)
        {
            if(!j)
                cout << "|";
            cout << " " << this->board[i][j] << " |";
        }
        cout << endl;
        cout << "+---+---+---+\n";
    }
    cout << endl;
}


template <typename T>
bool _3x3X_O_Board<T>::is_win()
{
    // Check rows and columns
    for (int i = 0; i < this->rows; i++)
    {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && (this->board[i][0] == 'X' || this->board[i][0] == 'O')) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && (this->board[0][i] == 'X' || this->board[0][i] == 'O')))
            return 1;
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && (this->board[0][0] == 'X' || this->board[0][0] == 'O')) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && (this->board[0][2] == 'X' || this->board[0][2] == 'O')))
        return 1;

    return 0;
}


template <typename T>
bool _3x3X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}


template <typename T>
bool _3x3X_O_Board<T>::game_is_over() {
    return (is_win() || is_draw());
}

template <typename T>
T _3x3X_O_Board<T>::getcell(int x, int y)
{
    return this->board[x][y];
}


// ----- 3x3_X_O_Tic_Tac_Toe_Player Implementation -----


template <typename T>
_3x3X_O_Player<T>::_3x3X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void _3x3X_O_Player<T>::getmove(int& x, int& y)
{
    cout << "\nPlease, enter a number of an empty cell:\n";
    int i;
    cin >> i;
    i--;
    x = i / 3 , y = i % 3;
}


// ----- 3x3_X_O_Tic_Tac_Toe_Random_Player Implementation -----

template <typename T>
_3x3X_O_Random_Player<T>::_3x3X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void _3x3X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H

