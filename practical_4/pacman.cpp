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

shared_ptr<Entity> player;
vector<shared_ptr<Entity>> ghosts;

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
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	//player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(ls::getTilePosition(ghost_spawns[rand() % GHOST_COUNT]));
		//g->getCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.f);
	}
}

void GameScene::load() {

	ls::loadLevelFile("res/pacman.txt", 25.f);

	{
		player = make_shared<Entity>();

		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin({ 12.f, 12.f });

		player->addComponent<PlayerMovementComponent>();

		_ents.list.push_back(player);
	}

	const sf::Color ghost_cols[]{ {208, 62, 25},		// red Blinky
							      {219, 133, 28},		// orange Clyde
								  {70, 191, 238},		// cyan inky
								  {234, 130, 229} };	// pink Pinky

	for (int i = 0; i < GHOST_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin({ 12.f, 12.f });

		ghost->addComponent<EnemyAIComponent>();
		
		_ents.list.push_back(ghost);
		ghosts.push_back(ghost);
	}

	respawn();

}