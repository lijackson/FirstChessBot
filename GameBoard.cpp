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
    return (int)(col - 'a');
}
int sqr_to_row(char row) {
    return (int)('8' - row);
}

// Initialize the piece -> positions map
char pieces[12] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};

GameBoard::GameBoard(std::string FEN) {

    for (int i = 0; i < 12; i++) {
        positions_of[pieces[i]] = std::vector<Pos>();
    }

    // Stores what step of the filling process we are on so one loop through the chars can read all the information
    int info_filled = 0;

    // This stores the coords of the square that is currently being filled on the board
    int temp_col = 0;
    int temp_row = 0;

    // Read each char in the FEN string
    for (char c : FEN) {
        if (temp_col + temp_row < 15) {

            // A number, x, in FEN means that the next x squares in the row are empty
            if (c <= '8' && c >= '1') {
                for (int i = 0; i < c - '0'; i++) {
                    state[temp_row][temp_col] = ' ';
                    temp_col++;
                }

            // A / in FEN means to move to the next row in the board. Extraneous info, but helps with consistency and reading
            } else if (c == '/') { // "temp_x == 7" also works as a conditional but this is more consistent
                temp_row++;
                temp_col = 0;

            // If neither of these special coniditions are met, fill the current square with a piece and continue
            } else {
                state[temp_row][temp_col] = c;
                positions_of[c].push_back(Pos(temp_row, temp_col));
                temp_col++;
            }

        // After all piece location info is filled, extra info needs to be read as well
        } else {

            // In FEN, a space indicates a new block of information to read
            if (c == ' ') info_filled++;

            // This reads whos turn it is
            else if (info_filled == 1 && c == 'w') white_turn = 1;
            else if (info_filled == 1 && c == 'b') white_turn = 0;

            // This reads castling rights
            else if (info_filled == 2 && c == 'K') castling[0] = 1;
            else if (info_filled == 2 && c == 'Q') castling[1] = 1;
            else if (info_filled == 2 && c == 'k') castling[2] = 1;
            else if (info_filled == 2 && c == 'q') castling[3] = 1;

            // en_passant is saved as an integer because there are limited options; this converts to the correct number
            else if (info_filled == 3 && c != '-') {en_passant += 1 + sqr_to_col(c); info_filled++;} // +1 to balance -1 intial value
            else if (info_filled == 4 && c != '-') en_passant += sqr_to_row(c) * 10;
            
            // Fills the half move clock and how many moves have been made
            // I might be using a weird way of turning a string into an int, don't judge me
            else if (info_filled == 5) half_move_clock = half_move_clock * 10 + (int)(c - '0');
            else if (info_filled == 6) moves_made = moves_made * 10 + (int)(c - '0');
            
        }
    }
};

UnmakeData GameBoard::make_move(Move move) {
    if (move.move_type == 'c') {
        return make_castle_move(move.castle_short);
    } else if (move.move_type == 'p') {
        return make_promotion_move(move.from, move.to, move.promotion);
    } else if (move.move_type == 'e') {
        return make_en_passant_move(move.from, move.to);
    }
    // The default is to just treat the move like a coordinate move
    return make_coordinate_move(move.from, move.to);
}

UnmakeData GameBoard::make_coordinate_move(Pos from_pos, Pos to_pos) {

    // Create a reference to the relevant information to unmake the move easily if necessary
    UnmakeData unmaker;

    SqrData to(to_pos, get_piece((to_pos)));
    unmaker.squares.push_back(to);

    SqrData from(from_pos, get_piece(from_pos));
    unmaker.squares.push_back(from);

    for (int i = 0; i < 4; i++) {unmaker.prev_castling[i] = castling[i];};
    unmaker.prev_en_passant = en_passant;

    // Update relevant board state information
    char type = tolower(get_piece(from_pos));

    if (type == 'k' || (type == 'r' && from_pos.col == 0))
        castling[!white_turn * 2] = 0;
    if (type == 'k' || (type == 'r' && from_pos.col == 7))
        castling[!white_turn * 2 + 1] = 0;

    if (tolower(get_piece(to_pos)) == 'r' && to_pos.col == 0)
        castling[white_turn * 2] = 0;
    if (tolower(get_piece(to_pos)) == 'r' && to_pos.col == 7)
        castling[white_turn * 2 + 1] = 0;

    
    en_passant = -1;
    if (type == 'p' && abs(from_pos.row - to_pos.row) == 2)
        en_passant = from_pos.col + from_pos.row * 10;

    white_turn = !white_turn;

    // Make the move on the board
    state[to_pos.row][to_pos.col] = state[from_pos.row][from_pos.col];
    state[from_pos.row][from_pos.col] = ' ';

    return unmaker;
};

UnmakeData GameBoard::make_en_passant_move(Pos from_pos, Pos to_pos) {

    // Create a reference to the relevant information to unmake the move easily if necessary
    UnmakeData unmaker;

    SqrData to(to_pos, ' ');
    unmaker.squares.push_back(to);

    SqrData from(from_pos, get_piece(from_pos));
    unmaker.squares.push_back(from);

    SqrData captured(Pos(from_pos.row, to_pos.col), state[from_pos.row][to_pos.col]);
    unmaker.squares.push_back(captured);

    for (int i = 0; i < 4; i++) {unmaker.prev_castling[i] = castling[i];};
    unmaker.prev_en_passant = en_passant;

    // Update relevant board state information
    en_passant = -1;

    white_turn = !white_turn;

    // Make the move on the board
    state[to_pos.row][to_pos.col] = state[from_pos.row][from_pos.col];
    state[from_pos.row][from_pos.col] = ' ';
    state[from_pos.row][to_pos.col] = ' ';

    return unmaker;
};

UnmakeData GameBoard::make_castle_move(bool castle_short) {
    int row = 7 * white_turn;

    // Create a reference to the relevant information to unmake the move easily if necessary
    UnmakeData unmaker;

    SqrData king_sqr(row, 4, state[row][4]);
    unmaker.squares.push_back(king_sqr);

    SqrData rook_sqr(row, castle_short * 7, state[row][castle_short * 7]);
    unmaker.squares.push_back(rook_sqr);
    
    SqrData empty_one(row, 2 + castle_short * 4, ' ');
    unmaker.squares.push_back(empty_one);

    SqrData empty_two(row, 1 + castle_short * 4, ' ');
    unmaker.squares.push_back(empty_two);

    if (!castle_short) {
        SqrData empty_three(row, 3, ' ');
        unmaker.squares.push_back(empty_three);
    }

    for (int i = 0; i < 4; i++) {unmaker.prev_castling[i] = castling[i];};
    unmaker.prev_en_passant = en_passant;

    // Update relevant board state information
    castling[!white_turn * 2] = 0;
    castling[!white_turn * 2 + 1] = 0;
    white_turn = !white_turn;
    en_passant = -1;

    // Make the move on the board
    state[row][2 + castle_short * 4] = state[row][4];
    state[row][3 + castle_short * 2] = state[row][castle_short * 7];
    state[row][4] = ' ';
    state[row][castle_short * 7] = ' ';

    return unmaker;
}

UnmakeData GameBoard::make_promotion_move(Pos from_pos, Pos to_pos, char to_type) {

    // Create a reference to the relevant information to unmake the move easily if necessary
    UnmakeData unmaker;

    SqrData to(to_pos, ' ');
    unmaker.squares.push_back(to);

    SqrData from(from_pos, get_piece(from_pos));
    unmaker.squares.push_back(from);

    for (int i = 0; i < 4; i++) {unmaker.prev_castling[i] = castling[i];};
    unmaker.prev_en_passant = en_passant;

    // Update relevant board state information
    white_turn = !white_turn;
    en_passant = -1;

    // Make the move on the board
    state[to_pos.row][to_pos.col] = to_type;
    state[from_pos.row][from_pos.col] = ' ';

    return unmaker;
}

void GameBoard::unmake_move(UnmakeData unmaker) {
    for (SqrData sqr : unmaker.squares) {
        state[sqr.sqr.row][sqr.sqr.col] = sqr.piece;
    }
    for (int i = 0; i < 4; i++) {castling[i] = unmaker.prev_castling[i];};
    en_passant = unmaker.prev_en_passant;
    white_turn = !white_turn;
}

std::vector<Move> GameBoard::all_moves() {
    std::vector<Move> moves;
    for (int i = 6 * !white_turn; i < 6 + 6 * !white_turn; i++) {
        for (Pos p : positions_of[pieces[i]]) {
            for (Move m : valid_moves(p)) {
                moves.push_back(m);
            }
        }
    }
    return moves;
}

std::vector<Move> GameBoard::valid_moves(Pos pos) {

    char piece = tolower(get_piece(pos));

    if (piece == 'p') 
        return pawn_moves(pos);
    if (piece == 'n') 
        return knight_moves(pos);
    if (piece == 'b') 
        return bishop_moves(pos);
    if (piece == 'r') 
        return rook_moves(pos);
    if (piece == 'q') 
        return queen_moves(pos);
    if (piece == 'k') 
        return king_moves(pos);

    return std::vector<Move>();
}

std::vector<Move> GameBoard::pawn_moves(Pos pos) {

    std::vector<Move> moves;
    int dir = 1 - white_turn * 2;

    // Moving forward
    if (state[pos.row + dir][pos.col] == ' ') {
        if (pos.row + dir == !white_turn * 7) {
            // Promotion
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col), (char)('q' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col), (char)('n' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col), (char)('r' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col), (char)('b' + 26*white_turn)));
        } else {
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col)));
            if (pos.row == 1 + 5*white_turn && state[pos.row + 2*dir][pos.col] == ' ') {
                moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + 2*dir, pos.col)));
            }
        }
    }

    // Capturing
    char left_cap = state[pos.row + dir][pos.col - 1];
    if (opposite_color(get_piece(pos), left_cap)) {
        if (pos.row + dir == !white_turn * 7) {
            // Promotion
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1), (char)('q' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1), (char)('r' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos. col), Pos(pos.row + dir, pos.col - 1), (char)('n' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1), (char)('b' + 26*white_turn)));
        } else {
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1)));
        }
    }
    char right_cap = state[pos.row + dir][pos.col + 1];
    if (opposite_color(get_piece(pos), right_cap)) {
        if (pos.row + dir == !white_turn * 7) {
            // Promotion
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1), (char)('q' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1), (char)('r' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1), (char)('n' + 26*white_turn)));
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1), (char)('b' + 26*white_turn)));
        } else {
            moves.push_back(Move(Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col + 1)));
        }
    }

    // en passant capturing
    if (en_passant == (pos.row + dir) * 10 + (pos.col + 1))
        moves.push_back(Move('e', Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col + 1)));
    if (en_passant == (pos.row + dir) * 10 + (pos.col - 1))
        moves.push_back(Move('e', Pos(pos.row, pos.col), Pos(pos.row + dir, pos.col - 1)));

    return moves;

}

std::vector<Move> GameBoard::knight_moves(Pos pos) {
    std::vector<Move> moves;

    std::vector<Pos> knight_offsets = {Pos(-2, -1), Pos(-2, 1), Pos(-1, 2), Pos(1, 2), Pos(2, 1), Pos(2, -1), Pos(1, -2), Pos(-1, -2)};

    for (Pos offset : knight_offsets) {
        Pos new_pos = offset + pos;
        // Checks if the move is on the board, and then checks if it isn't already occupied by a piece of the same color
        if (is_on_board(new_pos) && !same_color(get_piece(new_pos), get_piece(pos))) {
            moves.push_back(Move(pos, new_pos));
        }
    }

    return moves;
}

std::vector<Move> GameBoard::bishop_moves(Pos pos) {
    std::vector<Move> moves;

    std::vector<Pos> bishop_offsets = {Pos(-1, -1), Pos(-1, 1), Pos(1, 1), Pos(1, -1)};

    for (Pos offset : bishop_offsets) {
        Pos new_pos = pos + offset;
        while (is_on_board(new_pos)) {
            if (same_color(get_piece(pos), get_piece(new_pos))) break;

            moves.push_back(Move(pos, new_pos));

            if (opposite_color(get_piece(pos), get_piece(new_pos))) break;

            new_pos = new_pos + offset;
        }
    }
    
    return moves;
}

std::vector<Move> GameBoard::rook_moves(Pos pos) {
    std::vector<Move> moves;

    std::vector<Pos> rook_offsets = {Pos(-1, 0), Pos(0, 1), Pos(1, 0), Pos(0, -1)};

    for (Pos offset : rook_offsets) {
        Pos new_pos = pos + offset;
        while (is_on_board(new_pos)) {
            if (same_color(get_piece(pos), get_piece(new_pos))) break;

            moves.push_back(Move(pos, new_pos));

            if (opposite_color(get_piece(pos), get_piece(new_pos))) break;

            new_pos = new_pos + offset;
        }
    }
    
    return moves;
}

std::vector<Move> GameBoard::queen_moves(Pos pos) {
    // Queen moves can just be generated by combining bishop and rook moves
    std::vector<Move> moves = bishop_moves(pos);
    for (Move m : rook_moves(pos)) {
        moves.push_back(m);
    }    
    return moves;
}

std::vector<Move> GameBoard::king_moves(Pos pos) {
    std::vector<Move> moves;

    std::vector<Pos> king_offsets = {Pos(-1, -1), Pos(-1, 1), Pos(1, 1), Pos(1, -1), Pos(-1, 0), Pos(0, 1), Pos(1, 0), Pos(0, -1)};

    for (Pos offset : king_offsets) {
        Pos new_pos = pos + offset;
        if (is_on_board(new_pos) && !same_color(get_piece(pos), get_piece(new_pos)))
            moves.push_back(Move(pos, new_pos));
    }

    if (castling[2 - 2 * white_turn] && state[pos.row][5] == ' ' && state[pos.row][6] == ' ') {
        moves.push_back(Move(true));
    }

    if (castling[3 - 2 * white_turn] && state[pos.row][3] == ' ' && state[pos.row][2] == ' ' && state[pos.row][1] == ' ') {
        moves.push_back(Move(false));
    }
    
    return moves;
}

void GameBoard::display() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            std::cout << state[r][c];
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}