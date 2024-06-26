#include <iostream>
#include <game-runner.h>
#include <SFML/Graphics.hpp>
#include <utils.h>

extern int BOARD_OFFSET_Y, BOARD_OFFSET_X;
extern int SINGLE_TILE_WIDTH , SINGLE_TILE_HEIGHT ;


void move_piece_to_tile(int dest_x, int dest_y, sf::Sprite &pieceSprite, struct Piece &pieceStruct)
{
	std::cout << "Moved "<<  pieceStruct.type <<" to " << dest_x <<"," <<dest_y << std::endl;

	pieceSprite.setPosition(  BOARD_OFFSET_X + 40 + SINGLE_TILE_WIDTH * pieceStruct.x, BOARD_OFFSET_Y + 35 + SINGLE_TILE_HEIGHT * pieceStruct.y );


}



std::vector<int> calculate_clicked_tile_on_borad(int x, int y)
{
	if (x < BOARD_OFFSET_X + 40 || x > BOARD_OFFSET_X + 40 + 4 * SINGLE_TILE_WIDTH || y < BOARD_OFFSET_Y + 40 || y > BOARD_OFFSET_Y + 40 + 7 * SINGLE_TILE_HEIGHT)
		return std::vector<int> {-1, -1};
	x = x - 40 - BOARD_OFFSET_X;
	x /= SINGLE_TILE_WIDTH;
	y = y - 40 - BOARD_OFFSET_Y;
	y = y / SINGLE_TILE_HEIGHT;

	return std::vector<int> {x, y};
}


