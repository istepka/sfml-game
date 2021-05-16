#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <board.h>
#include <utils.h>
#include <map>
#include <uicontroller.h>
#include <SFML/Audio.hpp>

void render_pieces(sf::Texture* PiecesTextures, sf::Sprite* PiecesSprites);

int WINDOW_SIZE_X = 800, WINDOW_SIZE_Y = 1000;
const int NUMBER_OF_PIECES_TEXTURES = 16;
int BOARD_OFFSET_Y = 100, BOARD_OFFSET_X = 200;
int SINGLE_TILE_WIDTH = 91, SINGLE_TILE_HEIGHT = 90;
bool isPieceGrabbed = false;
int grabbedIndex = -1;
int game_state = 0; //0 - menu, 1 - game 
int sound_volume = 50; // 0-100

Board board;


int main()
{
	std::map<std::string, sf::Sprite> sprites_dictionary;
	std::map<std::string, sf::Texture> textures_dictionary;
	std::map<std::string, sf::Text> texts_dictionary;
	
	std::string whose_turn = "white", turn_dummy_text = "Turn: ";
	sf::Font font;
	font.loadFromFile("./res/ArialUnicodeMS.ttf");
	
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32), "Scuffed chess");
	
	sf::Color button_color = sf::Color::Color(230, 230, 230);
	sf::Color background_color = sf::Color::Color(217, 217, 217);

	ui_load_sprites_and_textures(textures_dictionary, sprites_dictionary);
	ui_load_texts(texts_dictionary, font);
	//Initialize pieces on board
	bd_init();
	sf::Texture PiecesTextures[NUMBER_OF_PIECES_TEXTURES];
	sf::Sprite PiecesSprites[NUMBER_OF_PIECES_TEXTURES];
	render_pieces(PiecesTextures, PiecesSprites);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("./res/move.flac");
	sf::Sound move;
	move.setBuffer(buffer);
	move.setVolume(sound_volume);
	sf::SoundBuffer buffer1;
	buffer1.loadFromFile("./res/click.flac");
	sf::Sound click;
	click.setBuffer(buffer1);
	click.setVolume(sound_volume/2);

	
	

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			if (game_state == 0) { //menu actions
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (sprites_dictionary["play_button"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						// mouse is on sprite
						game_state = 1;
						bd_new_game();
						std::vector< Piece>& Pieces = bd_getPiecesOnBoard();
						for (int i = 0; i < Pieces.size(); i++)
							move_piece_to_tile(board.alivePieces[i].x, board.alivePieces[i].y, PiecesSprites[i], Pieces[i]);
						whose_turn = "white";
						board.toMove = PieceColor::white;
						texts_dictionary["text_turn"].setString(turn_dummy_text + whose_turn);
						click.play();
					}
					else if (sprites_dictionary["load_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						bd_load_save();
						std::vector< Piece>& Pieces = bd_getPiecesOnBoard();
						for (int i = 0; i < Pieces.size(); i++)
							move_piece_to_tile(board.alivePieces[i].x, board.alivePieces[i].y, PiecesSprites[i], Pieces[i]);

						whose_turn = board.toMove == PieceColor::white ? "white" : "black";
						texts_dictionary["text_turn"].setString(turn_dummy_text + whose_turn);
						game_state = 1;
						click.play();
					}
					else if (sprites_dictionary["exit_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						click.play();
						window.close();
					}

					
				}
			}
			else {
				//game handling
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::R)
					{
						std::vector<struct Piece> Pieces = bd_getPiecesOnBoard();
						for (int i = 0; i < NUMBER_OF_PIECES_TEXTURES; i++)
						{
							std::cout << i << " piece " << Pieces[i].x << "," << Pieces[i].y << std::endl;

						}
					}
				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					//Back to menu button
					if (sprites_dictionary["back_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						bd_save();
						game_state = 0;
						click.play();
					}
					if (sprites_dictionary["new_game_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						bd_new_game();
						std::vector< Piece>& Pieces = bd_getPiecesOnBoard();
						for (int i = 0; i < Pieces.size(); i++)
							move_piece_to_tile(board.alivePieces[i].x, board.alivePieces[i].y, PiecesSprites[i], Pieces[i]);
						whose_turn = "white";
						board.toMove = PieceColor::white;
						texts_dictionary["text_turn"].setString(turn_dummy_text + whose_turn);
						click.play();
					}


					if (!isPieceGrabbed) //Grab piece
					{
						sf::Vector2i pos = sf::Mouse::getPosition(window);
						std::vector<int> calculatedPos = calculate_clicked_tile_on_borad(pos.x, pos.y);
						if (calculatedPos[0] == -1) break;

						grabbedIndex = bd_getPieceIndex(calculatedPos[0], calculatedPos[1]);
						if (grabbedIndex == -1) break;

						isPieceGrabbed = true;
						std::cout << "Grabbed" << std::endl;
					}
					else { // Move piece to desired position (currently some restrictions)
						sf::Vector2i pos = sf::Mouse::getPosition(window);
						std::vector<int> calculatedPos = calculate_clicked_tile_on_borad(pos.x, pos.y);

						std::vector<struct Piece>& Pieces = bd_getPiecesOnBoard();
						Piece& grabbedPiece = Pieces[grabbedIndex];

						//If clicked in a bad place return figure to its origin
						if (calculatedPos[0] == -1 || !isLegal(grabbedPiece, calculatedPos[0], calculatedPos[1]))
						{

							move_piece_to_tile(grabbedPiece.x, grabbedPiece.y, PiecesSprites[grabbedIndex], grabbedPiece);
							std::cout << "Returned to origin tile" << std::endl;

						}
						else
						{
							Piece* other = bd_getPieceAtCords(calculatedPos[0], calculatedPos[1]);
							if (other)
							{
								bd_destroy(*other);
							}

							bd_move(grabbedPiece, calculatedPos[0], calculatedPos[1]);

							if (isInCheck(static_cast<PieceColor>(!board.toMove)))
							{
								bd_undo();
								move_piece_to_tile(grabbedPiece.x, grabbedPiece.y, PiecesSprites[grabbedIndex], grabbedPiece);
								std::cout << "In check, returned to origin tile" << std::endl;
							}
							else
								move_piece_to_tile(calculatedPos[0], calculatedPos[1], PiecesSprites[grabbedIndex], grabbedPiece);

							//Change turn display text
							if (whose_turn == "white") whose_turn = "black";
							else whose_turn = "white";
							texts_dictionary["text_turn"].setString(turn_dummy_text + whose_turn);
						}

						grabbedIndex = -1;
						isPieceGrabbed = false;
						std::cout << "Released" << std::endl;	
						move.play();

					}



				}
			}
		}

		window.clear(background_color);
		

		if (game_state == 1) { //display in-game stuff
			
			window.draw(sprites_dictionary["board_sprite"]);

			for (int i = 0; i < NUMBER_OF_PIECES_TEXTURES; i++)
			{
				if (isPieceGrabbed && i == grabbedIndex)
				{
					sf::Vector2i pos = sf::Mouse::getPosition(window);
					PiecesSprites[i].setPosition(pos.x - 38, pos.y - 38);
					//std::cout << "Following" << std::endl;
				}

				// Modifying the vector breaks the sprite array!
				if (board.alivePieces[i].alive)
					window.draw(PiecesSprites[i]);
			}

			//Whose  turn
			window.draw(texts_dictionary["text_turn"]);
			window.draw(texts_dictionary["save_exit_text"]);
		

			window.draw(sprites_dictionary["new_game_button_sprite"]);
			window.draw(texts_dictionary["new_game"]);

			window.draw(sprites_dictionary["back_button_sprite"]);
		}
		else if (game_state == 0) //display main_menu stuff
		{
			window.clear(background_color);
			window.draw(sprites_dictionary["play_button"]);
			window.draw(texts_dictionary["menu_play"]);

			window.draw(sprites_dictionary["load_button_sprite"]);
			window.draw(texts_dictionary["menu_load"]);
			window.draw(sprites_dictionary["exit_button_sprite"]);
			window.draw(texts_dictionary["menu_exit"]);
		}


		window.display();
	}

	return 0;
}


//Only render on the begining
void render_pieces(sf::Texture *PiecesTextures, sf::Sprite *PiecesSprites)
{
	std::vector<Piece> Pieces = bd_getPiecesOnBoard();
	
	for (int i = 0; i <Pieces.size(); i++)
	{
		std::cout << Pieces[i].x << std::endl;
		

		std::string piece_name = "", color = "", filename;

		color = Pieces[i].player_color == PieceColor::black ? "black" : "white";
		switch (Pieces[i].type)
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
		
		std::cout << Pieces[i].type << filename << std::endl;
		



		PiecesTextures[i] = sf::Texture();
		PiecesTextures[i].loadFromFile(filename);
		//PiecesTextures[i].setSmooth(true);

		PiecesSprites[i] = sf::Sprite(PiecesTextures[i], sf::IntRect(0, 0, 75, 75));

		

		PiecesSprites[i].setPosition(BOARD_OFFSET_X + 40 + SINGLE_TILE_WIDTH * Pieces[i].x, 
			BOARD_OFFSET_Y + 35 + SINGLE_TILE_HEIGHT * Pieces[i].y);

		//PiecesSprites[]
	}
}

