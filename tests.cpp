#include "tests.h"

int main()
{

    GameBoard gb("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Renderer r(800, 800);
    /*
    char b1[8][8]= {{'q', 'k', ' ', ' ', ' ', 'Q', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', 'p', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', 'R', ' ', 'K', ' '}};
    */

    while (r.is_open())
    {
        r.draw_board(gb.state);
    }

    return 0;
}