#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

Bullet::Bullet(const sf::Vector2f &pos, const bool mode) : Bullet() {	
	setPosition(pos);
	_mode = mode;
	// Set correct texture
	if (_mode) {
		setTextureRect(IntRect(32, 32, 32, 32));
	}
	else {
		setTextureRect(IntRect(64, 32, 32, 32));
	}
};

Bullet::Bullet() : Sprite() {
	setOrigin(16, 16);
	setTexture(spritesheet);
};

unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];

void Bullet::Update(const float &dt) {
	for (auto &b : bullets)
	{
		b._Update(dt);
	}
}

void Bullet::Fire(const sf::Vector2f &pos, const bool mode) {
	bullets[++bulletPointer].setPosition(pos);
	bullets[bulletPointer]._mode = mode;
	// Set correct texture
	if (mode) {
		bullets[bulletPointer].setTextureRect(IntRect(32, 32, 32, 32));
	}
	else {
		bullets[bulletPointer].setTextureRect(IntRect(64, 32, 32, 32));
	}
}

void Bullet::Render(sf::RenderWindow &window) {
	for (auto &b : bullets) {
		window.draw(b);
	}
}

void Bullet::_Update(const float &dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		// off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.f * (_mode ? 1.f : -1.f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == playerShip) {
				// player bullets don't collide with player
				continue;
			}
			if (_mode && s != playerShip) {
				// invader bullets don't collide with other invaders
				continue;
			}
			if (!s->isExploded() &&
				s->getGlobalBounds().intersects(boundingBox)) {
				// Explode the ship
				s->Explode();
				// Warp bullet off-screen
				setPosition(-100, -100);
				return;
			}
		}
	}
}