#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "text.h"

//The application time based timer
class Timer
{
public:
	//Initializes variables
	Timer(SDL_Renderer* renderer);

	void update(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	void pollEvents(SDL_Event& event);

	void loadMedia(SDL_Renderer* renderer, const std::string& message_text);

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;

	//In memory text stream
	std::stringstream timeText;

	Text* _text;

	// Constants for text
	const int X_POS = 20, Y_POS = 50;
	const std::string FONT_PATH = "assets/consolab.ttf";
	const int FONT_SIZE = 30;
	const SDL_Color RED = { 255, 0, 0 , 255 }; 
	const std::string START_TEXT = "Time: 0";

};