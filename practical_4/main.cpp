#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "ghost.h"
#include "entity.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;
EntityManager em;

void Load() {
	auto player = make_shared<Player>();
	em.list.push_back(player);

	Vector2f pos = Vector2f{ 300.0f, 300.0f };
	for (int i = 0; i < 4; ++i) {
		auto ghost = make_shared<Ghost>();
		ghost->setPosition(pos);
		em.list.push_back(ghost);
		pos += Vector2f(70.0f, 0);
	}
}

void Update(RenderWindow &window) {
	// recalculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
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

	em.Update(dt);
}

void Render(RenderWindow &window) {
	em.Render(window);
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
