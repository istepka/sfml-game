#include <vector>
#include "game-runner.h"
#include <iostream>

void _render_pieces()
{
	std::vector<Piece> Pieces = bd_getPiecesOnBoard();

	for (int i = 0; i < Pieces.size(); i++)
	{
		std::cout << Pieces[i].x << std::endl;
	}
}