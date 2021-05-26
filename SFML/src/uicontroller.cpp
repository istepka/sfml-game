#include <vector>
#include <game-runner.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <utils.h>

void _render_pieces()
{
	std::vector<Piece> Pieces = bd_getPiecesOnBoard();

	for (int i = 0; i < Pieces.size(); i++)
	{
		std::cout << Pieces[i].x << std::endl;
	}
}


extern int BOARD_OFFSET_X, BOARD_OFFSET_Y, WINDOW_SIZE_X, WINDOW_SIZE_Y, SINGLE_TILE_WIDTH, SINGLE_TILE_HEIGHT, sound_volume, NUMBER_OF_PIECES;
extern Board board;


void ui_load_sprites_and_textures(std::map<std::string, sf::Texture> &textures_dictionary, std::map<std::string, sf::Sprite> &sprites_dictionary )
{
	sf::Color button_color = sf::Color(230, 230, 230);


	textures_dictionary["board_texture"] = sf::Texture();
	textures_dictionary["board_texture"].loadFromFile("./res/board.png");
	textures_dictionary["board_texture"].setSmooth(true);

	sprites_dictionary["board_sprite"] = sf::Sprite(textures_dictionary["board_texture"]);
	sprites_dictionary["board_sprite"].setTextureRect(sf::IntRect(0, 0, 400, 660));
	sprites_dictionary["board_sprite"].setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);

	textures_dictionary["button_wide_texture"] = sf::Texture();
	textures_dictionary["button_wide_texture"].loadFromFile("./res/button_wide.png");
	textures_dictionary["button_wide_texture"].setSmooth(true);
	textures_dictionary["button_wide_texture"].setRepeated(true);

	textures_dictionary["empty_texture"] = sf::Texture();

	textures_dictionary["button_wide_highlighted"] = sf::Texture();
	textures_dictionary["button_wide_highlighted"].loadFromFile("./res/button_wide_highlighted.png");
	textures_dictionary["button_wide_highlighted"].setSmooth(true);

	textures_dictionary["mute_sound"] = sf::Texture();
	textures_dictionary["mute_sound"].loadFromFile("./res/mute_sound.png");
	textures_dictionary["mute_sound"].setSmooth(true);

	textures_dictionary["high_sound"] = sf::Texture();
	textures_dictionary["high_sound"].loadFromFile("./res/high_sound.png");
	textures_dictionary["high_sound"].setSmooth(true);

	textures_dictionary["low_sound"] = sf::Texture();
	textures_dictionary["low_sound"].loadFromFile("./res/low_sound.png");
	textures_dictionary["low_sound"].setSmooth(true);
	textures_dictionary["low_sound"].setSmooth(true);

	sprites_dictionary["sound_button"] = sf::Sprite(textures_dictionary["high_sound"]);
	sprites_dictionary["sound_button"].setTextureRect(sf::IntRect(0, 0, 300, 300));
	sprites_dictionary["sound_button"].setPosition(WINDOW_SIZE_X  - 100, WINDOW_SIZE_Y - 100);
	sprites_dictionary["sound_button"].setScale(0.3, 0.3);



	sprites_dictionary["play_button"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["play_button"].setTextureRect(sf::IntRect(0, 0, 300, 60));
	sprites_dictionary["play_button"].setPosition(WINDOW_SIZE_X / 2 - 150, 300);
	sprites_dictionary["play_button"].setColor(button_color);

	textures_dictionary["back_button_texture"] = sf::Texture();
	textures_dictionary["back_button_texture"].loadFromFile("./res/back.png");
	textures_dictionary["back_button_texture"].setSmooth(true);

	sprites_dictionary["back_button_sprite"] = sf::Sprite(textures_dictionary["back_button_texture"]);
	sprites_dictionary["back_button_sprite"].setTextureRect(sf::IntRect(0, 0, 100, 100));
	sprites_dictionary["back_button_sprite"].setPosition(15, 15);
	sprites_dictionary["back_button_sprite"].setScale(0.5, 0.5);


	sprites_dictionary["back_button_background_sprite"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["back_button_background_sprite"].setTextureRect(sf::IntRect(0, 0, 150, 60));
	sprites_dictionary["back_button_background_sprite"].setPosition(10, 10);
	sprites_dictionary["back_button_background_sprite"].setColor(button_color);


	sprites_dictionary["load_button_sprite"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["load_button_sprite"].setTextureRect(sf::IntRect(0, 0, 300, 60));
	sprites_dictionary["load_button_sprite"].setPosition(WINDOW_SIZE_X / 2 - 150, 400);
	sprites_dictionary["load_button_sprite"].setColor(button_color);

	sprites_dictionary["exit_button_sprite"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["exit_button_sprite"].setTextureRect(sf::IntRect(0, 0, 300, 60));
	sprites_dictionary["exit_button_sprite"].setPosition(WINDOW_SIZE_X / 2 - 150, 500);
	sprites_dictionary["exit_button_sprite"].setColor(button_color);


	sprites_dictionary["new_game_button_sprite"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["new_game_button_sprite"].setTextureRect(sf::IntRect(0, 0, 150, 60));
	sprites_dictionary["new_game_button_sprite"].setPosition(WINDOW_SIZE_X - 160, 10);
	sprites_dictionary["new_game_button_sprite"].setColor(button_color);

	sprites_dictionary["save_game_button_sprite"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["save_game_button_sprite"].setTextureRect(sf::IntRect(0, 0, 150, 60));
	sprites_dictionary["save_game_button_sprite"].setPosition(WINDOW_SIZE_X - 160, 80);
	sprites_dictionary["save_game_button_sprite"].setColor(button_color);

	sprites_dictionary["concede_button_sprite"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["concede_button_sprite"].setTextureRect(sf::IntRect(0, 0, 150, 60));
	sprites_dictionary["concede_button_sprite"].setPosition(WINDOW_SIZE_X - 160, 150);
	sprites_dictionary["concede_button_sprite"].setColor(button_color);
}

void ui_load_texts(std::map<std::string, sf::Text>& texts_dic, sf::Font &font, sf::Font &bold_font)
{
	sf::Text text_turn;
	text_turn.setPosition(WINDOW_SIZE_X / 2 - 100, 80);
	text_turn.setCharacterSize(40);
	text_turn.setFont(font);
	text_turn.setFillColor(sf::Color::Black);
	text_turn.setString("Turn: white");

	sf::Text menu_play = text_turn;
	menu_play.setString("Play");
	menu_play.setPosition(WINDOW_SIZE_X / 2 - 40, 305 - 2);

	sf::Text menu_load = text_turn;
	menu_load.setString("Load game");
	menu_load.setPosition(WINDOW_SIZE_X / 2 - 100, 300 - 2 + 105);


	sf::Text menu_exit = text_turn;
	menu_exit.setString("Exit");
	menu_exit.setPosition(WINDOW_SIZE_X / 2 - 35, 300 - 2 + 205);

	sf::Text exit_text = text_turn;
	exit_text.setString("Exit");
	exit_text.setPosition(80, 25);
	exit_text.setCharacterSize(24);


	sf::Text new_game = text_turn;
	new_game.setString("New game");
	new_game.setPosition(WINDOW_SIZE_X - 145, 25);
	new_game.setCharacterSize(24);
	
	sf::Text concede_text = text_turn;
	concede_text.setString("Concede");
	concede_text.setPosition(WINDOW_SIZE_X - 135, 165);
	concede_text.setCharacterSize(24);


	sf::Text save_game = text_turn;
	save_game.setString("Save game");
	save_game.setPosition(WINDOW_SIZE_X - 145, 95);
	save_game.setCharacterSize(24);


	sf::Text info_text = text_turn;
	info_text.setString("");
	info_text.setPosition(0, WINDOW_SIZE_Y - 30);
	info_text.setCharacterSize(20);

	sf::Text title_text = text_turn;
	title_text.setString("Scuffed chess!");
	title_text.setPosition(WINDOW_SIZE_X/2 - 150, 120);
	title_text.setCharacterSize(45);
	title_text.setFont(bold_font);


	sf::Text gameover_text = text_turn;
	gameover_text.setString("");
	gameover_text.setPosition(WINDOW_SIZE_X / 2 - 110,60);
	gameover_text.setCharacterSize(45);


	texts_dic["text_turn"] = text_turn;
	texts_dic["menu_play"] = menu_play;
	texts_dic["menu_load"] = menu_load;
	texts_dic["menu_exit"] = menu_exit;
	texts_dic["save_exit_text"] = exit_text;
	texts_dic["new_game"] = new_game;
	texts_dic["save_game"] = save_game;
	texts_dic["info_text"] = info_text;
	texts_dic["concede_text"] = concede_text;
	texts_dic["title_text"] = title_text;
	texts_dic["gameover_text"] = gameover_text;
}


void ui_render_pieces(sf::Texture* PiecesTextures, sf::Sprite* PiecesSprites)
{
	std::vector<Piece> Pieces = bd_getPiecesOnBoard();

	for (int i = 0; i < Pieces.size(); i++)
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


void ui_load_pieces(sf::Sprite* PiecesSprites)
{
	extern Board board;

	std::vector< Piece>& Pieces = bd_getPiecesOnBoard();
	for (int i = 0; i < Pieces.size(); i++)
		move_piece_to_tile(board.alivePieces[i].x, board.alivePieces[i].y, PiecesSprites[i], Pieces[i]);
}


void ui_draw_frame(sf::RenderWindow &window, int game_state, int grabbed_index, bool is_piece_grabbed, sf::Sprite *PiecesSprites,  std::map<std::string, sf::Sprite> &sprites_dictionary, std::map<std::string, sf::Text> &texts_dictionary)
{
	
	sf::Color background_color = sf::Color::Color(217, 217, 217);
	window.clear(background_color);


	if (game_state == 1) { //display in-game stuff

		window.draw(sprites_dictionary["board_sprite"]);

		for (int i = 0; i < NUMBER_OF_PIECES; i++)
		{
			if (is_piece_grabbed && i == grabbed_index)
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				PiecesSprites[i].setPosition(pos.x - 38, pos.y - 38);
				//std::cout << "Following" << std::endl;
			}

			// Modifying the vector breaks the sprite array!
			if (board.alivePieces[i].alive)
				window.draw(PiecesSprites[i]);
		}

	
		


		window.draw(sprites_dictionary["new_game_button_sprite"]);
		
		window.draw(sprites_dictionary["back_button_background_sprite"]);
		window.draw(sprites_dictionary["back_button_sprite"]);
		window.draw(sprites_dictionary["save_game_button_sprite"]);
		window.draw(sprites_dictionary["concede_button_sprite"]);
		window.draw(texts_dictionary["save_game"]);
		window.draw(texts_dictionary["new_game"]);
		window.draw(texts_dictionary["text_turn"]);
		window.draw(texts_dictionary["save_exit_text"]);
		window.draw(texts_dictionary["gameover_text"]);
		window.draw(texts_dictionary["concede_text"]);
		
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
		window.draw(texts_dictionary["title_text"]);
		
		
	}

	window.draw(texts_dictionary["info_text"]);
	window.draw(sprites_dictionary["sound_button"]);

	window.display();
}


void ui_change_sound_volume(int to_volume, std::map<std::string, sf::Sprite>& sprites_dictionary, std::map<std::string, sf::Texture>& textures_dictionary) {
	if (to_volume == 0) {
		sprites_dictionary["sound_button"].setTexture(textures_dictionary["mute_sound"]);
	}
	else if (to_volume == 10) {
		sprites_dictionary["sound_button"].setTexture(textures_dictionary["high_sound"]);
	}
	else if (to_volume == 5) {
		sprites_dictionary["sound_button"].setTexture(textures_dictionary["low_sound"]);
	}
}


void ui_load_sounds()
{	
	


	
}

void ui_play_click_sound()
{
	sf::SoundBuffer buffer1;
	sf::Sound click;
	buffer1.loadFromFile("./res/click.flac");
	click.setBuffer(buffer1);
	click.setVolume(sound_volume / 2);
	click.play();
}

void ui_play_piece_sound()
{
	sf::SoundBuffer buffer;
	sf::Sound move;

	buffer.loadFromFile("./res/move.flac");
	move.setBuffer(buffer);
	move.setVolume(sound_volume);
	move.play();
}


