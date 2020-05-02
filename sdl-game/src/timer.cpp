#include "timer.h"

Timer::Timer(SDL_Renderer* renderer) {
	//Initialize the variables
	_text = new Text(renderer, FONT_PATH, FONT_SIZE, START_TEXT, RED, X_POS, Y_POS);

	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = true;
}

void Timer::start() {
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop() {
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause() {
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused) {
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause() {
	//If the timer is running and paused
	if (mStarted && mPaused) {
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks() {
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted) {
		//If the timer is paused
		if (mPaused) {
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else {
			//Return the current time minus the start time
			time = (SDL_GetTicks() - mStartTicks);
		}
	}

	return time;
}

bool Timer::isStarted() {
	//Timer is running and paused or unpaused
	return mStarted;
}

bool Timer::isPaused() {
	//Timer is running and paused
	return mPaused && mStarted;
}

void Timer::loadMedia(SDL_Renderer* renderer, const std::string& message_text) {
	
}

void Timer::draw(SDL_Renderer* renderer) {
	_text->draw(renderer);
}

void Timer::update(SDL_Renderer* renderer) {
	//Set text to be rendered
	timeText.str("");
	timeText << "Timer: " << (int) (getTicks() / 1000.f);

	_text->reloadTexture(renderer, timeText.str().c_str(), RED);
}

void Timer::pollEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		//Start/stop
		if (event.key.keysym.sym == SDLK_b) {
			if (isStarted()) {
				stop();
			}
			else {
				start();
			}
		}
		//Pause/unpause
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
