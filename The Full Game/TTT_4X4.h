#ifndef TTT_4X4_H
#define TTT_4X4_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>


class TTT_4X4 : public Board<char> {
public:
    TTT_4X4();
    bool update_board(int x, int y, char symbol) override;
    bool check_board(int x, int y ,char symbol);
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class TTT_4X4Player : public Player<char> {
public:
    vector<int> availableNumbers;
    // Constructor
    TTT_4X4Player(string n, char symbol);
    bool is_valid(int x, int y ,int w, int z);
    bool is_in_cell(int x, int y);
    // Prompt the player for a move
    void getmove(int& x, int& y) override;
};

class TTT_4X4RandomPlayer : public RandomPlayer<char> {
public:
    TTT_4X4RandomPlayer(string name , char symbol);
    bool is_valid(int x, int y , int w ,int z);
    bool is_in_cell(int x, int y);
    void getmove(int& x, int& y) override;
};


#endif // TTT_4X4_H
