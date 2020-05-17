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

const int SCREEN_WIDTH = 840;
const int SCREEN_HEIGHT = 640;
const std::string FONT_PATH_BOLD = "assets/consolab.ttf";
const int FONT_SIZE_SMALL = 30;
const int FONT_SIZE_BIG = 50;
const SDL_Color WHITE = { 255, 255, 255 , 255 };

// Poll all events in game loop and objects
void pollEvents(Window& window, Player& player, Projectile& projectiles, bool& start, bool& paused, bool& quit) {
	SDL_Event event;

	if (SDL_PollEvent(&event)){
		// Window [X] button
		window.pollEvents(event, quit);

		// Start, quit, pause
		if(event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym) {
			case (SDLK_RETURN):
				start = true;
				break;
			case (SDLK_ESCAPE):
				quit = true;
				break;
			case (SDLK_p):
				if (start)
					paused = !paused;
			}

		// Objects
		if (!paused)
		{
			player.pollEvents(event);
			projectiles.pollEvents(event);
		}
	}
}

int main(int argc, char** argv) {
	
// Create all game objects

	// Game window
	Window window("Target Practice!", SCREEN_WIDTH, SCREEN_HEIGHT);

	// Cursor image
	std::shared_ptr<Rect> cursor(new Rect(Window::renderer, 64, 64, 0, 0, "assets/textures/reticle_sprite.png"));

	// Still objects
	Rect wall(Window::renderer, SCREEN_WIDTH, 320, 0, 0, "assets/textures/wood.png");
	Rect dirt(Window::renderer, SCREEN_WIDTH, 120, 0, 320, 101, 67, 33, 80);
	Rect grass(Window::renderer, SCREEN_WIDTH, 200, 0, 440, 125, 125, 130, 100);

	// Player character
	std::shared_ptr<Player> player(new Player(Window::renderer, 64, 64, 500, 500, 0, 0, 0, 0));

	// Targets and bullets
	std::shared_ptr<Projectile> projectiles(new Projectile(Window::renderer));

	// Text
	Text title(Window::renderer, FONT_PATH_BOLD, FONT_SIZE_SMALL, "Target Practice!", WHITE, 20, 20);
	Text score(Window::renderer, FONT_PATH_BOLD, FONT_SIZE_SMALL, "Score: " + std::to_string(projectiles->getScore()), WHITE, 20, 80);
	Text start_text = Text(Window::renderer, FONT_PATH_BOLD, FONT_SIZE_BIG, "PRESS ENTER TO START", WHITE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	start_text.center();
	Text pause_text = Text(Window::renderer, FONT_PATH_BOLD, FONT_SIZE_BIG, "PAUSED", WHITE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	pause_text.center();
	Text end_text = Text(Window::renderer, FONT_PATH_BOLD, FONT_SIZE_SMALL, "PRESS ENTER TO PLAY AGAIN. PRESS ESCAPE TO QUIT.", WHITE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	end_text.center();

	// Timer
	std::shared_ptr<Timer> timer(new Timer(Window::renderer));

	// Flags
	bool paused = false;
	bool start = false;
	bool quit = false;


	// Start screen
	wall.draw(Window::renderer);
	grass.draw(Window::renderer);
	dirt.draw(Window::renderer);
	start_text.draw(Window::renderer);
	window.clear();
	while (!start && !quit)
		pollEvents(window, *player, *projectiles, start, paused, quit);

	// New game
	while (!window.isClosed()) {
		timer->start();

		// Game loop
		// Poll events, update, and draw all objects
		while (!window.isClosed() && start && !quit) {
			pollEvents(window, *player, *projectiles, start, paused, quit);

			// Still objects
			wall.draw(Window::renderer);
			grass.draw(Window::renderer);
			dirt.draw(Window::renderer);

			// Check if game has ended
			if (projectiles->win()) {
				start = false;
				break;
			}

			// Player character
			player->update();
			player->draw(Window::renderer);

			// Targets and bullets
			projectiles->update(Window::renderer, player);
			projectiles->draw(Window::renderer);

			// Text 
			title.draw(Window::renderer);
			score.reloadTexture(Window::renderer, "Score: " + std::to_string(projectiles->getScore()), { 255, 255, 255 , 255 });
			score.draw(Window::renderer);

			// Timer
			timer->update(Window::renderer);
			timer->draw(Window::renderer);

			// Cursor image
			window.update(cursor);
			cursor->draw(Window::renderer);

			// Check for pause event
			if (paused) {
				timer->pause();
				pause_text.draw(Window::renderer);
				window.clear();
				while (paused && !quit)
					pollEvents(window, *player, *projectiles, start, paused, quit);
				timer->unpause();
			}
			else {
				window.clear();
			}
		}

		// If break out of loop, game has ended
		timer->stop();

		// Give user choice to quit or start again
		if (!start && !quit) {
			end_text.draw(Window::renderer);
			timer->setX(SCREEN_WIDTH / 2);
			timer->setY(SCREEN_HEIGHT / 2 + 50);
			timer->center();
			timer->draw(Window::renderer);
			window.clear();
			while (!start && !quit)
				pollEvents(window, *player, *projectiles, start, paused, quit);
		}

		// Exit the game
		if (quit)
			break;

		// New game
		if (start) {
			// Reset objects and variables
			player.reset(new Player(Window::renderer, 64, 64, 500, 500, 0, 0, 0, 0));
			projectiles.reset(new Projectile(Window::renderer));
			timer.reset(new Timer(Window::renderer));

			bool paused = false;
			bool start = true;
			bool quit = false;
		}

	}

	return 0;
}