#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,	// Player1 Up
	Keyboard::Z,	// Player1 Down
	Keyboard::Up,	// Player2 Up
	Keyboard::Down	// Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

void Load() {
	// Set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3.f, 3.f));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	// reset paddle position
	paddles[0].setPosition(Vector2f(gameWidth / 2 - 370.f, gameHeight / 2));
	paddles[1].setPosition(Vector2f(gameWidth / 2 + 370.f, gameHeight / 2));
	// reset ball position
	ball.setPosition(Vector2f(gameWidth / 2 - ballRadius / 2, gameHeight / 2 - ballRadius / 2));
	// ball velocity
	ballVelocity = { server ? 100.f : -100.f, 60.f };
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

	// Handle paddle movement
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	paddles[0].move(0, direction * paddleSpeed * dt);

	// move ball
	ball.move(ballVelocity * dt);
}

void Render(RenderWindow &window) {
	//Draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}