#include <iostream>
#include <game-runner.h>
#include <SFML/Graphics.hpp>
#include <utils.h>

extern int BOARD_OFFSET_Y, BOARD_OFFSET_X;
extern int SINGLE_TILE_WIDTH , SINGLE_TILE_HEIGHT ;


void movePieceToTile(int dest_x, int dest_y, sf::Sprite *pieceSprite, struct Piece *pieceStruct)
{
	

	std::cout << "Moved "<<  pieceStruct->piece_type <<" to " << dest_x <<"," <<dest_y << std::endl;
	pieceStruct->x = dest_x;
	pieceStruct->y = dest_y;

	pieceSprite->setPosition(  BOARD_OFFSET_X + 40 + SINGLE_TILE_WIDTH * pieceStruct->x, BOARD_OFFSET_Y + 40 + SINGLE_TILE_HEIGHT * pieceStruct->y );

	//PiecesSprites[i].setPosition(BOARD_OFFSET_X + 40 + SINGLE_TILE_WIDTH * Pieces[i].x, BOARD_OFFSET_Y + 35 + SINGLE_TILE_HEIGHT * Pieces[i].y);
}



std::vector<int> calculateBoardClickedTile(int x, int y)
{
	
	x = x - 40 - BOARD_OFFSET_X;
	x /= SINGLE_TILE_WIDTH;
	y = y - 40 - BOARD_OFFSET_Y;
	y = y / SINGLE_TILE_HEIGHT;

	return std::vector<int> {x, y};
}


