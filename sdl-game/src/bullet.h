#pragma once
#include "rect.h"
#include <vector>
#include <iostream>
#include <math.h>
#include "sprite.h"
#include "vector2.h"

class Bullet : public Rect
{
	public:
		Bullet(SDL_Renderer* renderer, int w, int h, float start_x, float start_y, float end_x, float end_y, int range, int speed, int distance, std::vector<std::shared_ptr<Sprite>> sprites);
		~Bullet();
		int findDirection();
		void draw(SDL_Renderer* renderer);
		void update();

		int _index = 0;
		float _angle;
		bool _moving;
		float _start_x, _start_y, _end_x, _end_y;
		float _range, _speed, _elapsed, _distance;
		enum direction{down, right_down, left_up, left_down, left, right_up, right, up };
		std::vector<std::shared_ptr<Sprite>> _sprites;
		SDL_Texture* _texture = nullptr;
		Vector2 v, _direction, _position;
		Vector2* _start_v;
		Vector2* _end_v;
		Vector2 test;
};