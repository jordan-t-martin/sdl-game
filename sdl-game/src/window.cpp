#include "window.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Renderer *Window::renderer = nullptr;

Window::Window(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	// If window initialized -> window not closed
	// If window failed to initialize -> window closed
	_closed = !init();
}

Window::~Window() {
	// Destroy renderer, window, SDL Image, SDL Text, SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Window::init() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialize SDL.\n";
		return false;
	}

	// Initialize SDL Image
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "Failed to initialize SDL_image.\n";
		return false;
	}

	// Initialize SDL Text
	if (TTF_Init() == -1) {
		std::cerr << "Failed to initialize SDL_ttf.\n";
		return false;
	}

	// Create Window
	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width,
		_height,
		SDL_WINDOW_RESIZABLE
	);

	// Check window was created.
	if (_window == nullptr) {
		std::cerr << "Failed to create window.\n";
		return false;
	}

	// Create renderer using window
	// -1 means use first flag
	// PRESENTVSYNC handles frame rate cap
	renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	// Check renderer was created
	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer.\n";
		return false;
	}
	
	// Disable the original cursor
	SDL_ShowCursor(SDL_DISABLE);

	// Intialization complete
	return true;
}

void Window::update(std::shared_ptr<Rect> cursor) {
	// Cursor Image
	// Get x/y coordinate of mouse
	SDL_GetMouseState(&_mouse_x, &_mouse_y);
	
	// Adjust for center of rectangle
	cursor->setX(_mouse_x - (cursor->getW() / 2));
	cursor->setY(_mouse_y- (cursor->getH() / 2));
}

void Window::pollEvents(SDL_Event &event) {
	switch (event.type) {
	// 'X' button in window to quit.
	case SDL_QUIT:
		_closed = true;
		break;

	default:
		break;
	}
}

// Update the screen every frame
void Window::clear() const {
	// Update renderer
	SDL_RenderPresent(renderer);
	// Set color white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); 
	// Redraw screen with set color
	SDL_RenderClear(renderer); 
}