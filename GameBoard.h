#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <string>
#include <tuple>

char col_to_sqr(int col);
char row_to_sqr(int row);
int sqr_to_col(char col);
int sqr_to_row(char row);

// The gameboard class stores all the information necessary about a particular gameboard in an organized format
class GameBoard {
    
    public:
    
    char state[8][8] = {};
    bool castling[4] = {0, 0, 0, 0}; // {K, Q, k, q} aka {white kingside, white queenside, black kingside, black queenside}
    int en_passant = -1; // 16 potential en_passant positions: {0: a6, 1: b6, ..., 15: h3}, and -1 is none
    bool check[2] = {0, 0};
    bool white_turn = 1;
    int half_move_clock = 0;
    int moves_made = 0;

    GameBoard(std::string FEN);

};

#endif