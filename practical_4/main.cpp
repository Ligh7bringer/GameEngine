#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "ghost.h"
#include "entity.h"
#include "system_renderer.h"
#include "pacman.h"
#include "scene.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;
std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

void Load() {
    gameScene = make_shared<GameScene>();
	menuScene = make_shared<MenuScene>();
	gameScene->Load();
	menuScene->Load();
	//set start scene
	activeScene = menuScene;
}

void Update(RenderWindow &window) {
	// recalculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();

	activeScene->Update(dt);

	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow &window) {
	activeScene->Render(window);
	Renderer::render();
}

  int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PAC MAN");
	Renderer::initiliase(window);
	
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

    return 0;
  }
