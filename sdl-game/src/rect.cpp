#include "rect.h"
#include "window.h"
#include <iostream>

Rect::Rect(SDL_Renderer *renderer, int w, int h, int x, int y, int r, int g, int b, int a) :
	_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{

}

Rect::Rect(SDL_Renderer *renderer, int w, int h, int x, int y, const std::string& image_path) :
	_w(w), _h(h), _x(x), _y(y)
{
	// Create surface from image using file path
	auto surface = IMG_Load(image_path.c_str());
	
	// Check if surface was created successfully
	if (!surface) {
		std::cerr << "Failed to create surface.\n";
	}

	// Create texture from surface
	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	// Check if texture was created successfully
	if (!_texture) {
		std::cerr << "Failed to create texture.\n";
	}
	
	// Free surface memory
	SDL_FreeSurface(surface); 
}

Rect::~Rect() {
	if(_texture != NULL)
		SDL_DestroyTexture(_texture);
}

int Rect::getW() { return _w;}
int Rect::getH() { return _h; }
int Rect::getX() { return _x; }
int Rect::getY() { return _y; }
void Rect::setW(int w) { _w = w; }
void Rect::setH(int h) { _h = h; }
void Rect::setX(int x) { _x = x; }
void Rect::setY(int y) { _y = y; }

void Rect::draw(SDL_Renderer *renderer) const {
	// Create rectangle using position and dimensions
	SDL_Rect rect = { _x, _y, _w, _h };

	// If texture exists, then copy texture to rectangle. 
	if (_texture) {
		SDL_RenderCopy(renderer, _texture, nullptr, &rect);
	}
	// Else, use color to draw rectangle.
	else {
		SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);
		SDL_RenderFillRect(renderer, &rect);
	}
}

bool Rect::colliding(Rect* a) {
	// No collision
	if (a->_x + a->_w < this->_x || a->_x > this->_x + this->_w ||
		a->_y + a->_h < this->_y || a->_y > this->_y + this->_h) {
		return false;
	}
	else
		return true;
}

void Rect::pollEvents(SDL_Event &event) {

}