#include "pacman.h"
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace std;
using namespace sf;

void MenuScene::update(float dt) {
	_ents.update(dt);
}

void MenuScene::render() {
	_ents.render(Renderer::getWindow());
}

void MenuScene::load() {
	
}

void GameScene::update(float dt) {
	_ents.update(dt);
}

void GameScene::render() {
	_ents.render(Renderer::getWindow());
}

void GameScene::respawn() {}

void GameScene::load() {

	// Player
	shared_ptr<Entity> player = make_shared<Player>();
	// make_shared<Player>() calls the constructor of Player with no parameters
	// make_shared<Player>(10) would call a constructor of Player with one parameters of type int
	_ents.list.push_back(player);

	// Ghosts
	for (int i = 0; i < 4; i++) {
		shared_ptr<Entity> ghost = make_shared<Ghost>();
		_ents.list.push_back(ghost);
	}

}