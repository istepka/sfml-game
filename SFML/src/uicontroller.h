#pragma once
#include <vector>
#include <game-runner.h>
#include <iostream>
#include <SFML/Graphics.hpp>
void _render_pieces();
void ui_load_sprites_and_textures(std::map<std::string, sf::Texture>& textures_dictionary, std::map<std::string, sf::Sprite>& sprites_dictionary);
void ui_load_texts(std::map<std::string, sf::Text>& texts_dic, sf::Font& font);
void ui_render_pieces(sf::Texture* PiecesTextures, sf::Sprite* PiecesSprites);
void ui_load_sounds();
void ui_play_click_sound();
void ui_play_piece_sound();
void ui_load_pieces(sf::Sprite* PiecesSprites);
void ui_draw_frame(sf::RenderWindow& window, int game_state, int grabbed_index, bool is_piece_grabbed, sf::Sprite* PiecesSprites, std::map<std::string, sf::Sprite>& sprites_dictionary, std::map<std::string, sf::Text>& texts_dictionary);