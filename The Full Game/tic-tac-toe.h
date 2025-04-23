#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

class TicTacToeNumbers : public Board<int> {

public:
    TicTacToeNumbers();
    bool update_board(int x, int y, int symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    // Evaluation function
};

class TicTacToeNumbersPlayer : public Player<int> {
private:
    vector<int> availableNumbers;

public:
    TicTacToeNumbersPlayer(string n, vector<int> numbers);

    void getmove(int& x, int& y) override;
};

class TicTacToeNumbersRandomPlayer : public Player<int> {
private:
    vector<int> availableNumbers; // To store the numbers the player can use
    vector<int> used_numbers;
public:
    TicTacToeNumbersRandomPlayer(string n, vector<int> numbers);

    void getmove(int& x, int& y) override;
};


#endif // TIC_TAC_TOE_H
