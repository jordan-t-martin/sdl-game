#include "window.h"
#include "rect.h"
#include "player.h"
#include "projectile.h"
#include "text.h"
#include "sprite.h"
#include "target.h"
#include <vector>
#include <string>
#include <iostream>

// Screen dimensions
const int SCREEN_WIDTH = 840;
const int SCREEN_HEIGHT = 640;

// Poll all events in each object
void pollEvents(Window& window, Rect& rect, std::vector<std::shared_ptr<Target>> targets, Player& player, Projectile& projectiles) {
	SDL_Event event;

	if (SDL_PollEvent(&event)){
		rect.pollEvents(event);
		for (int i = 0; i < targets.size(); i++) {
			targets.at(i)->pollEvents(event);
		}
		
		player.pollEvents(event);
		projectiles.pollEvents(event);
		window.pollEvents(event);
	}
}

std::vector<std::shared_ptr<Sprite>> createSprites()
{

	std::vector<std::shared_ptr<Sprite>> sprites;
	std::shared_ptr<Sprite> spr1(new Sprite(4, 74, "assets/sprite-sheets/player_left.png"));
	std::shared_ptr<Sprite> spr2(new Sprite(4, 74, "assets/sprite-sheets/player_right.png"));
	std::shared_ptr<Sprite> spr3(new Sprite(8, 74, "assets/sprite-sheets/player_up.png"));
	std::shared_ptr<Sprite> spr4(new Sprite(8, 74, "assets/sprite-sheets/player_down.png"));
	sprites.push_back(spr1);
	sprites.push_back(spr2);
	sprites.push_back(spr3);
	sprites.push_back(spr4);
	return sprites;
}

int main(int argc, char** argv) {
	
	// Create all game objects
	Window window("SDL_Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	Rect rect(Window::renderer, 840, 320, 0, 0, "assets/textures/wood.png");
	std::shared_ptr<Rect> cursor(new Rect(Window::renderer, 64, 64, 0, 0, "assets/textures/reticle_sprite.png"));

	std::shared_ptr<Target> target1(new Target(Window::renderer, 56, 56, 100, 100, "assets/textures/target.png"));
	std::shared_ptr<Target> target2(new Target(Window::renderer, 56, 56, 200, 100, "assets/textures/target.png"));
	std::shared_ptr<Target> target3(new Target(Window::renderer, 56, 56, 400, 100, "assets/textures/target.png"));
	std::shared_ptr<Target> target4(new Target(Window::renderer, 56, 56, 500, 100, "assets/textures/target.png"));
	std::vector<std::shared_ptr<Target>> targets;
	targets.push_back(target1);
	targets.push_back(target2);
	targets.push_back(target3);
	targets.push_back(target4);

	std::shared_ptr<Player> player(new Player(Window::renderer, 64, 64, 500, 500, createSprites()));
	Projectile projectiles(Window::renderer);
	Text text(Window::renderer, "assets/consolab.ttf", 30, "Target Practice!", { 255, 0, 0 , 255 });
	Text score(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles.score), { 255, 0, 0 , 255 });

	// Game loop, stops if window is closed
	while (!window.isClosed()) {
		pollEvents(window, rect, targets, *player, projectiles);
		rect.draw(Window::renderer);
		if(targets.size() != 0)
			for (auto target : targets) {
				target->draw(Window::renderer);
				target->update(Window::renderer);
			}
		player->draw(Window::renderer);
		player->processInput();
		projectiles.update(Window::renderer, targets);
		projectiles.processInput(Window::renderer, player);
		text.display(20, 20, Window::renderer);
		score.reloadTexture(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles.score), { 255, 0, 0 , 255 });
		score.display(20, 50, Window::renderer);
		cursor->draw(Window::renderer);
		window.update(cursor);
		window.clear();
	}

	return 0;
}