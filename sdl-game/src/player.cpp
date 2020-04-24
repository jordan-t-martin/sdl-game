#include "player.h"
#include <iostream>
#include <math.h>

// Use color contructor because multiple sprites are passed in to process textures
Player::Player(SDL_Renderer* renderer, int w, int h, int x, int y, int r, int g, int b, int a)
	: Rect(renderer, w, h, x, y, r, g, b, a)
{
	// Self create sprites
	_sprites = createSprites();
	
	// For all sprites created...
	for (int i = 0; i < _sprites.size(); i++) {
		// Create surface from image using file path
		auto surface = IMG_Load(_sprites.at(i)->_texture_path.c_str());

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

		// Add texture to vector
		_textures.push_back(texture);

		// Free surface memory
		SDL_FreeSurface(surface);
	}

}

Player::~Player() {
	// Destroy textures
	for(auto texture : _textures)
		if (texture != NULL)
			SDL_DestroyTexture(texture);
}

// Create and return sprites using constant values from class
std::vector<std::shared_ptr<Sprite>> Player::createSprites() {

	// Vector to hold sprites
	std::vector<std::shared_ptr<Sprite>> sprites;

	// Create sprites from constants
	std::shared_ptr<Sprite> left(new Sprite(PLAYER_LEFT_FRAMES, PLAYER_SIZE, PLAYER_LEFT_PATH));
	std::shared_ptr<Sprite> right(new Sprite(PLAYER_RIGHT_FRAMES, PLAYER_SIZE, PLAYER_RIGHT_PATH));
	std::shared_ptr<Sprite> up(new Sprite(PLAYER_UP_FRAMES, PLAYER_SIZE, PLAYER_UP_PATH));
	std::shared_ptr<Sprite> down(new Sprite(PLAYER_DOWN_FRAMES, PLAYER_SIZE, PLAYER_DOWN_PATH));

	// Load into vector
	sprites.push_back(left);
	sprites.push_back(right);
	sprites.push_back(up);
	sprites.push_back(down);

	return sprites;
}

// Render updates to the screen every tick
void Player::draw(SDL_Renderer* renderer) {
	// Create rectangle using position and dimensions
	SDL_Rect rect = { _x, _y, _w, _h };

	// Check that clips exists
	if (_sprites.at(_dir)->_sprite_clips == nullptr) {
		std::cerr << "Clips are empty.\n";
		return;
	}

	// Switch texture to correct direction
	_texture = _textures.at(_dir);

	// If character is walking...
	if (_walking) {
		// Increment animation frame
		_frame++;

		// If animation frame is greater than number of sprites, reset frame to 0 
		// Divide by animation speed to slow animation over game loop
		if (_frame / _anim_speed >= _sprites.at(_dir)->_sprite_num) 
			_frame = 0;
	}
	
	// Set the rectangle to be the size of the sprite using clips
	rect.w = _sprites.at(_dir)->_sprite_clips[_frame/_anim_speed].w;
	rect.h = _sprites.at(_dir)->_sprite_clips[_frame/_anim_speed].h;

	// If texture exists, then copy texture to rectangle. 
	if (_texture) {
		// Pass in clip to render only portion of texture onto rect
		SDL_RenderCopy(renderer, _texture, &_sprites.at(_dir)->_sprite_clips[_frame/_anim_speed], &rect);
	}
}

// Make updates to player every tick
void Player::update() {
	// Get state of keyboard to detect holding down of keys
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	// When key is held for WASD
	// - Set walking state to true
	// - Change direction
	// - Reset frame so new animation can start
	// - Adjust position

	if (keystate[SDL_SCANCODE_A]) { // [A] key
		_walking = true;
		_dir = left;
		_frame = 0;
		_x -= 3;
	}
	if (keystate[SDL_SCANCODE_D]) { // [D] key
		_walking = true;
		_dir = right;
		_frame = 0;
		_x += 3;
	}
	if (keystate[SDL_SCANCODE_W]) { // [W] key
		_walking = true;
		_dir = up;
		_frame = 0;
		_y -= 3;
	}
	if (keystate[SDL_SCANCODE_S]) { // [S] key
		_walking = true;
		_dir = down;
		_frame = 0;
		_y += 3;
	}
}

// Check if an event has happened every tick
void Player::pollEvents(SDL_Event& event) {
	// If a key is pressed down
	if (event.type == SDL_KEYDOWN) {

	}
	// If a key is released
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		// For WASD keys, set walking state to false when key is released

		case SDLK_a: // [A] key
			_walking = false;
			break;
		case SDLK_d: // [D] key
			_walking = false;
			break;
		case SDLK_w: // [W] key
			_walking = false;
			break;
		case SDLK_s: // [S] key
			_walking = false;
			break;
		}
	}
}

// Handle player variables when shooting
// Takes is horizontal/vertical distance from start to end
void Player::shoot(int diff_x, int diff_y) {
	// Shooting is not allowed while walking, do nothing
	if (_walking)
		return;

	// Determine which way to face when making a shot
	// Face the direction in which distance from start to finish is furthest
	// Change direction and reset animation frame 

	// If the end point is further horizontally
	if (abs(diff_x) > abs(diff_y)) {
		// If the end point is further to the left
		if (diff_x > 0) {
			_dir = left;
			_frame = 0;
		}
		// If the end point is further to the right
		else { 
			_dir = right;
			_frame = 0;
		}
	}
	// If the end point is further vertically
	else {
		// If the end point is further upwards
		if (diff_y > 0) {
			_dir = up;
			_frame = 0;
		}
		// If the end point is further downwards
		else { 
			_dir = down;
			_frame = 0;
		}
	}
}

