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

	// Game window
	Window window("SDL_Game", SCREEN_WIDTH, SCREEN_HEIGHT);

	// Cursor image
	std::shared_ptr<Rect> cursor(new Rect(Window::renderer, 64, 64, 0, 0, "assets/textures/reticle_sprite.png"));

	// Still objects
	Rect rect(Window::renderer, 840, 320, 0, 0, "assets/textures/wood.png");

	// Player character
	std::shared_ptr<Player> player(new Player(Window::renderer, 64, 64, 500, 500, 0, 0, 0, 0));

	// Targets and bullets
	Projectile projectiles(Window::renderer);

	// Text
	Text title(Window::renderer, "assets/consolab.ttf", 30, "Target Practice!", { 255, 0, 0 , 255 }, 20, 20);
	Text score(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles.getScore()), { 255, 0, 0 , 255 }, 20, 50);
	int prev_score = 0;

	// Game loop, stops if window is closed
	while (!window.isClosed()) {
		pollEvents(window, *player, projectiles);

		// Still objects
		rect.draw(Window::renderer);

		// Player character
		player->update();
		player->draw(Window::renderer);

		// Targets and bullets
		projectiles.update(Window::renderer, player);
		projectiles.draw(Window::renderer);

		// Text 
		title.draw(Window::renderer);
		if(projectiles.getScore() != prev_score)
			score.reloadTexture(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles.getScore()), { 255, 0, 0 , 255 });
		score.draw(Window::renderer);
		
		// Cursor image
		window.update(cursor);
		cursor->draw(Window::renderer);

		// Update screen with all draws
		window.clear();

		prev_score = projectiles.getScore();
	}

	// Successful exit
	return 0;
}