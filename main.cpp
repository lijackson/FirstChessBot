#include "tests.h"
#include "debugstuff.h"

int main()
{
    GameBoard gb("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Renderer rend(800, 800);
    ChessAI ai = ChessAI();

    rend.draw_board(gb);
    
    while (true) {
        Move m = ai.best_move(gb, 4);
        gb.make_move(m);
        rend.draw_board(gb);
    }

    return 0;
}