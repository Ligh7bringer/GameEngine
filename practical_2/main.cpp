#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader;
vector<Ship *> ships;
Player *player;

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << endl;
	}
	
	float x = 16.0f;
	float y = 16.0f;

	for (int i = 0; i < invaders_rows; ++i) {
		auto rect = new IntRect(0, 0, 32, 32);
		for (int j = 0; j < invaders_columns; ++j) {
			auto pos = Vector2f{ x, y };
			Invader *inv = new Invader(*rect, pos);
			ships.push_back(inv);
			x += 36.0f;
		}
		y += 36.0f;
		x = 16.0f;
	}

	player = new Player();
	ships.push_back(player);
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

	//close the window when escape is pressed
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	//update ships
	for (auto &s : ships) {
		s->Update(dt);
	}

	Bullet::Update(dt);
}

void Render(RenderWindow &window) {
	for (const auto s : ships) {
		window.draw(*s);
	}

	Bullet::Render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");

	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

    return 0;
  }