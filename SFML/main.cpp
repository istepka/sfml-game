#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <board.h>
#include <utils.h>
#include <map>
#include <uicontroller.h>
#include <SFML/Audio.hpp>

//void ui_render_pieces(sf::Texture* PiecesTextures, sf::Sprite* PiecesSprites);

int WINDOW_SIZE_X = 800, WINDOW_SIZE_Y = 1000;
const int NUMBER_OF_PIECES_TEXTURES = 16;
int NUMBER_OF_PIECES = NUMBER_OF_PIECES_TEXTURES;
int BOARD_OFFSET_Y = 150, BOARD_OFFSET_X = 200;
int SINGLE_TILE_WIDTH = 91, SINGLE_TILE_HEIGHT = 90;
bool is_piece_grabbed = false;
int grabbed_index = -1;
int game_state = 0; //0 - menu, 1 - game 
int sound_volume = 10; // 0-10
bool gameover = false;

Board board;


int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32), "Scuffed chess");
	sf::Color button_color = sf::Color::Color(230, 230, 230);


	std::map<std::string, sf::Sprite> sprites_dictionary;
	std::map<std::string, sf::Texture> textures_dictionary;
	std::map<std::string, sf::Text> texts_dictionary;
	sf::Texture PiecesTextures[NUMBER_OF_PIECES_TEXTURES];
	sf::Sprite PiecesSprites[NUMBER_OF_PIECES_TEXTURES];



	std::string whose_turn = "white", turn_dummy_text = "Turn: ";
	sf::Font font;
	font.loadFromFile("./res/Raleway-Medium.ttf");
	sf::Font bold_font;
	bold_font.loadFromFile("./res/Raleway-SemiBold.ttf");






	ui_load_sprites_and_textures(textures_dictionary, sprites_dictionary);
	ui_load_texts(texts_dictionary, font, bold_font);
	bd_init();
	ui_render_pieces(PiecesTextures, PiecesSprites);
	ui_load_sounds();

	sf::SoundBuffer buffer_click;
	sf::Sound click;
	buffer_click.loadFromFile("./res/click.flac");
	click.setBuffer(buffer_click);
	click.setVolume(sound_volume / 2);
	sf::SoundBuffer buffer_move;
	sf::Sound move;
	buffer_move.loadFromFile("./res/move.flac");
	move.setBuffer(buffer_move);
	move.setVolume(sound_volume);

	std::cout << "setup done";

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code== sf::Keyboard::R) { // debug
				int bd[4][8] = { 0 };
				std::vector<Piece> board = bd_getPiecesOnBoard();
				for (Piece pie : board) {
					if (pie.alive)
					bd[pie.x][pie.y] = pie.type + 1;
					else
					bd[pie.x][pie.y] = -1;

				}

				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						std::cout << bd[i][j] << " ";
					}
					std::cout << std::endl;
				}
				std::cout << "----------" << std::endl;
			}

			if (game_state == 0) { //menu actions
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (sprites_dictionary["play_button"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						// mouse is on sprite
						game_state = 1;
						bd_new_game();
						ui_load_pieces(PiecesSprites);

						whose_turn = "white";
						board.toMove = PieceColor::white;
						texts_dictionary["text_turn"].setString(turn_dummy_text + whose_turn);

					}
					else if (sprites_dictionary["load_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						bd_load_save();
						ui_load_pieces(PiecesSprites);

						whose_turn = board.toMove == PieceColor::white ? "white" : "black";
						texts_dictionary["text_turn"].setString(turn_dummy_text + whose_turn);
						game_state = 1;

					}
					else if (sprites_dictionary["exit_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						window.close();
					}
					else if (sprites_dictionary["sound_button"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						sound_volume = sound_volume == 0 ? 10 : sound_volume == 5 ? 0 : 5;
						ui_change_sound_volume(sound_volume, sprites_dictionary, textures_dictionary);
						click.setVolume(sound_volume / 2);
						move.setVolume(sound_volume);
					}

					click.play();
					
				}
			}
			else {

				if (event.type == sf::Event::MouseButtonPressed)
				{
					texts_dictionary["info_text"].setString("");
					//Back to menu button
					if (sprites_dictionary["back_button_background_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						texts_dictionary["gameover_text"].setString("");
						//bd_save();
						gameover = false;
						game_state = 0;
						click.play();
					}
					if (sprites_dictionary["save_game_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						bd_save();
						//game_state = 0;
						texts_dictionary["info_text"].setString("Succesfully saved!");
						click.play();
					}
					if (sprites_dictionary["concede_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						texts_dictionary["gameover_text"].setString(whose_turn + " died!");
						texts_dictionary["text_turn"].setString("");
						gameover = true;
						
						click.play();
					}
					if (sprites_dictionary["new_game_button_sprite"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						bd_new_game();
						ui_load_pieces(PiecesSprites);
						whose_turn = "white";
						board.toMove = PieceColor::white;
						texts_dictionary["text_turn"].setString(turn_dummy_text + whose_turn);
						texts_dictionary["gameover_text"].setString("");
						gameover = false;
						click.play();
					}
					if (sprites_dictionary["sound_button"].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						sound_volume = sound_volume == 0 ? 10 : sound_volume == 5 ? 0 : 5;
						ui_change_sound_volume(sound_volume, sprites_dictionary, textures_dictionary);
						click.setVolume(sound_volume / 2);
						move.setVolume(sound_volume);
					}

					if (!gameover) {
						if (!is_piece_grabbed) //Grab piece
						{
							sf::Vector2i pos = sf::Mouse::getPosition(window);
							std::vector<int> calculatedPos = calculate_clicked_tile_on_borad(pos.x, pos.y);
							if (calculatedPos[0] == -1) break;

							grabbed_index = bd_getPieceIndex(calculatedPos[0], calculatedPos[1]);
							if (grabbed_index == -1) break;

							is_piece_grabbed = true;
							std::cout << "Grabbed" << std::endl;
						}
						else { // Move piece to desired position (currently some restrictions)
							sf::Vector2i pos = sf::Mouse::getPosition(window);
							std::vector<int> calculatedPos = calculate_clicked_tile_on_borad(pos.x, pos.y);
							std::vector<struct Piece>& Pieces = bd_getPiecesOnBoard();
							Piece& grabbedPiece = Pieces[grabbed_index];

							//If clicked in a bad place return figure to its origin
							if (calculatedPos[0] == -1 || !isLegal(grabbedPiece, calculatedPos[0], calculatedPos[1]))
							{
								move_piece_to_tile(grabbedPiece.x, grabbedPiece.y, PiecesSprites[grabbed_index], grabbedPiece);
								std::cout << "Returned to origin tile" << std::endl;
								texts_dictionary["info_text"].setString("Returned to origin tile");
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
									move_piece_to_tile(grabbedPiece.x, grabbedPiece.y, PiecesSprites[grabbed_index], grabbedPiece);
									bd_resurrect(other);
									std::cout << "In check, returned to origin tile" << std::endl;
									texts_dictionary["info_text"].setString("In check, returned to origin tile");
								}
								else
								{
									move_piece_to_tile(calculatedPos[0], calculatedPos[1], PiecesSprites[grabbed_index], grabbedPiece);

									//Change turn display text
									if (whose_turn == "white") whose_turn = "black";
									else whose_turn = "white";
									texts_dictionary["text_turn"].setString(turn_dummy_text + whose_turn);
								}


							}

							grabbed_index = -1;
							is_piece_grabbed = false;
							std::cout << "Released" << std::endl;
							move.play();

							if (!board.king[0]->alive || !board.king[1]->alive) {
								//game_state = 0;
								texts_dictionary["gameover_text"].setString(whose_turn + " died!");
								texts_dictionary["text_turn"].setString("");
								gameover = true;
							}
						}
					}
					


				}
			}



			ui_draw_frame(window, game_state, grabbed_index, is_piece_grabbed, PiecesSprites, sprites_dictionary, texts_dictionary);

		}
		
		
		
	}
	return 0;
}





