#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void Load() {
}

void Update(RenderWindow &window) {
}

void Render(RenderWindow &window) {
}

int main() {
	RenderWindow window(VideoMode(200, 200), "SPACE INVADERS");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}