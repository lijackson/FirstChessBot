#ifndef CHESSAI_H
#define CHESSAI_H

#include <iostream>
#include <vector>
#include <cmath>
#include "GameBoard.h"

struct MovePriority {
    Move move;
    int priority;
    MovePriority() {};
    MovePriority(Move &m, int p) {
        move = m;
        priority = p;
    }
};

struct Score {
    int val;
    Score *tiebreak;
    Score();
    Score(int v, Score *t) {
        val = v;
        tiebreak = t;
    }
};

class ChessAI {
    private:
    // This provides the actual functionality of the best_move() function
    int minimax(int alpha, int beta, GameBoard &gb, int depth);

    // TODO Sorts the moves in a helpful order to speed up alpha-beta pruning
    // void sort_moves(std::vector<Move> *moves, GameBoard &gb);

    // These store weights for each piece
    double pawn_weight = 100;
    double knight_weight = 300;
    double bishop_weight = 300;
    double rook_weight = 500;
    double queen_weight = 900;

    public:
    ChessAI();

    // Gets the best move from a given gameboard
    Move best_move(GameBoard &gb, int depth);

    // Returns a score for a given GameBoard to evaluate how good the position is
    int score(GameBoard &gb);

};

#endif