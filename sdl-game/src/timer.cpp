#include "timer.h"

Timer::Timer(SDL_Renderer* renderer) {
	_text = new Text(renderer, FONT_PATH, FONT_SIZE, START_TEXT, WHITE, _x, _y);

	_start_ticks = 0;
	_paused_ticks = 0;

	_paused = false;
	_started = false;
}

void Timer::start() {
	_started = true;

	_paused = false;

	// Get the current clock time
	_start_ticks = SDL_GetTicks();
	_paused_ticks = 0;
}

void Timer::stop() {
	_started = false;

	_paused = false;

	_start_ticks = 0;
	_paused_ticks = 0;
}

void Timer::pause() {
	// Timer must be running and not already paused
	if (_started && !_paused) {
		_paused = true;

		_paused_ticks = SDL_GetTicks() - _start_ticks;
		_start_ticks = 0;
	}
}

void Timer::unpause() {
	// Timer must be running and already paused
	if (_started && _paused) {
		_paused = false;

		_start_ticks = SDL_GetTicks() - _paused_ticks;

		_paused_ticks = 0;
	}
}

Uint32 Timer::getTicks() {
	Uint32 time = 0;

	if (_started) {
		if (_paused) {
			time = _paused_ticks;
		}
		else {
			time = (SDL_GetTicks() - _start_ticks);
		}
	}

	return time;
}

bool Timer::isStarted() {
	return _started;
}

bool Timer::isPaused() {
	return _paused && _started;
}

void Timer::draw(SDL_Renderer* renderer) {
	_text->draw(renderer);
}

void Timer::update(SDL_Renderer* renderer) {
	_time_text.str("");
	_time_text << "Timer: " << (int) (getTicks() / 1000.f);

	_text->reloadTexture(renderer, _time_text.str().c_str(), WHITE);
}

void Timer::pollEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		// Start/stop
		if (event.key.keysym.sym == SDLK_b) {
			if (isStarted()) {
				stop();
			}
			else {
				start();
			}
		}
		// Pause/unpause
		else if (event.key.keysym.sym == SDLK_p) {
			if (isPaused()) {
				unpause();
			}
			else {
				pause();
			}
		}
	}
}

void Timer::center() {
	_text->center();
}