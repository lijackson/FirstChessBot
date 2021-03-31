#ifndef CHESSAI_H
#define CHESSAI_H

#include <iostream>
#include "GameBoard.h"

class ChessAI {
private:
    // This provides the actual functionality of the best_move() function
    Move minimax(int alpha, int beta, GameBoard gb);

public:
    ChessAI();

    // Gets the best move from a given gameboard
    Move best_move(GameBoard gb);

    // Returns a score for a given GameBoard to evaluate how good the position is
    int score(GameBoard gb);

};

#endif