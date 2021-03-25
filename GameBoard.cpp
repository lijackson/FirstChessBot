#include "GameBoard.h"

char col_to_sqr(int col) {
    char cols[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    return cols[cols[0]];
}
char row_to_sqr(int row) {
    char rows[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    return rows[7-rows[1]];
}

int sqr_to_col(char col) {
    return (int)(col - 'a' + 1);
}
int sqr_to_row(char row) {
    return (int)('8' - row);
}

GameBoard::GameBoard(std::string FEN) {

    // Stores what step of the filling process we are on so one loop through the chars can read all the information
    int info_filled = 0;

    // This stores the coords of the square that is currently being filled on the board
    int temp_x = 0;
    int temp_y = 0;

    // Read each char in the FEN string
    for (char c : FEN) {
        if (temp_x + temp_y < 15) {

            // A number, x, in FEN means that the next x squares in the row are empty
            if (c <= '8' && c >= '1') {
                for (int i = 0; i < c - '0'; i++) {
                    state[temp_x][temp_y] = ' ';
                    temp_x++;
                }

            // A / in FEN means to move to the next row in the board. Extraneous info, but helps with consistency and reading
            } else if (c == '/') { // "temp_x == 7" should also work as a conditional but this is consistent with my convention
                temp_y++;
                temp_x = 0;

            // If neither of these special coniditions are met, fill the current square with a piece and continue
            } else {
                state[temp_x][temp_y] = c;
                temp_x++;
            }

        // After all piece location info is filled, extra info needs to be read as well
        } else {
            // In FEN, a space indicates a new block of information to read
            if (c == ' ') info_filled++;

            // This reads whos turn it is
            else if (info_filled == 1 && c == 'w') white_turn == 1;
            else if (info_filled == 1 && c == 'b') white_turn == 0;

            // This reads castling rights
            else if (info_filled == 2 && c == 'K') castling[0] == 1;
            else if (info_filled == 2 && c == 'Q') castling[1] == 1;
            else if (info_filled == 2 && c == 'k') castling[2] == 1;
            else if (info_filled == 2 && c == 'q') castling[3] == 1;
            
            // en_passant is saved as an integer because there are limited options; this converts to the correct number
            else if (info_filled == 3 && c != '-') en_passant += 1 + sqr_to_col(c); // +1 to balance -1 intial value
            else if (info_filled == 4 && c != '-') en_passant += (sqr_to_row(c) == 6) * 8;

            // This catches the case that no en_passant square is selected, and skips the second en_passant step
            else if (info_filled == 3) info_filled++;
            
            // Fills the half move clock and how many moves have been made
            // I might be using a weird way of turning a string into an int, don't judge me
            else if (info_filled == 5) half_move_clock = half_move_clock * 10 + (int)(c - '0');
            else if (info_filled == 6) moves_made = moves_made * 10 + (int)(c - '0');
        }
    }
};