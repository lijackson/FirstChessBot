#include <iostream>
#include <string>
#include <tuple>


char col_to_sqr(int col) {
    char cols[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    return cols[coords[0]];
}
char row_to_sqr(int row) {
    char rows[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    return rows[7-coords[1]];
}

int col_to_coords(char col) {
    return (int)(c - 'a');
}
int col_to_coords(char row) {
    return (int)('8' - row);
}

class GameBoard {
    public:
    char state[8][8] = {};
    bool castling[4] = {0, 0, 0, 0}; // {K, Q, k, q} aka {white kingside, white queenside, black kingside, black queenside}
    int en_passant = -1; // 16 potential en_passant positions: {0: a6, 1: b6, ..., 15: h3}, and -1 is none
    bool check[2] = {0, 0};
    bool white_turn = 1;
    int half_move_clock = 0;
    int moves_made = 0;

    GameBoard(std::string FEN) {

        int info_filled = 0;

        std::string half_move_clock_str;
        std::string moves_made_str;

        int temp_x = 0;
        int temp_y = 0;
        for (char c : FEN) {
            if (temp_x + temp_y < 14) {
                if (c <= '8' && c >= '1') {
                    for (int i = 0; i < c - '0'; i++) {
                        state[temp_x][temp_y] = ' ';
                        temp_x++
                    }
                } else if (c == '/') {
                    temp_y++;
                    temp_x = 0;
                } else {
                    state[temp_x][temp_y] = c;
                    temp_x++
                }

            } else {
                if (c == ' ') info_filled++;

                else if (info_filled == 1 && c == 'w') white_turn == 1;
                else if (info_filled == 1 && c == 'b') white_turn == 0;

                else if (info_filled == 2 && c == 'K') castling[0] == 1;
                else if (info_filled == 2 && c == 'Q') castling[1] == 1;
                else if (info_filled == 2 && c == 'k') castling[2] == 1;
                else if (info_filled == 2 && c == 'q') castling[3] == 1;
                
                else if (info_filled == 3 && c != '-') en_passant += 1 + col_to_coords(c); // +1 to balance -1 intial value
                else if (info_filled == 4 && c != '-') en_passant += row_to_coords(c);
                else if (info_filled == 3) info_filled++;

                else if (info_filled == 5) {half_move_clock_str.append(c)};
                else if (info_filled == 6) {moves_made_str.append(c)};
            }
        }
        half_move_clock = Integer.parseInt(half_move_clock_str);
        moves_made = Integer.parseInt(moves_made_str);
    }
};