#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

Bullet::Bullet(const sf::Vector2f &pos, const bool mode) : Sprite() {
	setOrigin(16, 16);
	setPosition(pos);
	_mode = mode;
};

Bullet::Bullet() : Sprite() {
};

void Bullet::Update(const float &dt) {
	move(0, dt * 200.f * (_mode ? 1.f : -1.f));
}