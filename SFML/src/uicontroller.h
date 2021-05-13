#pragma once
#include <vector>
#include <game-runner.h>
#include <iostream>
#include <SFML/Graphics.hpp>
void _render_pieces();
void ui_load_sprites_and_textures(std::map<std::string, sf::Texture>& textures_dictionary, std::map<std::string, sf::Sprite>& sprites_dictionary);
void ui_load_texts(std::map<std::string, sf::Text>& texts_dic, sf::Font& font);