#pragma once
#include "rect.h"
#include "text.h"
#include "vector2.h"
#include <map>


class Target : public Rect {
public:
	Target(SDL_Renderer* renderer, int w, int h, float start_x, float start_y, float end_x, float end_y, const std::string& image_path);
	~Target();

	void update();
	void draw(SDL_Renderer* renderer);
	void hit(SDL_Renderer* renderer);
	bool isDead();


private:

	void swapPoints();


	int _health = 50;
	bool _moving;
	float _start_x, _start_y, _end_x, _end_y;
	float _speed = 250, _elapsed = 0.01f, _distance;
	Text* _health_text;
	Vector2  _v, _start_v, _end_v, _unit_v, _position_v;

	// Constants for text
	const std::string FONT_PATH = "assets/consola.ttf";
	const int FONT_SIZE = 30;
	const SDL_Color WHITE = { 255, 255, 255, 0 };
};