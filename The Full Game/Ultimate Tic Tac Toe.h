#ifndef TASK_2_ULTIMATE_TIC_TAC_TOE_H
#define TASK_2_ULTIMATE_TIC_TAC_TOE_H

#include <bits\stdc++.h>
#include "3x3X_O.h"
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class Ultimate_Tic_Tac_Toe_Board : public Board<T> {
private:
    int chosenDoard;
    _3x3X_O_Board<T> **boards;
public:
    Ultimate_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Ultimate_Tic_Tac_Toe_Player : public Player <T> {
public:
    Ultimate_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};


template <typename T>
class Ultimate_Tic_Tac_Toe_Random_Player : public RandomPlayer <T> {
public:
    Ultimate_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};



// ----- Ultimate_Tic_Tac_Toe Implementation -----

template <typename T>
Ultimate_Tic_Tac_Toe_Board<T>::Ultimate_Tic_Tac_Toe_Board()
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

    this->boards = new _3x3X_O_Board<char>*[this->rows * this->columns];
    for (int i = 0; i < this->rows * this->columns; ++i)
        this->boards[i] = new _3x3X_O_Board<char>();
}


template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol)
{
    chosenDoard = x / 10 , x %= 10;
    if(chosenDoard >= 0 && chosenDoard <= 8 && !this->boards[chosenDoard]->game_is_over() && this->boards[chosenDoard]->update_board(x,y,symbol)
    && this->board[chosenDoard/3][chosenDoard%3] >= '1' && this->board[chosenDoard/3][chosenDoard%3] <= '9')
    {
        if(this->boards[chosenDoard]->is_win())
            this->board[chosenDoard/3][chosenDoard%3] = symbol;
        else if(this->boards[chosenDoard]->is_draw())
            this->board[chosenDoard/3][chosenDoard%3] = 'D';
        this->n_moves++;
        return 1;
    }
    return 0;
}


template <typename T>
void Ultimate_Tic_Tac_Toe_Board<T>::display_board()
{
    // Print the main board
    cout << "\nThe main Board:";
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


    // Print all boards
    cout << "All Boards:\n";
    for (int i = 0; i < this->rows * this->columns; ++i)
    {
        cout << "+---+---+---+    +---+---+---+    +---+---+---+\n";
        for (int j = 0; j < this->rows * this->columns; ++j)
        {
            if (!(j%3))
            {
                if(j)
                    cout << "    ";
                cout << "|";
            }
            cout << " " << this->boards[3*(i/3) + j/3]->getcell(i%3,j%3) << " |";
        }
        if(!((i+1)%3) && i)
            cout << "\n+---+---+---+    +---+---+---+    +---+---+---+\n";
        cout << endl;
    }
    cout << endl;
}


template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_win()
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
bool Ultimate_Tic_Tac_Toe_Board<T>::is_draw()
{
    return (this->n_moves == 81 && !is_win());
}


template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::game_is_over(){
    return (is_win() || is_draw());
}


// ----- Ultimate_Tic_Tac_Toe_Board_Player Implementation -----

template <typename T>
Ultimate_Tic_Tac_Toe_Player<T>::Ultimate_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name,symbol){}

template <typename T>
void Ultimate_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y)
{
    int i , b;
    cout << "\nPlease, enter a number of a board:\n";
    cin >> b;
    cout << "\nPlease, enter a number of an empty cell in the chosen board:\n";
    cin >> i;
    i-- , b--;
    x = i / 3 , y = i % 3;
    x += 10 * b;
}


// ----- Ultimate_Tic_Tac_Toe_Random_Player Implementation -----

template <typename T>
Ultimate_Tic_Tac_Toe_Random_Player<T>::Ultimate_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Computer Player";
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(0)));
}


template <typename T>
void Ultimate_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y)
{
    int b = rand() % 9;
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    x += 10 * b;
}

#endif
