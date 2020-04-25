#pragma once
#include <SDL_image.h>
#include <string>

class Sprite {
public:
	Sprite(int sprite_num, int sprite_size, std::string texture_path);
	~Sprite();

	int inline getSpriteNum() { return _sprite_num; }
	int inline getSpriteSize() { return _sprite_size; }
	inline SDL_Rect* getSpriteClips() { return _sprite_clips; }
	std::string inline getTexturePath() { return _texture_path; }
	
	void inline setSpriteNum(int sprite_num) { _sprite_num = sprite_num; }
	void inline setSpriteSize(int sprite_size) { _sprite_size = sprite_size; }
	void inline setTexturePath(int texture_path) { _texture_path = texture_path; }
	void inline setSpriteClips(SDL_Rect* sprite_clips) { _sprite_clips = sprite_clips; }
	
private:
	SDL_Rect* loadSpriteClips();

	int _sprite_num;
	int _sprite_size;
	std::string _texture_path;
	SDL_Rect* _sprite_clips;
};