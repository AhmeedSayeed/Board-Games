#include <iostream>
#include "BoardGame_Classes.h"
#include "5x5X_O.h"
#include "3x3_inv_X_O.h"
#include "Pyramic X_O.h"
#include "Word Tic_Tac_Toe.h"
#include "Ultimate Tic Tac Toe.h"
#include "tic-tac-toe.h"
#include "TTT_4X4.h"
#include "connect4.h"

using namespace std;

void Game_1(string name1 , string name2 , string type1 , string type2 , string sym1 , string sym2 , Player<char>*players[2])
{
    Pyramic_X_O_Board <char> * B = new Pyramic_X_O_Board<char>();

    if (type1 == "1")
    {
        players[0] = new Pyramic_X_O_Player(name1,sym1[0]);
    }
    else
    {
        players[0] = new Pyramic_X_O_Random_Player(sym1[0]);
    }

    if (type2 == "1")
    {
        players[1] = new Pyramic_X_O_Player(name2,sym2[0]);
    }
    else
    {
        players[1] = new Pyramic_X_O_Random_Player(sym2[0]);
    }

    GameManager<char> pyramic_x_o_game(B, players);
    pyramic_x_o_game.run();

    delete B;
    for (int i = 0; i < 2; ++i)
        players[i] = nullptr;
}

void Game_2(string name1 , string name2 , string type1 , string type2 , string sym1 , string sym2 , Player<char>*players[2])
{
    Connect4* connect4Board = new Connect4();

    if (type1 == "1")
    {
        players[0] = new Connect4Player(name1,sym1[0]);
    }
    else
    {
        players[0] = new Connect4RandomPlayer(name1 , sym1[0]);
    }

    if (type2 == "1")
    {
        players[1] = new Connect4Player(name2,sym2[0]);
    }
    else
    {
        players[1] = new Connect4RandomPlayer(name2 , sym2[0]);
    }

    GameManager<char> x_o_game(connect4Board, players);
    x_o_game.run();

    delete connect4Board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Game_3(string name1 , string name2 , string type1 , string type2 , string sym1 , string sym2 , Player<char>*players[2])
{
    X_O_5x5_Board<char>* B = new X_O_5x5_Board<char>();

    if (type1 == "1")
    {
        players[0] = new X_O_5x5_Player(name1,sym1[0]);
    }
    else
    {
        players[0] = new X_O_5x5_Random_Player(sym1[0]);
    }

    if (type2 == "1")
    {
        players[1] = new X_O_5x5_Player(name2,sym2[0]);
    }
    else
    {
        players[1] = new X_O_5x5_Random_Player(sym2[0]);
    }

    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Game_4(string name1 , string name2 , string type1 , string type2 , string sym1 , string sym2 , Player<char>*players[2])
{
    string filename;
    while(1)
    {
        cout << "Please, enter the file name contains game words:\n";
        getline(cin , filename);
        ifstream file{filename};
        if(!file.is_open())
        {
            cout << "Error, the file can't be opened (may be it doesn't exist)." <<endl;
            continue;
        }
        break;
    }

    Word_Tic_Tac_Toe_Board <char> * B = new Word_Tic_Tac_Toe_Board<char>(filename);

    if (type1 == "1")
    {
        players[0] = new Word_Tic_Tac_Toe_Player(name1,sym1[0]);
    }
    else
    {
        players[0] = new Word_Tic_Tac_Toe_Random_Player(sym1[0]);
    }

    if (type2 == "1")
    {
        players[1] = new Word_Tic_Tac_Toe_Player(name2,sym2[0]);
    }
    else
    {
        players[1] = new Word_Tic_Tac_Toe_Random_Player(sym2[0]);
    }


    GameManager<char> word_tic_tac_toe_game(B, players);
    word_tic_tac_toe_game.run();

    delete B;
    for (int i = 0; i < 2; ++i)
        players[i] = nullptr;

}

void Game_5(string name1 , string name2 , string type1 , string type2)
{
    TicTacToeNumbers* ticTacToeBoard = new TicTacToeNumbers();

    Player<int>*players[2];


    vector<int> player1Numbers = {1, 3, 5, 7, 9};
    vector<int> player2Numbers = {0, 2, 4, 6, 8};

    if (type1 == "1")
    {
        players[0] = new TicTacToeNumbersPlayer(name1,player1Numbers);
    }
    else
    {
        players[0] = new TicTacToeNumbersRandomPlayer(name1,player1Numbers);
    }

    if (type2 == "1")
    {
        players[1] = new TicTacToeNumbersPlayer(name2,player2Numbers);
    }
    else
    {
        players[1] = new TicTacToeNumbersRandomPlayer(name2,player2Numbers);
    }

    GameManager<int> x_o_game(ticTacToeBoard, players);
    x_o_game.run();

    delete ticTacToeBoard;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Game_6(string name1 , string name2 , string type1 , string type2 , string sym1 , string sym2 , Player<char>*players[2])
{
    X_O_3x3_inv_Board<char>* B = new X_O_3x3_inv_Board<char>();

    if (type1 == "1")
    {
        players[0] = new X_O_3x3_inv_Player(name1,sym1[0]);
    }
    else
    {
        players[0] = new X_O_3x3_inv_Random_Player(sym1[0]);
    }

    if (type2 == "1")
    {
        players[1] = new X_O_3x3_inv_Player(name2,sym2[0]);
    }
    else
    {
        players[1] = new X_O_3x3_inv_Random_Player(sym2[0]);
    }

    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Game_7(string name1 , string name2 , string type1 , string type2 , string sym1 , string sym2 , Player<char>*players[2])
{
    TTT_4X4* TTT_4X4_Board = new TTT_4X4();

    if (type1 == "1")
    {
        players[0] = new TTT_4X4Player(name1,sym1[0]);
    }
    else
    {
        players[0] = new TTT_4X4RandomPlayer(name1,sym1[0]);
    }

    if (type2 == "1")
    {
        players[1] = new TTT_4X4Player(name2,sym2[0]);
    }
    else
    {
        players[1] = new TTT_4X4RandomPlayer(name2,sym2[0]);
    }

    GameManager<char> x_o_game(TTT_4X4_Board, players);
    x_o_game.run();

    delete TTT_4X4_Board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Game_8(string name1 , string name2 , string type1 , string type2 , string sym1 , string sym2 , Player<char>*players[2])
{
    Ultimate_Tic_Tac_Toe_Board <char> * B = new Ultimate_Tic_Tac_Toe_Board<char>();

    if (type1 == "1")
    {
        players[0] = new Ultimate_Tic_Tac_Toe_Player(name1,sym1[0]);
    }
    else
    {
        players[0] = new Ultimate_Tic_Tac_Toe_Random_Player(sym1[0]);
    }

    if (type2 == "1")
    {
        players[1] = new Ultimate_Tic_Tac_Toe_Player(name2,sym2[0]);
    }
    else
    {
        players[1] = new Ultimate_Tic_Tac_Toe_Random_Player(sym2[0]);
    }

    GameManager<char> Ultimate_Tic_Tac_Toe_game(B, players);
    Ultimate_Tic_Tac_Toe_game.run();

    delete B;
    for (int i = 0; i < 2; ++i)
        players[i] = nullptr;
}

void menuOfGames()
{
    cout << "------- The Games -------" <<endl;
    cout << "1) Pyramic Tic-Tac-Toe." <<endl;
    cout << "2) Four-in-a-row." <<endl;
    cout << "3) 5 x 5 Tic Tac Toe." <<endl;
    cout << "4) Word Tic-tac-toe." <<endl;
    cout << "5) Numerical Tic-Tac-Toe." <<endl;
    cout << "6) Misere Tic Tac Toe." <<endl;
    cout << "7) 4 x 4 Tic-Tac-Toe." <<endl;
    cout << "8) Ultimate Tic Tac Toe." <<endl;
    cout << "9) Back." <<endl;
}

void menu()
{
    cout << "----------- The Menu -----------" <<endl;
    cout << "1) Edit players information." <<endl;
    cout << "2) Open the menu of the games." <<endl;
    cout << "3) Exit." <<endl;
}

bool validChoice(int start , int end , string s)
{
    if (s.empty())
        return false;
    for (auto ch : s)
    {
        if (!isdigit(ch))
            return false;
    }
    return stoi(s) >= start && stoi(s) <= end;
}

void playersInfo(string name1 , string name2 , string type1 , string type2 , string sym1 , string sym2)
{
    cout << "Player 1 information : " <<endl;
    cout << "Name : " << name1 << '.' <<endl;
    cout << "Type : " << (type1 == "1" ? "Human." : "Random Player.") <<endl;
    cout << "Symbol : " << sym1 << '.' <<endl;
    cout << "----------------------------------------" <<endl;

    cout << "Player 2 information : " <<endl;
    cout << "Name : " << name2 << '.' <<endl;
    cout << "Type : " << (type2 == "1" ? "Human." : "Random Player.") <<endl;
    cout << "Symbol : " << sym2 << '.'<<endl;
    cout << "----------------------------------------" <<endl;
}

void editPlayersInfo(string &name1 , string &name2 , string &type1 , string &type2 , string &sym1 , string &sym2)
{
    auto validChar = [](string s) -> bool {
        return s.size() == 1 && !isdigit(s[0]);
    };

    cout << "Please, enter the name of the first player :" <<endl;
    getline(cin , name1);

    auto typePlayer1 = [&](){
        cout << "Please, choose the type of the first player :" <<endl;
        cout << "1) Human." <<endl;
        cout << "2) Random Player." <<endl;
        cout << "Please, enter your choice :" <<endl;
        getline(cin , type1);
    };

    typePlayer1();
    while (!validChoice(1 , 2 , type1))
    {
        cout << "Error, your input must be 1 or 2." <<endl;
        typePlayer1();
    }

    cout << "Please, enter the symbol of the first player (only one non-digit character) :" <<endl;
    getline(cin , sym1);
    while (!validChar(sym1))
    {
        cout << "Error, your input must be only one non-digit character." <<endl;
        getline(cin , sym1);
    }

    cout << "Please, enter the name of the second player :" <<endl;
    getline(cin , name2);

    while (name2 == name1)
    {
        cout << "Error, the names of the 2 players are the same." <<endl;
        cout << "Please, enter the name of the second player :" <<endl;
        getline(cin , name2);
    }

    auto typePlayer2 = [&](){
        cout << "Please, choose the type of the second player :" <<endl;
        cout << "1) Human." <<endl;
        cout << "2) Random Player." <<endl;
        cout << "Please, enter your choice :" <<endl;
        getline(cin , type2);
    };
    typePlayer2();
    while (!validChoice(1 , 2 , type2))
    {
        cout << "Error, your input must be 1 or 2." <<endl;
        typePlayer2();
    }

    cout << "Please, enter the symbol of the second player (only one non-digit character) :" <<endl;
    getline(cin , sym2);
    while (true)
    {
        bool ext = true;
        while (!validChar(sym2))
        {
            cout << "Error, your input must be only one non-digit character." <<endl;
            getline(cin , sym2);
        }
        while (sym2 == sym1)
        {
            cout << "Error, The symbols of the 2 players are the same." <<endl;
            cout << "Please, enter the symbol of the second player (only one non-digit character) :" <<endl;
            getline(cin , sym2);
            ext = false;
        }
        if (ext)
            break;
    }

    playersInfo(name1 , name2 , type1 , type2 , sym1 , sym2);
}

int main() {
    // ANA ==> Ahmed , Nour , Abdelrahman
    cout << "--- Welcome to ANA games app ---" <<endl;
    cout << "--------------------------------" <<endl;

    Player<char>* players[2];
    string player1Name, player2Name , type1 , type2 , sym1 , sym2;
    bool assigned = false;

    while (true)
    {
        if (!assigned)
        {
            editPlayersInfo(player1Name , player2Name , type1 , type2 , sym1 , sym2);
            assigned = true;
        }
        else
        {
            string chMenu;
            menu();
            cout << "Please, enter your choice : " <<endl;
            getline(cin , chMenu);


            while (!validChoice(1 , 3 , chMenu))
            {
                cout << "Error, your input must be from 1 to 3." <<endl;
                getline(cin , chMenu);
            }
            if (chMenu == "1")
            {
                editPlayersInfo(player1Name , player2Name , type1 , type2 , sym1 , sym2);
            }
            else if (chMenu == "2")
            {
                string chGame;
                menuOfGames();
                cout << "Please, enter your choice : " <<endl;
                getline(cin , chGame);
                while (!validChoice(1 , 9 , chGame))
                {
                    cout << "Error, your input must be from 1 to 9." <<endl;
                    getline(cin , chGame);
                }
                if (chGame == "1")
                {
                    Game_1(player1Name , player2Name , type1 , type2 , sym1 , sym2 , players);
                }
                else if (chGame == "2")
                {
                    Game_2(player1Name , player2Name , type1 , type2 , sym1 , sym2 , players);
                }
                else if (chGame == "3")
                {
                    Game_3(player1Name , player2Name , type1 , type2 , sym1 , sym2 , players);
                }
                else if (chGame == "4")
                {
                    Game_4(player1Name , player2Name , type1 , type2 , sym1 , sym2 , players);
                }
                else if (chGame == "5")
                {
                    Game_5(player1Name , player2Name , type1 , type2);
                }
                else if (chGame == "6")
                {
                    Game_6(player1Name , player2Name , type1 , type2 , sym1 , sym2 , players);
                }
                else if (chGame == "7")
                {
                    Game_7(player1Name , player2Name , type1 , type2 , sym1 , sym2 , players);
                }
                else if (chGame == "8")
                {
                    Game_8(player1Name , player2Name , type1 , type2 , sym1 , sym2 , players);
                }

                cin.ignore();
            }
            else
            {
                cout << "Thank you for using our app." <<endl;
                return 0;
            }
        }
    }
}