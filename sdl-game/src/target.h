#pragma once
#include "rect.h"
#include "text.h"
#include <vector>
#include <string>
#include <map>


class Target : public Rect {
public:
	Target(SDL_Renderer* renderer, int w, int h, int x, int y, const std::string& image_path);
	~Target();
	void update(SDL_Renderer* renderer);
	void hit();
	bool isDead();
	int health = 100;
	Text* health_text;
};