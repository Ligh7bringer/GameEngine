#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

//some variables
Texture spritesheet;
Sprite invader;
vector<Ship *> ships;
Player *player;
bool gameOver;
Font font;
Text text;

void Reset() {
	gameOver = false;
	ships.clear();
	Bullet::Reset();

	//create ships
	float x = 16.0f;
	float y = 16.0f;
	int spriteCoord = 0;

	for (int i = 0; i < invaders_rows; ++i) {
		auto rect = new IntRect(spriteCoord, 0, 32, 32);
		for (int j = 0; j < invaders_columns; ++j) {
			auto pos = Vector2f{ x, y };
			Invader *inv = new Invader(*rect, pos);
			ships.push_back(inv);
			x += 50.0f;
		}
		y += 32.0f;
		x = 16.0f;
		spriteCoord += 32;
	}

	//create player
	player = new Player();
	ships.push_back(player);
}

void Load() {
	//load spritesheet
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << endl;
	}

	//load font
	if (!font.loadFromFile("res/fonts/TravelingTypewriter.ttf")) {
		cout << "Couldn't load font!" << endl;
	}

	//prepare game over text
	text.setFont(font);
	text.setCharacterSize(24);
	text.setColor(Color::White);
	text.setString("Game over! Press Enter to restart.");
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), (gameHeight * 0.5f) - (text.getLocalBounds().height * 0.5f));
}

void Update(RenderWindow &window) {
	// recalculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	float fps = 1.0f / dt;
	//cout << to_string(fps) << endl;
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

	//update bullets
	Bullet::Update(dt);

	//start a new game
	if (gameOver && Keyboard::isKeyPressed(Keyboard::Return)) {
		Reset();
	}
}

void Render(RenderWindow &window) {
	for (const auto s : ships) {
		window.draw(*s);
	}

	Bullet::Render(window);

	static float gameovertime = 1.0f;
	//display game over screen
	if (gameOver) {
		window.clear();
		window.draw(text);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");

	//prepare everything needed
	Load();
	Reset();

	//main game loop
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

    return 0;
  }