#include "projectile.h"

Projectile::Projectile(SDL_Renderer* renderer)
{
	// Get screen dimensions for out of bounds check
	SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);

	_locations = setupLocations();
	_targets = createTargets(renderer);
}

Projectile::~Projectile() {

}

void Projectile::draw(SDL_Renderer* renderer) {
	for (size_t i = 0; i < _targets.size(); i++) 
		_targets.at(i)->draw(renderer);

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

		// Hit a target
		for (size_t j = 0; j < _targets.size(); j++) {
			std::shared_ptr<Target> t = _targets.at(j);
			if (b.get()->colliding(t.get())) {
				_bullets.erase(_bullets.begin() + i);
				t->hit(renderer);
				if (t->isDead()) {
					_targets.erase(_targets.begin() + j);
					_score += 10;
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

std::map<int, std::pair<int, int>> Projectile::setupLocations() {
	std::map<int, std::pair<int, int>> locations;
	for (int i = 0; i < 5; i++) {
		locations[i] = std::make_pair((i * 100), 200);
	}
	return locations;
}

std::vector<std::shared_ptr<Target>> Projectile::createTargets(SDL_Renderer* renderer) {
	std::vector<std::shared_ptr<Target>> targets;
	for (size_t i = 0; i < _locations.size(); i++) {
		std::shared_ptr<Target> target(new Target(renderer, 56, 56, _locations[i].first, _locations[i].second, "assets/textures/target.png"));
		targets.push_back(target);
	}
	return targets;
}