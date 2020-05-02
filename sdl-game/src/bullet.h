#pragma once
#include "rect.h"
#include "sprite.h"
#include "vector2.h"
#include <vector>
#include <iostream>
#include <math.h>


class Bullet : public Rect
{
	public:
		Bullet(SDL_Renderer* renderer, int w, int h, float start_x, float start_y, float end_x, float end_y, int r, int g, int b, int a);
		~Bullet();

		
		void update();
		void draw(SDL_Renderer* renderer);
		
		enum direction{down, right_down, left_up, left_down, left, right_up, right, up };

	private:
		int findDirection();
		std::vector<std::shared_ptr<Sprite>> createSprites();

		int _index = 0;
		float _start_x, _start_y, _end_x, _end_y;
		float _angle, _speed = 1500, _elapsed = 0.01f;
		Vector2  _v, _start_v, _end_v, _unit_v, _position_v;
		SDL_Texture* _texture = nullptr;
		std::vector<std::shared_ptr<Sprite>> _sprites;

		// Constants for sprite creation
		const std::string BULLET_FILE_PATH = "assets/sprite-sheets/bullet.png";
		const int BULLET_SPRITE_NUM = 8;
		const int BULLET_SPRITE_SIZE = 12;
};