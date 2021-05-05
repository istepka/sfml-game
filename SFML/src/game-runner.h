#pragma once
#include <iostream>
#include <vector>
enum PieceType {
	pawn,
	rook,
	knight,
	bishop,
	king
};

enum PieceColor {
	black,
	white
};
struct Piece {
	PieceType piece_type;
	PieceColor player_color;
	int x = -1; //cords on board like A5, but translated properly
	int y = -1;
};


int initBoard();
struct Piece getPieceAtCords(int x, int y);
std::vector< struct Piece> getPiecesOnBoard();
int getPieceIndex(int x, int y);