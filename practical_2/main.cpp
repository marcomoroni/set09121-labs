#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

Texture spritesheet;
std::vector<Ship *> ships;

void Reset() {
	// reset invaders movement
	Invader::direction = true;
	Invader::speed = 30.f;
	Player::speed = 160.f;
}

void Load() {
	// Load spritesheet
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet." << endl;
	}
	// Invaders
	for (int r = 0; r < invaders_rows; ++r) {
		// Note: IntRect(left, top, width, height)
		auto rect = IntRect(32 * r, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c) {
			float leftMargin = gameWidth / 2 - 32 * invaders_columns / 2;
			float topMargin = 64.f;
			Vector2f position = { leftMargin + 32.f * c + 16.f, topMargin + 32.f * r + 16.f};
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
	// Player
	auto player = new Player();
	ships.push_back(player);

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

	// Ships
	for (auto &s : ships) {
		s->Update(dt);
	}
}

void Render(RenderWindow &window) {
	for (auto &s : ships) {
		window.draw(*s);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}