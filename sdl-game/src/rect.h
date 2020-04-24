#pragma once

#include <SDL_image.h>
#include <string>

class Rect {
public:
	Rect(SDL_Renderer *renderer, int w, int h, int x, int y, int r, int g, int b, int a);
	Rect(SDL_Renderer *renderer, int w, int h, int x, int y, const std::string &image_path);
	~Rect();

	virtual void draw(SDL_Renderer* renderer) const;
	bool colliding(Rect* a);
	void pollEvents(SDL_Event& event);

	int inline getW() { return _w; }
	int inline getH() { return _h; }
	int inline getX() { return _x; }
	int inline getY() { return _y; }

	void inline setW(int w) { _w = w; }
	void inline setH(int h) { _h = h; }
	void inline setX(int x) { _x = x; }
	void inline setY(int y) { _y = y; }


protected:
	int _w, _h;
	int _x, _y;
	int _r, _g, _b, _a;
	SDL_Texture* _texture = nullptr;
};