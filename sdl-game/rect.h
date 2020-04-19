#pragma once

#include <SDL_image.h>
#include <string>

class Rect {
public:
	Rect(SDL_Renderer *renderer, int w, int h, int x, int y, int r, int g, int b, int a);
	Rect(SDL_Renderer *renderer, int w, int h, int x, int y, const std::string &image_path);
	~Rect();
	int getW();
	int getH();
	int getX();
	int getY();
	void setW(int w);
	void setH(int h);
	void setX(int x);
	void setY(int y);
	virtual void draw(SDL_Renderer* renderer) const;
	bool colliding(Rect* a);
	void pollEvents(SDL_Event& event);

protected:
	int _w, _h;
	int _x, _y;
	int _r, _g, _b, _a;
	SDL_Texture* _texture = nullptr;
};