#include "pacman.h"
#include "ecm.h"
#include <SFML/Graphics.hpp>
#include "system_renderer.h"
#include <iostream>
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "levelsystem.h"

using namespace std;
using namespace sf;

Font font;
const int GHOSTS_COUNT = 4;

//MENU SCENE
MenuScene::MenuScene() {
}

void MenuScene::Load() {
	if (!font.loadFromFile("res/fonts/TravelingTypewriter.ttf")) {
		cout << "Cannot load font!" << endl;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	text.setString("Almost Pacman");
	text.setFont(font);
}

void MenuScene::Update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}

	Scene::Update(dt);
	_ents.Update(dt);
}

void MenuScene::Render() {
	Scene::Render();
	_ents.Render();
	Renderer::queue(&text);
}

//GAME SCENE
vector<shared_ptr<Entity>> ghosts;
shared_ptr<Entity> player;
void GameScene::Respawn() {
	_ents.list[0]->setPosition(ls::findTiles(ls::START)[0]);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (int i = 1; i < _ents.list.size(); ++i) {
		_ents.list[i]->setPosition(ghost_spawns[rand() % ghost_spawns.size()]);
	}
}

void GameScene::Update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}

	for (auto &g : ghosts) {
		if (length(g->getPosition() - player->getPosition()) < 30.0f) {
			Respawn();
		}
	}

	_ents.Update(dt);
	Scene::Update(dt);
}

void GameScene::Render() {
	ls::Render(Renderer::getWindow());
	_ents.Render();	
	Scene::Render();
}

void GameScene::Load() {	
	ls::loadLevelFile("res/levels/pacman.txt", 25.0f);
	
	//text.setString("Game scene!");
	auto pl = make_shared<Entity>();
	auto mp = pl->addComponent<PlayerMovementComponent>();
	mp->setSpeed(100.0f);

	auto s = pl->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(10.0f, 10.0f);
	_ents.list.push_back(pl);
	player = pl;

	const sf::Color ghost_cols[]{
		{208, 62, 25},
		{219, 133, 28},
		{70, 191, 238},
		{234, 130, 229} };

	Vector2f pos = Vector2f{ 300.0f, 300.0f };
	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		ghost->addComponent<EnemyAIComponent>();

		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(10.0f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(10.f, 10.f));

		_ents.list.push_back(ghost);
		ghosts.push_back(ghost);
		pos += Vector2f(70.0f, 0);
	}

	Respawn();
}
