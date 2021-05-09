#include <iostream>
#include <vector>
#include <math.h>
#include "game-runner.h"
#include "board.h"

extern Board board;

bool isLegal(const Piece piece, int x, int y)
{
	if (x == piece.x && y == piece.y)
		return false;

	const Piece* other = bd_getPieceAtCords(x, y);

	if (other && other->player_color == piece.player_color)
	{
		return false;
	}

	int xs = (piece.x < x) ? 1 : -1, ys = (piece.y < y) ? 1 : -1;
	int dx = abs(x - piece.x), dy = abs(y - piece.y);
	int fwds = 2 * piece.player_color - 1;

	switch (piece.type)
	{
	case king:
		return abs(x - piece.x) <= 1 && abs(y - piece.y) <= 1;

	case rook:
		if (x == piece.x)
		{
			for (int i = piece.y + ys; i != y; i += ys)
				if (board.board[x][i])
						return false;
		}
		else if (y == piece.y)
		{
			for (int i = piece.x + xs; i != x; i += xs)
				if (board.board[i][y])
						return false;
		}
		else
			return false;
		break;
	
	case bishop:
		if (abs(x - piece.x) != abs(y - piece.y))
			return false;

		for (int i = piece.x + xs, j = piece.y + ys; i < x; i += xs, j += ys)
			if (board.board[i][j])
				return false;
		break;
	
	case knight:
		return dx && dy && dx + dy == 3;
	
	case pawn:
		if (x == piece.x && !board.board[x][y])
		{
			if (y == piece.y + fwds)
				return true;
			
			if (y == piece.y + 2 * fwds)
				return !piece.hasMoved;
		}
		return y == piece.y + fwds && dx == 1 && other;
	}
	
	return true;
}
