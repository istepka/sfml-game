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


std::vector< std::vector<int> > board(7, std::vector<int>(4));

std::vector<Piece> alivePieces;

int initBoard()
{
	struct Piece king;
	

	for (size_t i = 0; i < 7; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << board[i][j] << " " ;
		}
		std::cout << std::endl;
	}


	//Add pawns
	for (int i = 0; i < 4; i++)
	{

		struct Piece piece;
		piece.piece_type = PieceType::pawn;
		piece.player_color = PieceColor::white;
		piece.x = i;
		piece.y = 1;
		alivePieces.push_back(piece);
		piece.player_color = PieceColor::black;
		piece.y = 5;
		alivePieces.push_back(piece);

		
		switch (i)
		{
			case 0:
			{
				piece.piece_type = PieceType::rook;
				piece.player_color = PieceColor::black;
				piece.y = 6;
				alivePieces.push_back(piece);
				piece.piece_type = PieceType::king;
				piece.player_color = PieceColor::white;
				piece.y = 0;
				alivePieces.push_back(piece);
				break;
			}
			case 1:
			{
				piece.piece_type = PieceType::knight;
				piece.player_color = PieceColor::black;
				piece.y = 6;
				alivePieces.push_back(piece);
				piece.piece_type = PieceType::bishop;
				piece.player_color = PieceColor::white;
				piece.y = 0;
				alivePieces.push_back(piece);
				break;
			}
			case 2:
			{
				piece.piece_type = PieceType::bishop;
				piece.player_color = PieceColor::black;
				piece.y = 6;
				alivePieces.push_back(piece);
				piece.piece_type = PieceType::knight;
				piece.player_color = PieceColor::white;
				piece.y = 0;
				alivePieces.push_back(piece);
				break;
			}
			case 3:
			{
				piece.piece_type = PieceType::king;
				piece.player_color = PieceColor::black;
				piece.y = 6;
				alivePieces.push_back(piece);
				piece.piece_type = PieceType::rook;
				piece.player_color = PieceColor::white;
				piece.y = 0;
				alivePieces.push_back(piece);
				break;
			}

		}

	}


	//Print alive pieces to debug
	for (int i = 0; i < alivePieces.size(); i++)
	{
		std::cout << alivePieces[i].player_color << std::endl;
	}
	
	return 1;
}


/// <summary>
/// Get piece at x,y. Return found struct.
/// </summary>
struct Piece getPieceAtCords(int x, int y)
{
	for (int i = 0; i < alivePieces.size(); i++)
	{
		if (alivePieces[i].x == x && alivePieces[i].y == y)
		{
			return alivePieces[i];
		}
	}
	struct Piece found;
	return found;
}


std::vector<Piece> getPiecesOnBoard()
{
	return alivePieces;
}


