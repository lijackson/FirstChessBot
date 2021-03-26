#include "tests.h"

int TESTING_DELAY_MS = 300;

int main()
{
    GameBoard gb("r2qk2r/ppp2ppp/2np4/8/QbBPn1b1/2N2N2/PP1B1PPP/R3K2R b KQkq - 0 1");
    Renderer r(800, 800);

    std::vector<Move> moves = gb.all_moves();

    r.draw_board(gb.state);
    std::this_thread::sleep_for(std::chrono::milliseconds(TESTING_DELAY_MS));
    for (Move m : moves) {

        UnmakeData unmaker = gb.make_move(m);
        r.draw_board(gb.state);
        std::this_thread::sleep_for(std::chrono::milliseconds(TESTING_DELAY_MS));

        gb.unmake_move(unmaker);
        r.draw_board(gb.state);
        std::this_thread::sleep_for(std::chrono::milliseconds(TESTING_DELAY_MS));
    }

    return 0;
}