#pragma once
#include <vector>
#include <game-runner.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
void _render_pieces();
void ui_load_sprites_and_textures(std::map<std::string, sf::Texture>& textures_dictionary, std::map<std::string, sf::Sprite>& sprites_dictionary);
void ui_load_texts(std::map<std::string, sf::Text>& texts_dic, sf::Font& font, sf::Font& bold_font);
void ui_render_pieces(sf::Texture* PiecesTextures, sf::Sprite* PiecesSprites);
void ui_load_sounds();
void ui_play_click_sound();
void ui_play_piece_sound();
void ui_load_sound_and_font(sf::Font* font, sf::Font* bold_font, sf::SoundBuffer* buffer_click, sf::SoundBuffer* buffer_move, sf::Sound* click, sf::Sound* move);
void ui_load_pieces(sf::Sprite* PiecesSprites);
void ui_draw_frame(sf::RenderWindow& window, int game_state, int grabbed_index, bool is_piece_grabbed, sf::Sprite* PiecesSprites, std::map<std::string, sf::Sprite>& sprites_dictionary, std::map<std::string, sf::Text>& texts_dictionary);
void ui_change_sound_volume(int to_volume, std::map<std::string, sf::Sprite>& sprites_dictionary, std::map<std::string, sf::Texture>& textures_dictionary);
bool ui_handle_in_game_buttons(std::map<std::string, sf::Texture>& textures_dictionary, std::map<std::string, sf::Sprite>& sprites_dictionary, std::map<std::string, sf::Text>& texts_dictionary, sf::Sprite* PiecesSprites,
	bool* gameover, int* game_state, sf::Sound* click_sound, std::string* whose_turn, int* sound_volume, sf::Sound* move_sound, sf::RenderWindow& window);