#include <iostream>
#include "board.h"
#include <fstream>
#include <utils.h>

extern Board board;

int bd_init()
{
    auto &alivePieces = board.alivePieces;

	//Add pawns
	for (int i = 0; i < 4; i++)
	{
		bd_makePiece(white, pawn, i, 1);
		bd_makePiece(black, pawn, i, 5);
		
		bd_makePiece(white, static_cast<PieceType>(4 - i), i, 0);
		bd_makePiece(black, static_cast<PieceType>(i + 1), i, 6);
	}

	bd_build();

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
		if (alivePieces[i].x == x && alivePieces[i].y == y && alivePieces[i].alive)
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
	board.toMove = static_cast<PieceColor>(!board.toMove);
}

void bd_destroy(Piece &piece)
{
	piece.alive = false;
	bd_build();
}

void bd_build()
{
	for (Piece &piece : board.alivePieces)
		if (piece.alive)
			board.board[piece.x][piece.y] = &piece;
}

void bd_save()
{
	std::ofstream save_file("./save/save.txt");

	save_file << board.toMove << "\n";

	for (Piece& piece : board.alivePieces)
	{
		save_file << piece.alive << " " << piece.hasMoved << " " << piece.player_color << " " << piece.type << " " << piece.x << " " << piece.y << "\n";

	}

	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++)
			save_file << board.board[i][j] << " ";
		save_file << "\n";
	}*/
	save_file.close();

}

void bd_clear()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 7; j++)
			board.board[i][j] = nullptr;
}

void bd_load_save()
{
	bd_clear();

	std::ifstream save_file("./save/save.txt");

	int color; 
	save_file >> color;
	board.toMove = static_cast<PieceColor>(color);

	for (Piece& piece : board.alivePieces)
	{
		int type;
		save_file >> piece.alive >> piece.hasMoved >> color >> type >> piece.x >> piece.y;
		piece.player_color = static_cast<PieceColor>(color);
		piece.type = static_cast<PieceType>(type);

		bd_move(piece, piece.x, piece.y);
		
	}


	bd_build();

	save_file.close();
}
