#pragma once
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Text {
public:
	Text(SDL_Renderer* renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color, int x, int y);
	~Text();

	void free();
	void draw(SDL_Renderer* renderer) const;
	void reloadTexture(SDL_Renderer* renderer, const std::string& message_text, const SDL_Color& color);
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string &message_text, const SDL_Color &color);
	void center();

	int inline getX() { return _x; }
	int inline getY() { return _y; }
	int inline getW() { return _text_rect.w; }
	int inline getH() { return _text_rect.h; }
	void inline setX(int x) { _x = x; }
	void inline setY(int y) { _y = y; }

private:
	int _x, _y;
	TTF_Font* _font;
	SDL_Texture *_text_texture = nullptr;
	mutable SDL_Rect _text_rect;
};
