#include "sprite.h"

Sprite::Sprite(int sprite_num, int sprite_size, std::string texture_path) 
	: _sprite_num(sprite_num), _sprite_size(sprite_size), _texture_path(texture_path)
{
	_sprite_clips = loadSpriteClips();
}

Sprite::~Sprite() {

}

SDL_Rect* Sprite::loadSpriteClips() {
	// Rectangles for taking a "clip" of a larger texture
	SDL_Rect* sprite_clips = new SDL_Rect[_sprite_num];

	// Find the dimensions of the provided sprite sheet
	int dim = ceil(sqrt(_sprite_num)); 

	// Find "clips" for each individual sprite
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (((i * dim) + j) >= _sprite_num) // Out of bounds
				break;
			sprite_clips[((i * dim) + j)].x = i * _sprite_size;
			sprite_clips[((i * dim) + j)].y = j * _sprite_size;
			sprite_clips[((i * dim) + j)].w = _sprite_size;
			sprite_clips[((i * dim) + j)].h = _sprite_size;
		}
	}

	return sprite_clips;
}