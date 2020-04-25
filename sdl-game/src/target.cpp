#include "target.h"

Target::Target(SDL_Renderer* renderer, int w, int h, int x, int y, const std::string& image_path) 
	: Rect(renderer, w, h, x, y, image_path)
{
	health_text = new Text(renderer, FONT_PATH, FONT_SIZE, std::to_string(health), green, _x + 5, _y - 50);
}

Target::~Target() {

}

void Target::update(SDL_Renderer* renderer) {
	health_text->draw(renderer);
}

void Target::hit(SDL_Renderer* renderer) {
	health -= 10;
	health_text->reloadTexture(renderer, FONT_PATH, FONT_SIZE, std::to_string(health), green);
}

bool Target::isDead() {
	if (health <= 0) 
		return true; 

	return false;
}