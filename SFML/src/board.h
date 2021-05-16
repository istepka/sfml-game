#pragma once
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
	PieceType type;
	PieceColor player_color;
	int x = -1; //cords on board like A5, but translated properly
	int y = -1;
	bool hasMoved = false;
	bool alive = true;
};

struct Board
{
    Piece* board[4][7];
	Piece* king[2];
    std::vector<Piece> alivePieces;
	std::vector<Piece> prevState;
	PieceColor toMove = white;
};

int bd_init();

Piece* bd_getPieceAtCords(int x, int y);

std::vector<Piece> &bd_getPiecesOnBoard();

int bd_getPieceIndex(int x, int y);

void bd_makePiece(PieceColor color, PieceType type, int x, int y);

void bd_move(Piece &piece, int x, int y);

void bd_destroy(Piece &piece);

void bd_build();

void bd_undo();

void bd_save();
void bd_load_save();
void bd_new_game();
