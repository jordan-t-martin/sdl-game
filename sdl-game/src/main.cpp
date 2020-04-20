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
void pollEvents(Window& window, Player& player, Projectile& projectiles) {
	SDL_Event event;

	if (SDL_PollEvent(&event)){
		player.pollEvents(event);
		projectiles.pollEvents(event);
		window.pollEvents(event);
	}
}

int main(int argc, char** argv) {
	
	// Create all game objects
	Window window("SDL_Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	Rect rect(Window::renderer, 840, 320, 0, 0, "assets/textures/wood.png");
	std::shared_ptr<Rect> cursor(new Rect(Window::renderer, 64, 64, 0, 0, "assets/textures/reticle_sprite.png"));
	std::shared_ptr<Player> player(new Player(Window::renderer, 64, 64, 500, 500, 0, 0, 0, 0));
	Projectile projectiles(Window::renderer);
	Text title(Window::renderer, "assets/consolab.ttf", 30, "Target Practice!", { 255, 0, 0 , 255 });
	Text score(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles.score), { 255, 0, 0 , 255 });

	// Game loop, stops if window is closed
	while (!window.isClosed()) {
		pollEvents(window, *player, projectiles);
		// Custom image cursor
		window.update(cursor);
		cursor->draw(Window::renderer);

		// Still textures
		rect.draw(Window::renderer);

		// Player character
		player->update();
		player->draw(Window::renderer);

		// Targets and bullets
		projectiles.update(Window::renderer, player);
		projectiles.draw(Window::renderer);

		// Text 
		title.display(20, 20, Window::renderer);
		score.reloadTexture(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles.score), { 255, 0, 0 , 255 });
		score.display(20, 50, Window::renderer);
		
		window.clear();
	}

	return 0;
}