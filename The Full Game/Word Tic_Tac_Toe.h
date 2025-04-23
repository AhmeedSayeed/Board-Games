#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H

#include <bits\stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class Word_Tic_Tac_Toe_Board : public Board<T> {
private:
    string fileName;
    map <string,int> words;
public:
    Word_Tic_Tac_Toe_Board(string name);
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Word_Tic_Tac_Toe_Player : public Player <T> {
public:
    Word_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};


template <typename T>
class Word_Tic_Tac_Toe_Random_Player : public RandomPlayer <T> {
public:
    Word_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};



// ----- Word_Tic_Tac_Toe Implementation -----

template <typename T>
Word_Tic_Tac_Toe_Board<T>::Word_Tic_Tac_Toe_Board(string name) : fileName(name)
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

    ifstream gameWords{fileName};
    while(!gameWords.eof())
    {
        string s;
        gameWords >> s;
        words[s]++;
    }
}


template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol)
{
    if(x >= 0 && x <= 2 && y >= 0 && y <= 2 && this->board[x][y] >= '1' && this->board[x][y] <= '9')
    {
        this->board[x][y] = symbol;
        this->n_moves++;
        return 1;
    }
    return 0;
}


template <typename T>
void Word_Tic_Tac_Toe_Board<T>::display_board()
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
bool Word_Tic_Tac_Toe_Board<T>::is_win()
{
    // Check Diagonals
    string diag1 = string(1,this->board[0][0]) + string(1,this->board[1][1]) + string(1,this->board[2][2]);
    string diag2 = string(1,this->board[2][0]) + string(1,this->board[1][1]) + string(1,this->board[0][2]);
    if(words[diag1])
    {
        cout << "The win word is: " << diag1 << endl;
        return 1;
    }
    if(words[diag2])
    {
        cout << "The win word is: " << diag2 << endl;
        return 1;
    }
    reverse(diag1.begin(),diag1.end()) , reverse(diag2.begin(),diag2.end());
    if(words[diag1])
    {
        cout << "The win word is: " << diag1 << endl;
        return 1;
    }
    if(words[diag2])
    {
        cout << "The win word is: " << diag2 << endl;
        return 1;
    }

    // Check rows
    for (int i = 0; i < this->rows; ++i)
    {
        string word = string(1, this->board[i][0]);
        for (int j = 1; j < this->columns; ++j)
            word += string(1,this->board[i][j]);
        if(words[word])
        {
            cout << "The win word is: " << word << endl;
            return 1;
        }
        reverse(word.begin(),word.end());
        if(words[word])
        {
            cout << "The win word is: " << word << endl;
            return 1;
        }
    }

    // Check columns
    for (int j = 0; j < this->columns; ++j)
    {
        string word = string(1,this->board[0][j]);
        for (int i = 1; i < this->rows; ++i)
            word += string(1,this->board[i][j]);
        if(words[word])
        {
            cout << "The win word is: " << word << endl;
            return 1;
        }
        reverse(word.begin(),word.end());
        if(words[word])
        {
            cout << "The win word is: " << word << endl;
            return 1;
        }
    }
    return 0;
}


template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}


template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::game_is_over(){
    return (is_win() || is_draw());
}


// ----- Word_Tic_Tac_Toe_Player Implementation -----

template <typename T>
Word_Tic_Tac_Toe_Player<T>::Word_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name,symbol){}

template <typename T>
void Word_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease, enter a number of an empty cell:\n";
    int i;
    cin >> i;
    i--;
    x = i / 3 , y = i % 3;

    char c;
    while(1)
    {
        cout << "Please, enter the character you want to put:\n";
        cin >> c;
        if(isalpha(c))
            break;
    }
    this->symbol = toupper(c);
}


// ----- Word_Tic_Tac_Toe_Random_Player Implementation -----

template <typename T>
Word_Tic_Tac_Toe_Random_Player<T>::Word_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Computer Player";
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(0)));
}


template <typename T>
void Word_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = (rand() % 26) + 'A';
}

#endif //WORD_TIC_TAC_TOE_H
