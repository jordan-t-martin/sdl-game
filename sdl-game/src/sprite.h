#pragma once

#include <SDL_image.h>
#include <string>

class Sprite {
public:
	Sprite(int sprite_num, int sprite_size, std::string texture_path);
	~Sprite();
	int _sprite_num;
	int _sprite_size;
	std::string _texture_path;
	SDL_Rect* _sprite_clips;

	SDL_Rect* loadSprites();
};