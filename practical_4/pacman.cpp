#include "pacman.h"
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace std;
using namespace sf;

void MenuScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
}

void MenuScene::render() {
	Scene::render();
	//Renderer::queue(&text);
}

void MenuScene::load() {
	// Title text
	Font font;
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString("Almost Pacman");
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void GameScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	Scene::render();
}

void GameScene::respawn() {}

void GameScene::load() {

	// Player
	shared_ptr<Entity> player = make_shared<Player>();
	// make_shared<Player>() calls the constructor of Player with no parameters
	// make_shared<Player>(10) would call a constructor of Player with one parameters of type int
	_ents.list.push_back(player);
	player->setPosition({ 30.0f, 30.0f });

	// Ghosts
	for (int i = 0; i < 4; i++) {
		shared_ptr<Entity> ghost = make_shared<Ghost>();
		_ents.list.push_back(ghost);
		ghost->setPosition({ 50.0f * i, 50.0f * i });
	}

}