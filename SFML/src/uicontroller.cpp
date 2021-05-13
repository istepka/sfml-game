#include <vector>
#include <game-runner.h>
#include <iostream>
#include <SFML/Graphics.hpp>

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
