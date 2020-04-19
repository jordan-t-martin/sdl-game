#pragma once

#include <SDL_ttf.h>
#include <string>

class Text {
public:
	Text(SDL_Renderer* renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);

	void display(int x, int y, SDL_Renderer* renderer) const;
	void reloadTexture(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);
	static SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);

private:
	SDL_Texture *_text_texture = nullptr;
	mutable SDL_Rect _text_rect;
};
