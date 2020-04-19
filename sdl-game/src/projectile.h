#pragma once
#include "rect.h"
#include "bullet.h"
#include "sprite.h"
#include "player.h"
#include "target.h"
#include <vector>
#include <iostream>

class Projectile
{
public:
	Projectile(SDL_Renderer* renderer);
	~Projectile();

	void update(SDL_Renderer* renderer, std::vector<std::shared_ptr<Target>> &targets);
	void processInput(SDL_Renderer* renderer, std::shared_ptr<Player> player);
	void createProjectile(SDL_Renderer* renderer, int w, int h, int end_x, int end_y, int range, int speed, int distance, std::shared_ptr<Player> player);
	void pollEvents(SDL_Event& event);
	std::vector<std::shared_ptr<Bullet>> _bullets;

	int mouse_x = 0, mouse_y = 0;
	int cooldown = 0;
	bool shoot_flag = false;
	int score;
};