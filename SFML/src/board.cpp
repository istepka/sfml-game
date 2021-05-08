#include <iostream>
#include "board.h"

extern Board board;

int bd_init()
{
    auto &alivePieces = board.alivePieces;

    // for (size_t i = 0; i < 7; i++)
	// {
	// 	for (size_t j = 0; j < 4; j++)
	// 	{
	// 		board.board[i][j] = nullptr;
	// 	}
	// }

	//Add pawns
	for (int i = 0; i < 4; i++)
	{
		bd_makePiece(white, pawn, i, 1);
		bd_makePiece(black, pawn, i, 5);
		
		bd_makePiece(white, static_cast<PieceType>(4 - i), i, 0);
		bd_makePiece(black, static_cast<PieceType>(i + 1), i, 6);
	}

	for (Piece &piece : board.alivePieces)
	{
		board.board[piece.x][piece.y] = &piece;
	}

	//Print alive pieces to debug
	for (int i = 0; i < alivePieces.size(); i++)
	{
		std::cout << alivePieces[i].player_color << std::endl;
	}

	return 1;
}

void bd_makePiece(PieceColor color, PieceType type, int x, int y)
{
	Piece pc = {
		type,
		color,
		x,
		y
	};

	board.alivePieces.push_back(pc);
}

/// <summary>
/// Get piece at x,y. Return found struct.
/// </summary>
Piece* bd_getPieceAtCords(int x, int y)
{
	return board.board[x][y];
}


std::vector<Piece> &bd_getPiecesOnBoard()
{
	return board.alivePieces;
}


int bd_getPieceIndex(int x, int y)
{
    auto &alivePieces = board.alivePieces;

	for (int i = 0; i < alivePieces.size(); i++)
	{
		if (alivePieces[i].x == x && alivePieces[i].y == y)
		{
			return i;
		}
	}
	
	return -1;
}

void bd_move(Piece &piece, int x, int y)
{
	piece.hasMoved = true;
    board.board[x][y] = &piece;
    board.board[piece.x][piece.y] = nullptr;
}
