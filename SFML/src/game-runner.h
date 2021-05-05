#pragma once
int initBoard();
struct Piece getPieceAtCords(int x, int y);
std::vector<Piece> getPiecesOnBoard();

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
