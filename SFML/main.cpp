#include<SFML/Graphics.hpp>
//#include<game-runner.h>
#include "src/uicontroller.h"
#include <iostream>
#include <string>
#include "src/utils.h"
#include "src/game-runner.h"

void render_pieces(sf::Texture* PiecesTextures, sf::Sprite* PiecesSprites);

int WINDOW_SIZE_X = 800, WINDOW_SIZE_Y = 1000;
const int NUMBER_OF_PIECES_TEXTURES = 16;
int BOARD_OFFSET_Y = 100, BOARD_OFFSET_X = 200;
int SINGLE_TILE_WIDTH = 91, SINGLE_TILE_HEIGHT = 90;
bool isPieceGrabbed = false;
int grabbedIndex = -1;

int main()
{

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32), "Scuffed chess");

	sf::Texture boardTexture;
	boardTexture.loadFromFile("./res/board.png");
	boardTexture.setSmooth(true);
	sf::Sprite boardSprite(boardTexture);
	boardSprite.setTextureRect(sf::IntRect(0, 0, 400, 660));
	boardSprite.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);


	//Initialize pieces on board
	initBoard();
	sf::Texture PiecesTextures[NUMBER_OF_PIECES_TEXTURES];
	sf::Sprite PiecesSprites[NUMBER_OF_PIECES_TEXTURES];
	render_pieces(PiecesTextures, PiecesSprites);




	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::R)
				{		
					//movePieceToTile(3, 4, &PiecesSprites[0], &Pieces[0]);
					std::vector<struct Piece> Pieces = getPiecesOnBoard();
					for (int i = 0; i < NUMBER_OF_PIECES_TEXTURES; i++)
					{
						std::cout<<  i <<" piece " << Pieces[i].x << "," << Pieces[i].y <<std::endl;

					}
				}

			}

			if (event.type == sf::Event::MouseButtonPressed)
			{

				if (!isPieceGrabbed) //Grab piece
				{
					sf::Vector2i pos = sf::Mouse::getPosition(window);
					std::vector<int> calculatedPos = calculateBoardClickedTile(pos.x, pos.y);
					if (calculatedPos[0] == -1) break;

					grabbedIndex = getPieceIndex(calculatedPos[0], calculatedPos[1]);
					if (grabbedIndex == -1) break;

					isPieceGrabbed = true;
					std::cout << "Grabbed" << std::endl;
				}
				else { // Move piece to desired position (currently no restrictions)
					sf::Vector2i pos = sf::Mouse::getPosition(window);
					std::vector<int> calculatedPos = calculateBoardClickedTile(pos.x, pos.y);
					
					std::vector<struct Piece> &Pieces = getPiecesOnBoard();

					if (calculatedPos[0] == -1) //If clicked in a bad place return figure to its origin
					{
						
						movePieceToTile(Pieces[grabbedIndex].x, Pieces[grabbedIndex].y, PiecesSprites[grabbedIndex], Pieces[grabbedIndex]);
						std::cout << "Returned to origin tile" << std::endl;
					
					}
					else
						movePieceToTile(calculatedPos[0], calculatedPos[1], PiecesSprites[grabbedIndex], Pieces[grabbedIndex]);

					grabbedIndex = -1;
					isPieceGrabbed = false;
					std::cout << "Released" << std::endl;
				}

				
				
			}
		}

		window.clear(sf::Color::White);

		//DRAW EVERYTHING HERE
		window.draw(boardSprite);

		for (int i = 0; i < NUMBER_OF_PIECES_TEXTURES; i++)
		{
			if (isPieceGrabbed && i == grabbedIndex)
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				PiecesSprites[i].setPosition(pos.x-38, pos.y-38);	
				//std::cout << "Following" << std::endl;
			}
			
			window.draw(PiecesSprites[i]);
		}

		window.display();
	}

	return 0;
}


//Only render on the begining
void render_pieces(sf::Texture *PiecesTextures, sf::Sprite *PiecesSprites)
{
	std::vector<Piece> Pieces = getPiecesOnBoard();
	
	for (int i = 0; i <Pieces.size(); i++)
	{
		std::cout << Pieces[i].x << std::endl;
		

		std::string piece_name = "", color = "", filename;

		color = Pieces[i].player_color == PieceColor::black ? "black" : "white";
		switch (Pieces[i].piece_type)
		{
		case PieceType::bishop:
		{
			piece_name = "bishop";
			break;
		}
		case PieceType::king:
		{
			piece_name = "king";
			break;
		}
		case PieceType::pawn:
		{
			piece_name = "pawn";
			break;
		}
		case PieceType::rook:
		{
			piece_name = "rook";
			break;
		}
		case PieceType::knight:
		{
			piece_name = "knight";
			break;
		}
		}
		filename = "./res/" + piece_name + "_" + color + ".png";
		
		std::cout << Pieces[i].piece_type << filename << std::endl;
		



		PiecesTextures[i] = sf::Texture();
		PiecesTextures[i].loadFromFile(filename);
		//PiecesTextures[i].setSmooth(true);

		PiecesSprites[i] = sf::Sprite(PiecesTextures[i], sf::IntRect(0, 0, 75, 75));

		

		PiecesSprites[i].setPosition(BOARD_OFFSET_X + 40 + SINGLE_TILE_WIDTH * Pieces[i].x, 
			BOARD_OFFSET_Y + 35 + SINGLE_TILE_HEIGHT * Pieces[i].y);

		//PiecesSprites[]
	}
}