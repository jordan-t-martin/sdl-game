#pragma once
#include "rect.h"
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Window {
public:
	Window(const std::string& title, int width, int height);
	~Window();

	void update(std::shared_ptr<Rect> cursor);
	void pollEvents(SDL_Event& event, bool& quit);
	void clear() const;

	inline bool isClosed() const { return _closed; }

	static SDL_Renderer* renderer;

private:
	bool init();

	std::string _title;
	int _width = 800;
	int _height = 600;
	int _mouse_x, _mouse_y = 0;
	bool _closed = false;
	SDL_Window* _window = nullptr;
	
};