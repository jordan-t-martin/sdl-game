#include "projectile.h"

Projectile::Projectile(SDL_Renderer* renderer)
{
	// Get screen dimensions for out of bounds check
	SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);

	_target_locations = setupTargetLocations();
	_obst_locations = setupObstLocations();

	_targets = createTargets(renderer);
	_obstacles = createObstacles(renderer);
}

Projectile::~Projectile() {

}

void Projectile::draw(SDL_Renderer* renderer) {
	for (size_t i = 0; i < _targets.size(); i++) 
		_targets.at(i)->draw(renderer);

	for (size_t i = 0; i < _obstacles.size(); i++)
		_obstacles.at(i)->draw(renderer);

	for (size_t i = 0; i < _bullets.size(); i++) {
		_bullets.at(i)->draw(renderer);
	}
}

// Runs every tick
void Projectile::update(SDL_Renderer* renderer, std::shared_ptr<Player> player) {
	// Shoot if you can
	if (_cooldown == 0) {
		if (_mouse_down && !player->getWalking()) {
			SDL_GetMouseState(&_mouse_x, &_mouse_y);
			createProjectile(renderer, BULLET_SIZE, BULLET_SIZE, _mouse_x, _mouse_y, player);
			_cooldown = COOLDOWN_MAX;
		}
	}
	else { _cooldown -= 1; }

	// Update all bullets and targets
	for (size_t i = 0; i < _targets.size(); i++) {
		_targets.at(i)->update();
	}

	for (size_t i = 0; i < _bullets.size(); i++) {
		_bullets.at(i)->update();
	}

	// Check collisions for bullets
	for (size_t i = 0; i < _bullets.size(); i++) {
		std::shared_ptr<Bullet> b = _bullets.at(i);

		// Out of bounds
		if (b->getX() < 0 || b->getX() > screen_width || b->getY() < 0 || b->getY() > screen_height) {
			_bullets.erase(_bullets.begin() + i);
			continue;
		}

		// Hit an obstacle
		for (size_t j = 0; j < _obstacles.size(); j++) {
			std::shared_ptr<Rect> o = _obstacles.at(j);
			if (b.get()->colliding(o.get())) {
				_bullets.erase(_bullets.begin() + i);
				b = nullptr;
				break;
			}
		}

		// Hit a target
		if (b != nullptr) {
			for (size_t j = 0; j < _targets.size(); j++) {
				std::shared_ptr<Target> t = _targets.at(j);
				if (b.get()->colliding(t.get())) {
					_bullets.erase(_bullets.begin() + i);
					t->hit(renderer);
					if (t->isDead()) {
						_targets.erase(_targets.begin() + j);
						_score += 10;
					}
					break;
				}
			}
		}
	}
}

bool Projectile::win() {
	return (_targets.size() == 0);
}

void Projectile::pollEvents(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		_mouse_down = true;
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		_mouse_down = false;
	}
}

void Projectile::createProjectile(SDL_Renderer* renderer, int w, int h, int end_x, int end_y, std::shared_ptr<Player> player) {
	int start_x = player->getX(), start_y = player->getY();

	// Handle player variables for shot
	int diff_x = start_x - end_x;
	int diff_y = start_y - end_y;
	player->shoot(diff_x, diff_y);

	// Figure out where to start bullet relative to player position and direction
	if (player->getDir() == Player::left) {
		start_y += player->getH() / 2;
	}
	else if (player->getDir() == Player::right) {
		start_x += player->getW();
		start_y += player->getH() / 2;
	}
	else if (player->getDir() == Player::up) {
		start_x += player->getW() / 2;
	}
	else if (player->getDir() == Player::down) {
		start_x += player->getW() / 2;
		start_y += player->getH();
	}

	// Create the bullet
	std::shared_ptr<Bullet> b(new Bullet(renderer, w, h, (float) start_x, (float) start_y, (float) end_x, (float) end_y, 0, 0, 0, 0));
	_bullets.push_back(b);
}

std::map<int, points> Projectile::setupTargetLocations() {
	std::map<int, points> locations;
	points p;

	p.point1 = std::make_pair(0, 30);
	p.point2 = std::make_pair(700, 30);
	locations[0] = p;

	p.point1 = std::make_pair(0, 100);
	p.point2 = std::make_pair(0, 200);
	locations[1] = p;

	p.point1 = std::make_pair(100, 100);
	p.point2 = std::make_pair(100, 200);
	locations[2] = p;

	p.point1 = std::make_pair(200, 130);
	p.point2 = std::make_pair(570, 130);
	locations[3] = p;

	p.point1 = std::make_pair(200, 230);
	p.point2 = std::make_pair(570, 230);
	locations[4] = p;

	p.point1 = std::make_pair(650, 100);
	p.point2 = std::make_pair(650, 200);
	locations[5] = p;

	p.point1 = std::make_pair(750, 100);
	p.point2 = std::make_pair(750, 200);
	locations[6] = p;
	return locations;
}

std::map<int, std::pair<int, int>> Projectile::setupObstLocations() {
	std::map<int, std::pair<int, int> > locations;
	locations[0] = std::make_pair(50, 300);
	locations[1] = std::make_pair(375, 350);
	locations[2] = std::make_pair(550, 300);
	locations[3] = std::make_pair(200, 350);
	locations[4] = std::make_pair(700, 325);
	return locations;
}

std::vector<std::shared_ptr<Target>> Projectile::createTargets(SDL_Renderer* renderer) {
	std::vector<std::shared_ptr<Target>> targets;
	for (size_t i = 0; i < _target_locations.size(); i++) {
		std::shared_ptr<Target> target(new Target(renderer, 56, 56, _target_locations[i].point1.first, _target_locations[i].point1.second, _target_locations[i].point2.first, _target_locations[i].point2.second, "assets/textures/target.png"));
		targets.push_back(target);
	}
	return targets;
}

std::vector<std::shared_ptr<Rect>> Projectile::createObstacles(SDL_Renderer* renderer) {
	std::vector<std::shared_ptr<Rect>> obstacles;
	for (size_t i = 0; i < _obst_locations.size(); i++) {
		std::shared_ptr<Rect> obstacle(new Rect(renderer, 90, 63, _obst_locations[i].first, _obst_locations[i].second, "assets/textures/rock.png"));
		obstacles.push_back(obstacle);
	}
	return obstacles;
}