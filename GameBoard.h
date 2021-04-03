#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <list>
#include <map>

char col_to_sqr(int col);
char row_to_sqr(int row);
int sqr_to_col(char col);
int sqr_to_row(char row);

// This just helps to deal with coordinates
struct Pos {
    int row;
    int col;
    Pos() {}
    Pos(int r, int c) {
        row = r;
        col = c;
    }
    Pos operator+(const Pos& p_rhs) {
        return Pos(row + p_rhs.row, col + p_rhs.col);
    }
    bool operator==(const Pos& p_rhs) {
        return row == p_rhs.row && col == p_rhs.col;
    }
};

// This stores the information for a move
struct Move {
    char move_type; // 'p' for promotion, 'c' for castle, 'e' for an en passant capture, 'm' for a regular move
    bool castle_short = 0;
    char promotion = ' ';
    bool is_capture = 0;
    Pos from;
    Pos to;
    Move() {}
    Move(Pos p_from, Pos p_to, bool cap) {
        move_type = 'm';
        from = p_from;
        to = p_to;
        is_capture = cap;

    }
    Move(char p_move_type, Pos p_from, Pos p_to) {
        move_type = p_move_type; // made to be used for move_type = 'e', but this is a little bit more dynamic
        from = p_from;
        to = p_to;
        is_capture = 1;
    }
    Move(Pos p_from, Pos p_to, char piece, bool cap) {
        move_type = 'p';
        from = p_from;
        to = p_to;
        promotion = piece;
        is_capture = cap;
    }
    Move(bool kingside) {
        move_type = 'c';
        castle_short = kingside;
        is_capture = 0;
    }
};

// This stores information for an individual square. This helps the UnmakeData struct store previous data
struct SqrData {
    Pos sqr;
    char piece;
    SqrData(int r, int c, char p) {
        sqr.row = r;
        sqr.col = c;
        piece = p;
    }
    SqrData(Pos pos, char p) {
        sqr = pos;
        piece = p;
    }
};

// This saves data from a move made on a board to efficiently unmake the move instead of copying the whole board
struct UnmakeData {
    std::vector<SqrData> squares;
    int prev_en_passant;
    bool prev_castling[4];
};

// The gameboard class stores all the information necessary about a particular gameboard in an organized format
class GameBoard {
    private:
    struct UnmakeData unmaker;

    // Helper function for make_move that deals with all the standard moves
    UnmakeData make_coordinate_move(Pos from_pos, Pos to_pos);

    // Helper function for make_move that deals with castling moves
    UnmakeData make_castle_move(bool castle_short);

    // Helper function for make_move that deals with castling moves
    UnmakeData make_promotion_move(Pos from_pos, Pos to_pos, char to_type);

    // Helper function for make_move that deals with en passant moves
    UnmakeData make_en_passant_move(Pos from_pos, Pos to_pos);
    
    public:

    // Saves the contents of each square
    char state[8][8] = {};

    // Provides bidirectional mapping from piece -> positions because that is faster in some algorithms
    std::map<char, std::list<Pos>> positions_of;

    // Storing other information about the game
    bool castling[4] = {1, 1, 1, 1}; // {K, Q, k, q} aka {white kingside, white queenside, black kingside, black queenside}
    int en_passant = -1; // 16 potential en_passant positions: {20: a6, 21: b6, ..., 57: h3}, and -1 is none
    bool check[2] = {0, 0};
    bool white_turn = 1;
    bool just_captured = 0;
    int half_move_clock = 0;
    int moves_made = 0;

    // Initializes a gameboard from FEN notation
    GameBoard(std::string FEN);

    // Makes a move on the board but DOESNT CHECK IF IT IS A VALID MOVE
    UnmakeData make_move(Move move);

    // Unmakes a move with the given UnmakeData
    void unmake_move(UnmakeData unmaker);

    // Gets a complete list of all pseudo-legal moves for a player
    std::vector<Move> all_moves();

    // Gets a complete list of all actually legal moves for a player
    std::vector<Move> legal_moves();

    // Get the valid moves of the piece at a position
    std::vector<Move> valid_moves(Pos pos);

    // Get the valid moves for a pawn at a position
    std::vector<Move> pawn_moves(Pos pos);

    // Get the valid moves for a knight at a position
    std::vector<Move> knight_moves(Pos pos);

    // Get the valid moves for a bishop at a position
    std::vector<Move> bishop_moves(Pos pos);

    // Get the valid moves for a rook at a position
    std::vector<Move> rook_moves(Pos pos);

    // Get the valid moves for a queen at a position
    std::vector<Move> queen_moves(Pos pos);

    // Get the valid moves for a pawn at a position
    std::vector<Move> king_moves(Pos pos);

    // Display the board state in the terminal for debugging
    void display();

    // Gets the piece at a Pos
    char get_piece(Pos pos) {
        return state[pos.row][pos.col];
    }

    // Determines if a piece is white
    bool is_white(char p) {
        return toupper(p) == p;
    }

    // Determines if two pieces are of the same color
    bool same_color(char p1, char p2) {
        if (p1 == ' ' || p2 == ' ') return 0;
        return is_white(p1) == is_white(p2);
    }

    // Determines if two pieces are of opposite colors
    bool opposite_color(char p1, char p2) {
        if (p1 == ' ' || p2 == ' ') return 0;
        return is_white(p1) != is_white(p2);
    }

    // Helper function to determine if a position is in the range of the board
    bool is_on_board(Pos pos) {
        return pos.row >= 0 && pos.row < 8 && pos.col >= 0 && pos.col < 8;
    }
};

#endif