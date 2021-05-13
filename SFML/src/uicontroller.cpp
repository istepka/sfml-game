#include <vector>
#include <game-runner.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void _render_pieces()
{
	std::vector<Piece> Pieces = bd_getPiecesOnBoard();

	for (int i = 0; i < Pieces.size(); i++)
	{
		std::cout << Pieces[i].x << std::endl;
	}
}


extern int BOARD_OFFSET_X, BOARD_OFFSET_Y, WINDOW_SIZE_X;
void ui_load_sprites_and_textures(std::map<std::string, sf::Texture> &textures_dictionary, std::map<std::string, sf::Sprite> &sprites_dictionary )
{
	sf::Color button_color = sf::Color::Color(230, 230, 230);


	textures_dictionary["board_texture"] = sf::Texture();
	textures_dictionary["board_texture"].loadFromFile("./res/board.png");
	textures_dictionary["board_texture"].setSmooth(true);

	sprites_dictionary["board_sprite"] = sf::Sprite(textures_dictionary["board_texture"]);
	sprites_dictionary["board_sprite"].setTextureRect(sf::IntRect(0, 0, 400, 660));
	sprites_dictionary["board_sprite"].setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);

	textures_dictionary["button_wide_texture"] = sf::Texture();
	textures_dictionary["button_wide_texture"].loadFromFile("./res/button_wide.png");
	textures_dictionary["button_wide_texture"].setSmooth(true);

	textures_dictionary["empty_texture"] = sf::Texture();

	textures_dictionary["button_wide_highlighted"] = sf::Texture();
	textures_dictionary["button_wide_highlighted"].loadFromFile("./res/button_wide_highlighted.png");
	textures_dictionary["button_wide_highlighted"].setSmooth(true);

	sprites_dictionary["play_button"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["play_button"].setTextureRect(sf::IntRect(0, 0, 300, 60));
	sprites_dictionary["play_button"].setPosition(WINDOW_SIZE_X / 2 - 150, 200);
	sprites_dictionary["play_button"].setColor(button_color);



	textures_dictionary["back_button_texture"] = sf::Texture();
	textures_dictionary["back_button_texture"].loadFromFile("./res/back.png");
	textures_dictionary["back_button_texture"].setSmooth(true);

	sprites_dictionary["back_button_sprite"] = sf::Sprite(textures_dictionary["back_button_texture"]);
	sprites_dictionary["back_button_sprite"].setTextureRect(sf::IntRect(0, 0, 100, 100));
	sprites_dictionary["back_button_sprite"].setPosition(10, 10);


	sprites_dictionary["load_button_sprite"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["load_button_sprite"].setTextureRect(sf::IntRect(0, 0, 300, 60));
	sprites_dictionary["load_button_sprite"].setPosition(WINDOW_SIZE_X / 2 - 150, 300);
	sprites_dictionary["load_button_sprite"].setColor(button_color);

	sprites_dictionary["exit_button_sprite"] = sf::Sprite(textures_dictionary["button_wide_texture"]);
	sprites_dictionary["exit_button_sprite"].setTextureRect(sf::IntRect(0, 0, 300, 60));
	sprites_dictionary["exit_button_sprite"].setPosition(WINDOW_SIZE_X / 2 - 150, 400);
	sprites_dictionary["exit_button_sprite"].setColor(button_color);


	sprites_dictionary["new_game_button_sprite"] = sf::Sprite(textures_dictionary["empty_texture"]);
	sprites_dictionary["new_game_button_sprite"].setTextureRect(sf::IntRect(0, 0, 150, 60));
	sprites_dictionary["new_game_button_sprite"].setPosition(0, 100);
	sprites_dictionary["new_game_button_sprite"].setColor(button_color);
}

void ui_load_texts(std::map<std::string, sf::Text>& texts_dic, sf::Font &font)
{
	sf::Text text_turn;
	text_turn.setPosition(WINDOW_SIZE_X / 2 - 130, 30);
	text_turn.setCharacterSize(50);
	text_turn.setFont(font);
	text_turn.setFillColor(sf::Color::Black);
	text_turn.setString("Turn: white");

	sf::Text menu_play = text_turn;
	menu_play.setString("Play");
	menu_play.setPosition(WINDOW_SIZE_X / 2 - 80, 200 - 2);

	sf::Text menu_load = text_turn;
	menu_load.setString("Load game");
	menu_load.setPosition(WINDOW_SIZE_X / 2 - 150, 200 - 2 + 100);


	sf::Text menu_exit = text_turn;
	menu_exit.setString("Exit");
	menu_exit.setPosition(WINDOW_SIZE_X / 2 - 150, 200 - 2 + 200);

	sf::Text save_exit_text = text_turn;
	save_exit_text.setString("Save & exit");
	save_exit_text.setPosition(0, 0);
	save_exit_text.setCharacterSize(24);


	sf::Text new_game = text_turn;
	new_game.setString("New game");
	new_game.setPosition(0, 100 - 2);
	new_game.setCharacterSize(24);


	texts_dic["text_turn"] = text_turn;
	texts_dic["menu_play"] = menu_play;
	texts_dic["menu_load"] = menu_load;
	texts_dic["menu_exit"] = menu_exit;
	texts_dic["save_exit_text"] = save_exit_text;
	texts_dic["new_game"] = new_game;
}


void ui_init_sounds()
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile("./res/move.flac");
	sf::Sound move;
	move.setBuffer(buffer);

	buffer.loadFromFile("./res/click.flac");
	sf::Sound click;
	click.setBuffer(buffer);




}