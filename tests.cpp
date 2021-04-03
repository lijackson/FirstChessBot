#include "tests.h"
#include "debugstuff.h"

int TESTING_DELAY_MS = 500;

int main()
{
    GameBoard gb("r3k2r/p1ppqpb1/Bn2pnp1/3PN3/1p2P3/2N2Q1p/PPP2PPP/R3K2R b KQkq - 0 1");
    Renderer r(800, 800);
    ChessAI ai = ChessAI();

    r.draw_board(gb);
    

    // std::vector<Move> moves = gb.all_moves();
    // for (Move m : moves) {
    //     print(m);

    //     UnmakeData unmaker = gb.make_move(m);
    //     r.draw_board(gb);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(TESTING_DELAY_MS));

    //     gb.unmake_move(unmaker);
    //     r.draw_board(gb);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(TESTING_DELAY_MS));
    // }


    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //while (r.is_open()) {
    Move m = ai.best_move(gb, 4);
    UnmakeData unmaker = gb.make_move(m);
    r.draw_board(gb);
    std::this_thread::sleep_for(std::chrono::milliseconds(TESTING_DELAY_MS));

    return 0;
}