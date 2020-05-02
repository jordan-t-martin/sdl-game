#include "target.h"

Target::Target(SDL_Renderer* renderer, int w, int h, float start_x, float start_y, float end_x, float end_y, const std::string& image_path)
	: Rect(renderer, w, h, (int) start_x, (int) start_y, image_path),
	_start_x(start_x), _start_y(start_y), _end_x(end_x), _end_y(end_y)
{
	// Setup
	_start_v = Vector2(_start_x, _start_y);
	_end_v = Vector2(_end_x, _end_y);
	_position_v = Vector2((float) _x, (float)_y);
	_unit_v = _v.normalize(_v.subtract(_end_v, _start_v));

	_distance = _v.distance(_start_v, _end_v);

	_moving = true;

	_health_text = new Text(renderer, FONT_PATH, FONT_SIZE, std::to_string(_health), WHITE, _x + 5, _y - 50);
}

Target::~Target() {

}

void Target::update() {
	
	// Add how much position has moved at speed in elapsed time (game tick) in unit vector's direction
	if (_moving)
		_position_v = _v.add(_position_v, _v.multiply_scalar((_speed * _elapsed), _unit_v));

	if (_v.distance(_start_v, _position_v) > _distance) {
		//_position_v = _end_v;
		//_moving = false;
		swapPoints();
	}
	// Update x/y coords with position vector
	_x = (int)_position_v.getX();
	_y = (int)_position_v.getY();
	_health_text->setX(_x + 5);
	_health_text->setY(_y - 30);
}

void Target::draw(SDL_Renderer* renderer) {
	_health_text->draw(renderer);
	Rect::draw(renderer);
}

void Target::hit(SDL_Renderer* renderer) {
	_health -= 10;
	_health_text->reloadTexture(renderer, std::to_string(_health), WHITE);
}

bool Target::isDead() {
	if (_health <= 0) 
		return true; 

	return false;
}

void Target::swapPoints() {
	Vector2 temp = _end_v;
	_end_v = _start_v;
	_start_v = temp;
	_unit_v = _v.normalize(_v.subtract(_end_v, _start_v));
}