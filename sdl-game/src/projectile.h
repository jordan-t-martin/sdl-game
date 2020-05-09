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
	std::map<int, points> setupTargetLocations();
	std::map<int, std::pair<int, int>> setupObstLocations();
	std::vector<std::shared_ptr<Target>> createTargets(SDL_Renderer* renderer);
	std::vector<std::shared_ptr<Rect>> createObstacles(SDL_Renderer* renderer);
	void createProjectile(SDL_Renderer* renderer, int w, int h, int end_x, int end_y, std::shared_ptr<Player> player);
	
	int screen_width, screen_height;
	int _mouse_x = 0, _mouse_y = 0;
	int _cooldown = 0, _score = 0, _prev_score = 0;
	bool _mouse_down = false;
	std::map<int, points> _target_locations;
	std::map<int, std::pair<int, int>> _obst_locations;
	std::vector<std::shared_ptr<Target>> _targets;
	std::vector<std::shared_ptr<Rect>> _obstacles;
	std::vector<std::shared_ptr<Bullet>> _bullets;

	// Constants for object creation
	const int BULLET_SIZE = 12;
	const int TARGET_SIZE = 56;
	const int ROCK_W = 45;
	const int ROCK_H = 32;
	const int COOLDOWN_MAX = 10;
	const std::string TARGET_FILE_PATH = "assets/textures/target.png";
	const std::string ROCK_FILE_PATH = "assets/textures/rock.png";
};