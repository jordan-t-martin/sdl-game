#include "projectile.h"

Projectile::Projectile(SDL_Renderer* renderer)
{
	_locations = setupLocations();
	_targets = createTargets(renderer);
}

Projectile::~Projectile() {

}

void Projectile::draw(SDL_Renderer* renderer) {
	for (int i = 0; i < _targets.size(); i++) 
		_targets.at(i)->draw(renderer);
	for (int i = 0; i < _bullets.size(); i++) {
		_bullets.at(i)->draw(renderer);
	}
}

void Projectile::update(SDL_Renderer* renderer, std::shared_ptr<Player> player) {
	if (cooldown == 0) {
		if (shoot_flag && !player->getWalking()) {
			SDL_GetMouseState(&mouse_x, &mouse_y);
			createProjectile(renderer, 12, 12, (float)mouse_x, (float)mouse_y, 5, 5, 5, player);
			cooldown = 10;
		}
	}
	else { cooldown -= 1; }

	for (int i = 0; i < _targets.size(); i++) {
		_targets.at(i)->update(renderer);
	}

	for (int i = 0; i < _bullets.size(); i++) {
		std::shared_ptr<Bullet> b = _bullets.at(i);
		b->update();
		int screen_width, screen_height;
		SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);
		if (b->getX() < 0 || b->getX() > screen_width || b->getY() < 0 || b->getY() > screen_height) {
			_bullets.erase(_bullets.begin() + i);
			continue;
		}
		for (int j = 0; j < _targets.size(); j++) {
			std::shared_ptr<Target> t = _targets.at(j);
			if (b.get()->colliding(t.get())) {
				_bullets.erase(_bullets.begin() + i);
				t->hit();
				if (t->isDead()) {
					_targets.erase(_targets.begin() + j);
					score += 10;
				}
			}
		}
	}
}

void Projectile::pollEvents(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		shoot_flag = true;
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		shoot_flag = false;
	}
	for (int i = 0; i < _targets.size(); i++) {
		_targets.at(i)->pollEvents(event);
	}
}

void Projectile::createProjectile(SDL_Renderer* renderer, int w, int h, int end_x, int end_y, int range, int speed, int distance, std::shared_ptr<Player> player) {
	int start_x = player->getX(), start_y = player->getY();

	// Choose larger difference of start and end in either x or y direction. 
	// Snap direction to the larger difference
	int diff_x = start_x - end_x;
	int diff_y = start_y - end_y;

	player->shoot(diff_x, diff_y);

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

	std::vector<std::shared_ptr<Sprite>> sprites;
	std::shared_ptr<Sprite> sprite(new Sprite(8, 12, "assets/sprite-sheets/bullet.png"));
	sprites.push_back(sprite);
	std::shared_ptr<Bullet> b(new Bullet(renderer, w, h, start_x, start_y, end_x, end_y, range, speed, distance, sprites));
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
	for (int i = 0; i < _locations.size(); i++) {
		std::shared_ptr<Target> target(new Target(renderer, 56, 56, _locations[i].first, _locations[i].second, "assets/textures/target.png"));
		targets.push_back(target);
	}
	return targets;
}