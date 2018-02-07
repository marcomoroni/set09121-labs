#include "player.h"

using namespace sf;
using namespace std;

void Player::update(float dt) {
	// Movement
	sf::Vector2f displacement = { 0.0f, 0.0f };
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		displacement.x --;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		displacement.x ++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		displacement.y --;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		displacement.y ++;
	}
	// Normalise displacement
	float l = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	if (l != 0) {
		displacement.x = displacement.x / l;
		displacement.y = displacement.y / l;
	}
	move((float)dt * displacement * _speed);

	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}