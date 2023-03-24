#include "ChessAI.h"
#include "debugstuff.h"

ChessAI::ChessAI() {

}

Move ChessAI::best_move(GameBoard &gb, int depth) {
    std::vector<Move> moves = gb.legal_moves();
    //sort_moves(&moves, gb);
    if (moves.size() == 0) exit(1);
    Move best = moves[0];
    int best_score = (gb.white_turn * INT32_MIN) + (!gb.white_turn * INT32_MAX);

    int alpha = INT32_MIN;
    int beta = INT32_MAX;

    for (int i = 0; i < moves.size(); i++) {
        UnmakeData unmaker = gb.make_move(moves[i]);
        std::cout << "considering move: ";
        print(moves[i]);
        int score = minimax(alpha, beta, gb, depth - 1);
        // Opposite of expected players turn because the board state is AFTER they made a move (this confused me for a while)
        if ((!gb.white_turn && score > best_score) || (gb.white_turn && score < best_score)) {
            best = moves[i];
            best_score = score;
            // AB pruning
            if (gb.white_turn)
                beta = score;
            else
                alpha = score;
        }
        gb.unmake_move(unmaker);
    }
    std::cout << "Best score found: " << best_score << '\n';
    return best;
}

int ChessAI::minimax(int alpha, int beta, GameBoard &gb, int depth) {
    if (depth <= 0) {
        // Not fast enough to implement this yet. Maybe after sorting
        //if (!gb.just_captured)
            return score(gb);
    }
    int best_score;

    auto moves = gb.legal_moves();
    //sort_moves(&moves, gb);
    
    if (gb.white_turn) {
        best_score = INT32_MIN;
        for (Move m : moves) {
            // Make move
            UnmakeData unmaker = gb.make_move(m);

            // Finding a prescore (if the king has been taken, theres no need to continue checking moves)
            int current_score = score(gb);
            if (abs(current_score) != 100000)
                current_score = minimax(alpha, beta, gb, depth - 1);

            // Recursive minimax
            best_score = std::max(best_score, current_score);
            gb.unmake_move(unmaker);

            // Alpha beta pruning implementation
            alpha = std::max(alpha, best_score);
            if (alpha >= beta || best_score == 100000)
                break;
        }
    } else {
        best_score = INT32_MAX;
        for (Move m : moves) {
            // Make move
            UnmakeData unmaker = gb.make_move(m);

            // Finding a prescore (if the king has been taken, theres no need to continue checking moves)
            int current_score = score(gb);
            if (abs(current_score) != 100000)
                current_score = minimax(alpha, beta, gb, depth - 1);

            // Recursive minimax
            best_score = std::min(best_score, minimax(alpha, beta, gb, depth - 1));
            gb.unmake_move(unmaker);

            // Alpha beta pruning implementation
            beta = std::min(beta, best_score);
            if (alpha >= beta || best_score == -100000)
                break;
        }
    }

    return best_score;
}

int val(char p) {
    switch (tolower(p)) {
        case 'q':
            return 900;
        case 'r':
            return 500;
        case 'b':
            return 310;
        case 'n':
            return 300;
        case 'p':
            return 100;
    }
    return 0;
}

int cmpfunc (MovePriority &a, MovePriority &b) {
   return ( a.priority - b.priority );
}

int ChessAI::score(GameBoard &gb) {
    int s = 0;

    if (gb.positions_of['k'].size() == 0) return 100000;
    if (gb.positions_of['K'].size() == 0) return -100000;
    
    // Value of pawns
    s += gb.positions_of['P'].size() * pawn_weight;
    s -= gb.positions_of['p'].size() * pawn_weight;

    // Value of knights
    s += gb.positions_of['N'].size() * knight_weight;
    s -= gb.positions_of['n'].size() * knight_weight;

    // Value of bishops
    s += gb.positions_of['B'].size() * bishop_weight;
    s -= gb.positions_of['b'].size() * bishop_weight;

    // Value of rooks
    s += gb.positions_of['R'].size() * rook_weight;
    s -= gb.positions_of['r'].size() * rook_weight;

    // Value of queen
    s += gb.positions_of['Q'].size() * queen_weight;
    s -= gb.positions_of['q'].size() * queen_weight;

    // Advancing pawns is good
    for (auto p : gb.positions_of['P'])
        s += (p.row);
    for (auto p : gb.positions_of['p'])
        s -= (8-p.row);

    // Being on the edge is bad for N
    for (Pos p : gb.positions_of['N'])
        s -= abs(p.row*2 - 7) + abs(p.col*2 - 7);
    for (Pos p : gb.positions_of['n'])
        s += abs(p.row*2 - 7) + abs(p.col*2 - 7);
    
    // Being on the edge is bad for B
    for (Pos p : gb.positions_of['B'])
        s -= (abs(p.row*2 - 7) + abs(p.col*2 - 7)) / 2;
    for (Pos p : gb.positions_of['b'])
        s += (abs(p.row*2 - 7) + abs(p.col*2 - 7)) / 2;

    return s;
}