#include "cmp_enemy_ai.h"

using namespace sf;
using namespace std;

EnemyAIComponent::EnemyAIComponent(Entity* p)
	: ActorMovementComponent(p) {}

void EnemyAIComponent::update(float dt) {

	// Movement
	sf::Vector2f displacement = { 0.0f, 0.0f };
	/*if (Keyboard::isKeyPressed(Keyboard::Left)) {
		displacement.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		displacement.x++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		displacement.y--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		displacement.y++;
	}*/
	displacement.x = rand() % 2 + 0 - 1;
	displacement.y = rand() % 2 + 0 - 1;
	//displacement.x++;
	// Normalise displacement
	float l = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	if (l != 0) {
		displacement.x = displacement.x / l;
		displacement.y = displacement.y / l;
	}

	//move((float)dt * displacement * _speed);

}