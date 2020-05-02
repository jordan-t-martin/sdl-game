#pragma once
#include "rect.h"
#include "text.h"
#include <map>


class Target : public Rect {
public:
	Target(SDL_Renderer* renderer, int w, int h, int x, int y, const std::string& image_path);
	~Target();

	void update();
	void draw(SDL_Renderer* renderer);
	void hit(SDL_Renderer* renderer);
	bool isDead();


private:
	int health = 100;
	Text* health_text;

	// Constants for text
	const std::string FONT_PATH = "assets/consola.ttf";
	const int FONT_SIZE = 30;
	const SDL_Color WHITE = { 255, 255, 255, 0 };
};