#pragma once
#include "rect.h"
#include "sprite.h"
#include <vector>
#include <iostream>
#include <string>

class Player : public Rect {
public:	
	Player(SDL_Renderer* renderer, int w, int h, int x, int y, int r, int g, int b, int a);
	Player(SDL_Renderer* renderer, int w, int h, int x, int y, std::vector<std::shared_ptr<Sprite>> sprites);
	~Player();

	void draw(SDL_Renderer* renderer);
	void reloadTexture(SDL_Renderer* renderer, std::string image_path);
	void processInput();
	void pollEvents(SDL_Event& event);
	void shoot(int diff_x, int diff_y);

	enum direction{ left, right, up, down };
	std::vector<std::shared_ptr<Sprite>> _sprites;
	int frame = 0;
	std::vector<SDL_Texture*> textures;
	bool walking = false; // Start facing down
	int dir = down;
	SDL_Texture* _texture = nullptr;
};
