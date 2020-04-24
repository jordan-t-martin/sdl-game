#include "rect.h"
#include <iostream>

// Constructor for color texture
Rect::Rect(SDL_Renderer *renderer, int w, int h, int x, int y, int r, int g, int b, int a) :
	_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{

}

// Constructor for image texture
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
	// Destroy texture
	if(_texture != NULL)
		SDL_DestroyTexture(_texture);
}

// Render updates to the screen every tick
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

// Check if another rectangle is colliding with this one
bool Rect::colliding(Rect* r) {
	// No collision.
	if (r->_x + r->_w < this->_x || // [r] left of [this]
		r->_x > this->_x + this->_w || // [r] right of [this]
		r->_y + r->_h < this->_y || // [r] above [this] 
		r->_y > this->_y + this->_h) // [r] below [this]
		return false;

	// Collision!
	return true;
}

// Check if an event has occurred every tick
void Rect::pollEvents(SDL_Event &event) {

}