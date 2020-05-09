#include "player.h"

// Use color contructor as no need for image path. Sprites will be used instead.
Player::Player(SDL_Renderer* renderer, int w, int h, int x, int y, int r, int g, int b, int a)
	: Rect(renderer, w, h, x, y, r, g, b, a)
{
	// Get screen dimensions for out of bounds check
	SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);

	// Self create sprites
	_sprites = createSprites();
	
	// For all sprites
	for (size_t i = 0; i < _sprites.size(); i++) {
		// Create surface from image using file path
		auto surface = IMG_Load(_sprites.at(i)->getTexturePath().c_str());

		if (!surface) {
			std::cerr << "Failed to create player surface.\n";
		}

		// Create texture from surface
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (!texture) {
			std::cerr << "Failed to create player texture: " << i << "\n";
		}

		// Add spritesheet texture to vector
		_textures.push_back(texture);

		// Free surface memory
		SDL_FreeSurface(surface);
	}

}

Player::~Player() {
	for(auto texture : _textures)
		if (texture != NULL)
			SDL_DestroyTexture(texture);
}

std::vector<std::shared_ptr<Sprite>> Player::createSprites() {
	std::vector<std::shared_ptr<Sprite>> sprites;

	std::shared_ptr<Sprite> left(new Sprite(PLAYER_LEFT_SPRITE_NUM, PLAYER_SIZE, PLAYER_LEFT_PATH));
	std::shared_ptr<Sprite> right(new Sprite(PLAYER_RIGHT_SPRITE_NUM, PLAYER_SIZE, PLAYER_RIGHT_PATH));
	std::shared_ptr<Sprite> up(new Sprite(PLAYER_UP_SPRITE_NUM, PLAYER_SIZE, PLAYER_UP_PATH));
	std::shared_ptr<Sprite> down(new Sprite(PLAYER_DOWN_SPRITE_NUM, PLAYER_SIZE, PLAYER_DOWN_PATH));

	sprites.push_back(left);
	sprites.push_back(right);
	sprites.push_back(up);
	sprites.push_back(down);

	return sprites;
}

void Player::draw(SDL_Renderer* renderer) {
	// Create new rectangle using position and dimensions
	SDL_Rect rect = { _x, _y, _w, _h };

	if (_sprites.at(_dir)->getSpriteClips() == nullptr) {
		std::cerr << "Clips are empty.\n";
		return;
	}

	// Switch texture to correct direction
	_texture = _textures.at(_dir);

	// Reset frame if direction changed
	if (_dir != _prev_dir)
		_frame = 0;

	// If character is walking, play animation
	if (_walking) {
		// Increment animation frame
		_frame++;

		// If animation frame is greater than number of sprites, reset frame to 0 
		// Divide by animation speed to slow animation over game loop
		if (_frame / _anim_speed >= _sprites.at(_dir)->getSpriteNum()) 
			_frame = 0;
	}
	
	// Set the object rectangle to be the size of the sprite using clips
	rect.w = _sprites.at(_dir)->getSpriteClips()[_frame/_anim_speed].w;
	rect.h = _sprites.at(_dir)->getSpriteClips()[_frame/_anim_speed].h;

	if (_texture) {
		// Pass in clip to render only portion of spritesheet texture onto object rectangle
		SDL_RenderCopy(renderer, _texture, &_sprites.at(_dir)->getSpriteClips()[_frame/_anim_speed], &rect);
	}

	_prev_dir = _dir;
}

void Player::update() {
	// Get state of keyboard to detect holding down of keys
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_A]) { 
		_walking = true;
		_dir = left;
		if(!outOfBounds(_x - _player_speed, _y))
			_x -= _player_speed;
	}
	if (keystate[SDL_SCANCODE_D]) { 
		_walking = true;
		_dir = right;
		if (!outOfBounds(_x + _player_speed, _y))
			_x += _player_speed;
	}
	if (keystate[SDL_SCANCODE_W]) { 
		_walking = true;
		_dir = up;
		if (!outOfBounds(_x, _y - _player_speed))
			_y -= _player_speed;
	}
	if (keystate[SDL_SCANCODE_S]) { 
		_walking = true;
		_dir = down;
		if (!outOfBounds(_x, _y + _player_speed))
			_y += _player_speed;
	}
}

void Player::pollEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {

	}
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_a: 
			_walking = false;
			break;
		case SDLK_d: 
			_walking = false;
			break;
		case SDLK_w: 
			_walking = false;
			break;
		case SDLK_s: 
			_walking = false;
			break;
		}
	}
}

// Handle player variables when shooting
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

bool Player::outOfBounds(int x, int y) {
	return (
		x < 0 ||
		y < screen_height - 200 ||
		x + _w > screen_width ||
		y + _h > screen_height
	);
}
