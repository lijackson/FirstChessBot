#ifndef DEBUGSTUFF_H
#define DEBUGSTUFF_H

#include "GameBoard.h"
#include "Renderer.h"
#include "ChessAI.h"
#include <vector>
#include <list>
#include <iostream>
#include <string>

std::string str(Pos &p);

void print(Pos &p);

void print(std::list<Pos> &positions);

void print(Move &m);

void print(std::vector<Move> &moves);

void print(std::list<Move> &moves);

#endif