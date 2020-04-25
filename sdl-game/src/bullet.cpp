#include "bullet.h"

#define PI 3.14159265

// take distance out
Bullet::Bullet(SDL_Renderer* renderer, int w, int h, float start_x, float start_y, float end_x, float end_y, int r, int g, int b, int a)
	: Rect(renderer, w, h, (int) start_x, (int) start_y, r, g, b, a),
	_start_x(start_x), _start_y(start_y), _end_x(end_x), _end_y(end_y)
{
	// Load sprites
	_sprites = createSprites();

	// Setup
	_start_v = Vector2(_start_x, _start_y);
	_end_v = Vector2(_end_x, _end_y);
	_position_v = Vector2((float) _x, (float) _y);
	_unit_v = _v.normalize(_v.subtract(_end_v, _start_v));

	// Find angle of unit vector
	Vector2 horz_unit_v = Vector2(1, 0);
	float degrees = (180 / (float) M_PI);
	_angle = acosf(_v.dot_product(_unit_v, horz_unit_v)) * degrees;

	// Create surface from image using file path
	auto surface = IMG_Load(_sprites.at(0)->getTexturePath().c_str());

	// Check if surface was created successfully
	if (!surface) {
		std::cerr << "Failed to create surface.\n";
	}

	// Create texture from surface
	_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// Check if texture was created successfully
	if (!_texture) {
		std::cerr << "Failed to create texture.\n";
	}

	// Free surface memory
	SDL_FreeSurface(surface);
}

Bullet::~Bullet() {

}

void Bullet::draw(SDL_Renderer* renderer) {
	// Create rectangle using position and dimensions
	SDL_Rect myrect = { _x, _y, _w, _h };

	// Index from 8 Directional
	_index = findDirection();

	// Check that clips exists
	if (_sprites.at(0)->getSpriteClips() == nullptr) {
		std::cerr << "Clips are empty.\n";
		return;
	}

	// Set the rectangle to be the size of the sprite using clips
	myrect.w = _sprites.at(0)->getSpriteClips()[_index].w;
	myrect.h = _sprites.at(0)->getSpriteClips()[_index].h;

	// If texture exists, then copy texture to rectangle. 
	if (_texture) {
		SDL_RenderCopy(renderer, _texture, &_sprites.at(0)->getSpriteClips()[_index], &myrect);
	}
}

void Bullet::update() {
	// Add how much position has moved at speed in elapsed time (game tick) in unit vector's direction
	_position_v = _v.add(_position_v, _v.multiply_scalar((_speed * _elapsed), _unit_v));
	
	// Update x/y coords with position vector
	_x = (int) _position_v.getX();
	_y = (int) _position_v.getY();
}

// Convert 360 degree angle to 8 directional for bullet sprite
int Bullet::findDirection() {

// Using arc cos to determine direction, angle gives only positive results.
// Need to determine if angle is positive or negative by comparing start and end Y-coordinate

	if (_angle <= 15) 
		return right;

	if (_angle > 15 && _angle <= 75) {
		if (_start_y > _end_y)
			return right_up;
		else 
			return right_down;
	}

	if (_angle > 75 && _angle <= 105) {
		if (_start_y > _end_y)
			return up;
		else 
			return down;
	}

	if (_angle > 105 && _angle <= 165) {
		if (_start_y > _end_y)
			return left_up;
		else
			return left_down;
	}

	if (_angle > 165)
		return left;

	else return -1;
}

// Create and return sprites using constant values from class
std::vector<std::shared_ptr<Sprite>> Bullet::createSprites() {

	// Vector to hold sprites
	std::vector<std::shared_ptr<Sprite>> sprites;

	// Create sprites from constants
	std::shared_ptr<Sprite> bullet(new Sprite(BULLET_SPRITE_NUM, BULLET_SPRITE_SIZE, BULLET_FILE_PATH));

	// Load into vector
	sprites.push_back(bullet);

	return sprites;
}