#include<SFML/Graphics.hpp>
#include<game-runner.h>
#include<uicontroller.h>
#include <iostream>
#include <string>

void render_pieces();

int WINDOW_SIZE_X = 800, WINDOW_SIZE_Y = 1000;
int BOARD_OFFSET_Y = 100, BOARD_OFFSET_X = 0;
int SINGLE_TILE_WIDTH = 91, SINGLE_TILE_HEIGHT = 90;
std::vector<sf::Texture> PiecesTextures;
std::vector<sf::Sprite> PiecesSprites;

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

	render_pieces();

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
					//render_pieces();
					
					
				}
			}
		}

		window.clear(sf::Color::White);

		//DRAW EVERYTHING HERE
		window.draw(boardSprite);

		for (int i = 0; i < PiecesSprites.size(); i++)
		{
			window.draw(PiecesSprites[i]);
		}

		window.display();
	}

	return 0;
}

void render_pieces()
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
		
		PiecesTextures.push_back(sf::Texture());
		PiecesTextures[i].loadFromFile(filename);
		//PiecesTextures[i].setSmooth(true);

		PiecesSprites.push_back(sf::Sprite(PiecesTextures[i], sf::IntRect(0, 0, 75, 75)));
		PiecesSprites[i].setPosition(BOARD_OFFSET_X + 40 + SINGLE_TILE_WIDTH * Pieces[i].x, 
			BOARD_OFFSET_Y + 35 + SINGLE_TILE_HEIGHT * Pieces[i].y);

		//PiecesSprites[]
	}
}