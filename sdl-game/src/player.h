#pragma once
#include "rect.h"
#include "sprite.h"
#include <vector>
#include <iostream>
#include <math.h>

class Player : public Rect {
public:	
	Player(SDL_Renderer* renderer, int w, int h, int x, int y, int r, int g, int b, int a);
	~Player();

	void draw(SDL_Renderer* renderer);
	void update();
	void pollEvents(SDL_Event& event);
	void shoot(int diff_x, int diff_y);
	
	int inline getDir() { return _dir; }
	bool inline getWalking() { return _walking; }
	void inline setDir(int dir) { _dir = dir; }
	void inline setWalking(bool walking) { _walking = walking; }
	
	enum direction{ left, right, up, down };

private:
	std::vector<std::shared_ptr<Sprite>> createSprites();

	int _frame = 0;
	int _dir = down;
	int _anim_speed = 5;
	bool _walking = false; 
	std::vector<SDL_Texture*> _textures;
	std::vector<std::shared_ptr<Sprite>> _sprites;

	// Constant values for sprite creation
	const std::string PLAYER_LEFT_PATH = "assets/sprite-sheets/player_left.png";
	const std::string PLAYER_RIGHT_PATH = "assets/sprite-sheets/player_right.png";
	const std::string PLAYER_UP_PATH = "assets/sprite-sheets/player_up.png";
	const std::string PLAYER_DOWN_PATH = "assets/sprite-sheets/player_down.png";
	const int PLAYER_SIZE = 74;
	const int PLAYER_LEFT_SPRITE_NUM = 4;
	const int PLAYER_RIGHT_SPRITE_NUM = 4;
	const int PLAYER_UP_SPRITE_NUM = 8;
	const int PLAYER_DOWN_SPRITE_NUM = 8;
};
