#include <iostream>
#include <game-runner.h>
#include <SFML/Graphics.hpp>
void move_piece_to_tile(int dest_x, int dest_y, sf::Sprite& pieceSprite, struct Piece& pieceStruct);
std::vector<int> calculate_clicked_tile_on_borad(int x, int y);