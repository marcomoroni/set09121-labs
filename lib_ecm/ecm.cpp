#include "ecm.h"

using namespace std;
using namespace sf;

Entity::Entity() {}

const sf::Vector2f & Entity::getPosition() const {
	return _position;
}

void Entity::setPosition(const Vector2f &pos) { _position = pos; }

void Entity::update(const float dt) {}

void Entity::render() {}

Component::Component(Entity * const p) : _parent(p) {}
