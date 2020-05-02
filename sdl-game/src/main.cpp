#include "window.h"
#include "rect.h"
#include "player.h"
#include "projectile.h"
#include "text.h"
#include "sprite.h"
#include "target.h"
#include "timer.h"
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
	Rect wall(Window::renderer, 840, 320, 0, 0, "assets/textures/wood.png");
	Rect dirt(Window::renderer, 840, 120, 0, 320, 101, 67, 33, 80);
	Rect grass(Window::renderer, 840, 200, 0, 440, 0, 120, 0, 100);

	// Player character
	std::shared_ptr<Player> player(new Player(Window::renderer, 64, 64, 500, 500, 0, 0, 0, 0));

	// Targets and bullets
	Projectile projectiles(Window::renderer);

	// Text
	Text title(Window::renderer, "assets/consolab.ttf", 30, "Target Practice!", { 255, 0, 0 , 255 }, 20, 20);
	Text score(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles.getScore()), { 255, 0, 0 , 255 }, 20, 80);

	// Timer
	Timer timer(Window::renderer);

	// Game loop, stops if window is closed
	while (!window.isClosed()) {
		pollEvents(window, *player, projectiles);

		// Still objects
		wall.draw(Window::renderer);
		grass.draw(Window::renderer);
		dirt.draw(Window::renderer);

		// Player character
		player->update();
		player->draw(Window::renderer);

		// Targets and bullets
		projectiles.update(Window::renderer, player);
		projectiles.draw(Window::renderer);
		if (projectiles.win())
			break;

		// Text 
		title.draw(Window::renderer);
		score.reloadTexture(Window::renderer, "Score: " + std::to_string(projectiles.getScore()), { 255, 0, 0 , 255 });
		score.draw(Window::renderer);
		
		// Timer
		timer.update(Window::renderer);
		timer.draw(Window::renderer);

		// Cursor image
		window.update(cursor);
		cursor->draw(Window::renderer);

		// Update screen with all draws
		window.clear();
	}

	// Successful exit
	return 0;
}