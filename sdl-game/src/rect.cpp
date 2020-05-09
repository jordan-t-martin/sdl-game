#include "rect.h"

// Color texture
Rect::Rect(SDL_Renderer *renderer, int w, int h, int x, int y, int r, int g, int b, int a) :
	_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{

}

// Image texture
Rect::Rect(SDL_Renderer *renderer, int w, int h, int x, int y, const std::string& image_path) :
	_w(w), _h(h), _x(x), _y(y), _r(0), _g(0), _b(0), _a(0)
{
	// Create surface from image using file path
	auto surface = IMG_Load(image_path.c_str());
	
	if (!surface) {
		std::cerr << "Failed to create surface.\n";
	}

	// Create texture from surface
	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	if (!_texture) {
		std::cerr << "Failed to create texture.\n";
	}
	
	// Free memory
	SDL_FreeSurface(surface); 
}

Rect::~Rect() {
	if(_texture != NULL)
		SDL_DestroyTexture(_texture);
}

void Rect::draw(SDL_Renderer *renderer) const {
	// New rect with updated position
	SDL_Rect rect = { _x, _y, _w, _h };

	// Texture render
	if (_texture) {
		SDL_RenderCopy(renderer, _texture, nullptr, &rect);
	}
	// Color render
	else {
		SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);
		SDL_RenderFillRect(renderer, &rect);
	}
}

bool Rect::colliding(Rect* r) {
	// No collision
	if (r->_x + r->_w < this->_x || // [r] left of [this]
		r->_x > this->_x + this->_w || // [r] right of [this]
		r->_y + r->_h < this->_y || // [r] above [this] 
		r->_y > this->_y + this->_h) // [r] below [this]
		return false;

	// Collision
	return true;
}