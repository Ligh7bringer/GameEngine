#include "pacman.h"
#include "ecm.h"
#include <SFML/Graphics.hpp>
#include "system_renderer.h"
#include <iostream>
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"

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
void GameScene::Respawn() {
}

void GameScene::Update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::Update(dt);
	_ents.Update(dt);
}

void GameScene::Render() {
	Scene::Render();
	_ents.Render();
}

void GameScene::Load() {	
	//text.setString("Game scene!");
	auto pl = make_shared<Entity>();
	auto mp = pl->addComponent<PlayerMovementComponent>();
	mp->setSpeed(200.0f);

	auto s = pl->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(12.0f);
	s->getShape().setFillColor(Color::Yellow);
	_ents.list.push_back(pl);

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
		s->setShape<sf::CircleShape>(12.0f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(ghost);
		pos += Vector2f(70.0f, 0);
	}
}
