#pragma once
#include <iostream>
#include <vector>
#include <board.h>

bool isLegal(const Piece piece, int x, int y);

bool isInCheck(PieceColor color);
