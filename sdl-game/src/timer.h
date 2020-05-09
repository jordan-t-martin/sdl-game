#pragma once
#include <sstream>
#include "text.h"

class Timer
{
public:
	Timer(SDL_Renderer* renderer);

	void update(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	void pollEvents(SDL_Event& event);

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

	void center();

	void inline setX(int x) { _x = x; _text->setX(_x); }
	void inline setY(int y) { _y = y; _text->setY(_y); }

private:
	//The clock time when the timer started
	Uint32 _start_ticks;

	//The ticks stored when the timer was paused
	Uint32 _paused_ticks;

	int _x = 20, _y = 50;
	bool _paused;
	bool _started;
	std::stringstream _time_text;
	Text* _text;

	// Constants for text
	const std::string FONT_PATH = "assets/consolab.ttf";
	const int FONT_SIZE = 30;
	const SDL_Color WHITE = { 255, 255, 255 , 255 };
	const std::string START_TEXT = "Time: 0";

};