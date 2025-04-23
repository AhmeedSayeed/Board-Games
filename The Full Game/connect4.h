#ifndef CONNECT4_H
#define CONNECT4_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>

class Connect4 : public Board<char> {
public:
    Connect4();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class Connect4Player : public Player<char> {
public:
    vector<int> availableNumbers;

    // Constructor
    Connect4Player(string n, char symbol);

    // Prompt the player for a move
    void getmove(int& x, int& y) override;
};

class Connect4RandomPlayer : public RandomPlayer<char> {
public:
    Connect4RandomPlayer(string name , char symbol);
    void getmove(int& x, int& y) override;
};

#endif // CONNECT4_H