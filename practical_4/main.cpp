#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;

EntityManager em;

void Reset() {
	//player->setPosition({ 50.f, 50.f });
}

void Load() {
	// Player
	shared_ptr<Entity> player = make_shared<Entity>(Player());
	em.list.push_back(player);

	// Ghosts
	for (int i = 0; i < 4; i++) {
		shared_ptr<Entity> ghost = make_shared<Entity>(Ghost());
		em.list.push_back(ghost);
	}

	Reset();
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	/*for (auto &e : entities) {
		e->update(dt);
	}*/
}

void Render(RenderWindow &window) {
	/*for (auto &e : entities) {
		e->render(window);
	}*/
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "TILE ENGINE");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}