#include "pacman.h"
#include "player.h"
#include "ghost.h"
#include <SFML/Graphics.hpp>
#include "system_renderer.h"
#include <iostream>

using namespace std;
using namespace sf;

Font font;

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

void MenuScene::Render(sf::RenderWindow &window) {
	Scene::Render(window);
	_ents.Render(window);
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

void GameScene::Render(sf::RenderWindow &window) {
	Scene::Render(window);
	_ents.Render(window);
}

void GameScene::Load() {	
	//text.setString("Game scene!");
	auto player = make_shared<Player>();
	_ents.list.push_back(player);

	Vector2f pos = Vector2f{ 300.0f, 300.0f };
	for (int i = 0; i < 4; ++i) {
		auto ghost = make_shared<Ghost>();
		ghost->setPosition(pos);
		_ents.list.push_back(ghost);
		pos += Vector2f(70.0f, 0);
	}
}
