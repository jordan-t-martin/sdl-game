#include "text.h"

Text::Text(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color, int x, int y) : _x(x), _y(y)
{
	// Create font from font path
	_font = TTF_OpenFont(font_path.c_str(), font_size);

	if (!_font) {
		std::cerr << "Failed to load font.\n";
	}

	// Load the texture
	_text_texture = loadTexture(renderer, message_text, color);
	
	// Get texture width and height and save this to text rectangle
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

Text::~Text() {
	free();
}

// Free memory from texture
void Text::free() {
	if (_text_texture != nullptr) {
		SDL_DestroyTexture(_text_texture);
		_text_texture = nullptr;
	}
}

void Text::draw(SDL_Renderer *renderer) const {
	// Update position
	_text_rect.x = _x;
	_text_rect.y = _y;

	// If texture exists, then copy texture to rectangle.
	if (_text_texture) {
		SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
	}
	
}

// Reload text with new string value
void Text::reloadTexture(SDL_Renderer* renderer, const std::string& message_text, const SDL_Color& color) {
	// Free memory from previous texture
	free();
	
	// Load the texture 
	_text_texture = loadTexture(renderer, message_text, color);
	
	// Get texture width and height and save this to text rectangle
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

SDL_Texture* Text::loadTexture(SDL_Renderer *renderer, const std::string &message_text, const SDL_Color &color) {
	// Create surface from a string message, font, and color
	auto text_surface = TTF_RenderText_Solid(_font, message_text.c_str(), color);

	if (!text_surface) {
		std::cerr << "Failed to create text surface.\n";
	}

	// Create texture from surface
	auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	if (!text_texture) {
		std::cerr << "Failed to create text texture.\n";
	}
	
	// Free surface memory
	SDL_FreeSurface(text_surface);

	return text_texture;
}

void Text::center() {
	_x = (_x - (_text_rect.w / 2));
	_y = (_y - (_text_rect.h / 2));
}