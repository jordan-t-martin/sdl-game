#include "player.h"
#include <iostream>
#include <math.h>

Player::Player(SDL_Renderer* renderer, int w, int h, int x, int y, int r, int g, int b, int a)
	: Rect(renderer, w, h, x, y, r, g, b, a)
{

}

Player::Player(SDL_Renderer* renderer, int w, int h, int x, int y, std::vector<std::shared_ptr<Sprite>> sprites)
	: Rect(renderer, w, h, x, y, sprites.at(0)->_texture_path), _sprites(sprites)
{
	//std::vector<SDL_Surface> surfaces;
	
	for (int i = 0; i < sprites.size(); i++) {
		// Create surface from image using file path
		auto surface = IMG_Load(sprites.at(i)->_texture_path.c_str());

		// Check if surface was created successfully
		if (!surface) {
			std::cerr << "Failed to create player surface.\n";
		}

		// Create texture from surface
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		// Check if texture was created successfully
		if (!texture) {
			std::cerr << "Failed to create player texture: " << i << "\n";
		}

		textures.push_back(texture);
		// Free surface memory
		SDL_FreeSurface(surface);
	}

}

Player::~Player() {

}

void Player::draw(SDL_Renderer* renderer) {
	// Create rectangle using position and dimensions
	SDL_Rect rect = { _x, _y, _w, _h };

	if (_sprites.at(dir)->_sprite_clips == nullptr) {
		std::cerr << "Clips are empty.\n";
		return;
	}

	//reloadTexture(renderer, _sprites.at(dir)->_texture_path);

	_texture = textures.at(dir);

	if (walking) {
		frame++;
		if (frame / 5 >= _sprites.at(dir)->_sprite_num) 
			frame = 0;
	}
	
	// Set the rectangle to be the size of the sprite
	rect.w = _sprites.at(dir)->_sprite_clips[frame/5].w;
	rect.h = _sprites.at(dir)->_sprite_clips[frame/5].h;

	// If texture exists, then copy texture to rectangle. 
	if (_texture) {
	SDL_RenderCopy(renderer, _texture, &_sprites.at(dir)->_sprite_clips[frame/5], &rect);
	}
}

/*
void Player::reloadTexture(SDL_Renderer* renderer, std::string image_path)
{
	// Create surface from image using file path
	auto surface = IMG_Load(image_path.c_str());

	// Check if surface was created successfully
	if (!surface) {
		std::cerr << "Failed to create player surface.\n";
	}

	// Create texture from surface
	_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// Check if texture was created successfully
	if (!_texture) {
		std::cerr << "Failed to create player texture.\n";
	}

	// Free surface memory
	SDL_FreeSurface(surface);
}
*/


void Player::processInput() {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_A]) {
		walking = true;
		dir = left;
		frame = 0;
		_x -= 3;
	}
	if (keystate[SDL_SCANCODE_D]) {
		walking = true;
		dir = right;
		frame = 0;
		_x += 3;
	}
	if (keystate[SDL_SCANCODE_W]) {
		walking = true;
		dir = up;
		frame = 0;
		_y -= 3;
	}
	if (keystate[SDL_SCANCODE_S]) {
		walking = true;
		dir = down;
		frame = 0;
		_y += 3;
	}
}

void Player::pollEvents(SDL_Event& event) {
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_UP:
			break;
		case SDLK_DOWN:
			break;
		}
	}

	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_a:
			walking = false;
			break;
		case SDLK_d:
			walking = false;
			break;
		case SDLK_w:
			walking = false;
		case SDLK_s:
			walking = false;
			break;
		}
	}
}

void Player::shoot(int diff_x, int diff_y) {
	if (walking)
		return;
	if (abs(diff_x) > abs(diff_y)) {
		if (diff_x > 0) { // Left
			dir = left;
			frame = 0;
		}
		else { // Right
			dir = right;
			frame = 0;
		}
	}
	else {
		if (diff_y > 0) { // Up
			dir = up;
			frame = 0;
		}
		else { // Down
			dir = down;
			frame = 0;
		}
	}
}
