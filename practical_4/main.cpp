#include <SFML/Graphics.hpp>
#include <iostream>
#include "pacman.h"
#include "entity.h"
#include "player.h"
#include "ghost.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

EntityManager em;

void Reset() {
	//player->setPosition({ 50.f, 50.f });
}

void Load() {
	// Player
	shared_ptr<Entity> player = make_shared<Player>();
	// make_shared<Player>() calls the constructor of Player with no parameters
	// make_shared<Player>(10) would call a constructor of Player with one parameters of type int
	em.list.push_back(player);

	// Ghosts
	for (int i = 0; i < 4; i++) {
		shared_ptr<Entity> ghost = make_shared<Ghost>();
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

	em.update(dt);
}

void Render(RenderWindow &window) {
	em.render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PACMAN");
	Renderer::initialise(window);
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}