#include "pacman.h"
//#include "entity.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_ai.h"
//#include "player.h"
//#include "ghost.h"
#include "levelsystem.h"

#define GHOST_COUNT 4

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
	/*Font font;
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString("Almost Pacman");
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);*/
}

void GameScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	ls::render(Renderer::getWindow()); // REMEMBER THIS
	Scene::render();
}

void GameScene::respawn() {
	
}

void GameScene::load() {

	ls::loadLevelFile("res/pacman.txt", 25.f);

	{
		auto pl = make_shared<Entity>();

		auto s = pl->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin({ 12.f, 12.f });

		pl->addComponent<PlayerMovementComponent>();

		// THIS SHOULD BE IN respawn()
		pl->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		//pl->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

		_ents.list.push_back(pl);
	}

	const sf::Color ghost_cols[]{ {208, 62, 25},		// red Blinky
							      {219, 133, 28},		// orange Clyde
								  {70, 191, 238},		// cyan inky
								  {234, 130, 229} };	// pink Pinky

	// THIS SHOULD BE IN respawn()
	auto ghost_spawns = ls::findTiles(ls::ENEMY);

	for (int i = 0; i < GHOST_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin({ 12.f, 12.f });

		ghost->addComponent<EnemyAIComponent>();

		// THIS SHOULD BE IN respawn()
		ghost->setPosition(ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
		//ghost->getCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.f);

		_ents.list.push_back(ghost);
	}

}