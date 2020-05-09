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

// Poll all events in objects and pause
void pollEvents(Window& window, Player& player, Projectile& projectiles, bool& start, bool& paused, bool& quit) {
	SDL_Event event;

	if (SDL_PollEvent(&event)){
		window.pollEvents(event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
			start = true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			quit = true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
			if(start)
				paused = !paused;
		}
		if (!paused)
		{
			player.pollEvents(event);
			projectiles.pollEvents(event);
			//window.pollEvents(event);
		}
	}
}

void pause(Window& window, SDL_Renderer* renderer, Rect screenshot) {
	//Rect screenshot = Rect(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, window.saveScreenshot());
	Text pause_text = Text(renderer, "assets/consolab.ttf", 30, "PAUSED", { 255, 0, 0 , 255 }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
	pause_text.draw(renderer);
	screenshot.draw(renderer);
	window.clear();
}

int main(int argc, char** argv) {
	
	// Create all game objects

	// Game window
	Window window("Target Practice!", SCREEN_WIDTH, SCREEN_HEIGHT);

	// Cursor image
	std::shared_ptr<Rect> cursor(new Rect(Window::renderer, 64, 64, 0, 0, "assets/textures/reticle_sprite.png"));

	// Still objects
	Rect wall(Window::renderer, 840, 320, 0, 0, "assets/textures/wood.png");
	Rect dirt(Window::renderer, 840, 120, 0, 320, 101, 67, 33, 80);
	Rect grass(Window::renderer, 840, 200, 0, 440, 125, 125, 130, 100);

	// Player character
	std::shared_ptr<Player> player(new Player(Window::renderer, 64, 64, 500, 500, 0, 0, 0, 0));

	// Targets and bullets
	std::shared_ptr<Projectile> projectiles(new Projectile(Window::renderer));

	// Text
	Text title(Window::renderer, "assets/consolab.ttf", 30, "Target Practice!", { 255, 255, 255 , 255 }, 20, 20);
	Text score(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles->getScore()), { 255, 255, 255 , 255 }, 20, 80);
	Text start_text = Text(Window::renderer, "assets/consolab.ttf", 50, "PRESS ENTER TO START", { 255, 255, 255 , 255 }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	start_text.center();
	Text pause_text = Text(Window::renderer, "assets/consolab.ttf", 50, "PAUSED", { 255, 255, 255 , 255 }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	pause_text.center();
	Text end_text = Text(Window::renderer, "assets/consolab.ttf", 30, "PRESS ENTER TO PLAY AGAIN. PRESS ESCAPE TO QUIT.", { 255, 255, 255 , 255 }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	end_text.center();

	// Timer
	std::shared_ptr<Timer> timer(new Timer(Window::renderer));

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

	// Game loop, stops if window is closed
	while (!window.isClosed()) {
		timer->start();
		while (!window.isClosed() && start) {
			pollEvents(window, *player, *projectiles, start, paused, quit);

			// Still objects
			wall.draw(Window::renderer);
			grass.draw(Window::renderer);
			dirt.draw(Window::renderer);

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

			if (paused) {
				timer->pause();
				pause_text.draw(Window::renderer);
				window.clear();
				while (paused && !quit)
					pollEvents(window, *player, *projectiles, start, paused, quit);
				timer->unpause();
			}
			else {
				// Update screen with all draws
				window.clear();
			}
		}

		timer->stop();

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

		if (quit)
			break;

		if (start) {
			// Player character
			player.reset(new Player(Window::renderer, 64, 64, 500, 500, 0, 0, 0, 0));

			// Targets and bullets
			projectiles.reset(new Projectile(Window::renderer));

			// Text

			Text score(Window::renderer, "assets/consolab.ttf", 30, "Score: " + std::to_string(projectiles->getScore()), { 255, 0, 0 , 255 }, 20, 80);
			
			// Timer
			timer.reset(new Timer(Window::renderer));

			bool paused = false;
			bool start = true;
			bool quit = false;
		}

	}

	// Successful exit
	return 0;
}