#pragma once
#include "rect.h"
#include "bullet.h"
#include "sprite.h"
#include "player.h"
#include "target.h"
#include <vector>
#include <iostream>

struct points {
	std::pair<int, int> point1;
	std::pair<int, int> point2;
};

class Projectile
{
public:
	Projectile(SDL_Renderer* renderer);
	~Projectile();

	void update(SDL_Renderer* renderer, std::shared_ptr<Player> player);
	void draw(SDL_Renderer* renderer);
	void pollEvents(SDL_Event& event);
	bool win();

	int inline getScore() { return _score; }
	void inline setScore(int score) { _score = score; }

private:
	std::map<int, points> setupLocations();
	std::vector<std::shared_ptr<Target>> createTargets(SDL_Renderer* renderer);
	void createProjectile(SDL_Renderer* renderer, int w, int h, int end_x, int end_y, std::shared_ptr<Player> player);
	
	int screen_width, screen_height;
	int _mouse_x = 0, _mouse_y = 0;
	int _cooldown = 0, _score = 0, _prev_score = 0;
	bool _mouse_down = false;
	std::map<int, points> _locations;
	std::vector<std::shared_ptr<Target>> _targets;
	std::vector<std::shared_ptr<Bullet>> _bullets;

	const int BULLET_SIZE = 12;
	const int COOLDOWN_MAX = 10;

	// Target constants
};