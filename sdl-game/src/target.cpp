#include "target.h"

Target::Target(SDL_Renderer* renderer, int w, int h, int x, int y, const std::string& image_path) 
	: Rect(renderer, w, h, x, y, image_path)
{
	health_text = new Text(renderer, "assets/consola.ttf", 30, std::to_string(health), { 255, 0, 0 , 255 });
}

Target::~Target() {

}

void Target::update(SDL_Renderer* renderer) {
	health_text->reloadTexture(renderer, "assets/consola.ttf", 30, std::to_string(health), { 0, 128, 0 , 255 });
	health_text->display(Rect::getX() + 5, Rect::getY() - 50, renderer);
}

void Target::hit() { 
	printf("Target hit!\n");
	health -= 10;
	printf("Health is now %d \n", health);
}

bool Target::isDead() {
	if (health <= 0) { return true; }
	else return false;
}