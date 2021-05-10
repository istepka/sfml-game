#pragma once
#include <iostream>
#include <vector>
#include "board.h"

struct GameState
{
    PieceColor activePlayer;
	unsigned int turn;
};

bool isLegal(const Piece piece, int x, int y);
