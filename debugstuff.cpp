#include "debugstuff.h"

std::string str(Pos &p) {
    std::string s = "(row: ";
    s += (char)('0' + p.row);
    s += ", col: ";
    s += (char)('0' + p.col);
    s += ")";
    return s;
}

void print(Pos &p) {
    std::cout << str(p) << std::endl;
}

void print(std::list<Pos> &positions) {
    for (Pos p : positions){
        std::cout << str(p) << "  ";
    }
    std::cout << std::endl;
}

void print(Move &m) {
    std::cout << "[Type: " << m.move_type << " ";
    if (m.move_type == 'm' || m.move_type == 'e') {
        std::cout << " | From: " << str(m.from) << " | To: " << str(m.to) << "]"<< std::endl;
    }
    if (m.move_type == 'p') {
        std::cout << " | From: " << str(m.from) << " | To: " << str(m.to) << " | Promotes: " << m.promotion << "]" << std::endl;
    }
    if (m.move_type == 'c') {
        std::cout << " | kingside: " << m.castle_short << "]" << std::endl;
    }
}

void print(std::vector<Move> &moves) {
    std::cout << "Move list: " << std::endl;
    for (Move m : moves){
        print(m);
    }
    std::cout << std::endl;
}
void print(std::list<Move> &moves) {
    std::cout << "Move list: " << std::endl;
    for (Move m : moves){
        print(m);
    }
    std::cout << std::endl;
}