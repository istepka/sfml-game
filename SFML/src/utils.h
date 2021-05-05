#include <iostream>
#include <game-runner.h>
#include <SFML/Graphics.hpp>
void movePieceToTile(int dest_x, int dest_y, sf::Sprite* pieceSprite, struct Piece* pieceStruct);
std::vector<int> calculateBoardClickedTile(int x, int y);