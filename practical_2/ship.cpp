#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

// Define the ship deconstructor
// Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);
	// Move left of right
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	// Drop and reverse
	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			ships[i]->move(0, 24);
		}
	}
}

// Remember: Any decelared STATIC variable must be defined somewhere
// Then, these variables can be accessed anywhere with `invader::speed = 20.f`
bool Invader::direction;
float Invader::speed;