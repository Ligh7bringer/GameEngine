#include "ship.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;

bool Invader::direction = true;
float Invader::speed = 15.0f;

//ship class
Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

Ship::~Ship() = default;

//invader class
Invader::Invader() : Ship() {}

Invader::Invader(IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);
	cout << direction << endl;

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			ships[i]->move(0, 24);			
		}
	}
}

//player class
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.0f });
}

//float direction = 0.0f;
float playerSpeed = 100.0f;
void Player::Update(const float &dt) {
	Ship::Update(dt);

	//move left
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(-dt * playerSpeed, 0);
	}

	//move left
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(dt * playerSpeed, 0);
	}

	if (getPosition().x + 32.0f > gameWidth) {
		setPosition(gameWidth - 32.0f, gameHeight - 32.0f);
	} else if (getPosition().x < 0) {
		setPosition(0, gameHeight - 32.0f);
	}
}
