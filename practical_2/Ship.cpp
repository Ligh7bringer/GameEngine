#include "ship.h"
#include "game.h"
#include "bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

bool Invader::direction = true;
float Invader::speed = 35.0f;
float playerSpeed = 100.0f;

//ship class
Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

//used when a ship is destroyed
void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	setOrigin(16, 16);
	_exploded = true;
	if (this == player) {
		gameOver = true;
	}
}

//returns whether a ship is destroyed
bool Ship::isExploded() {
	return _exploded;
}

//destructor
Ship::~Ship() = default;

//invader class
Invader::Invader() : Ship() {}

//constructor
Invader::Invader(IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	//ship movement
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	//change direction when about to go offscreen
	if (((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) && !isExploded()) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			if(ships[i] != player && !ships[i]->isExploded())
				ships[i]->move(0, 24);			
		}
	}

	//invader shooting
	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <= 0 && rand() % 100 == 0) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
	}
	
	static float explosiontime = 1.0f;

	//remove exploded ships from the screen	
	for (auto &s : ships) {
		if (s->isExploded()) {
			explosiontime -= dt;
		}
		if (explosiontime <= 0.0f) {
			s->setPosition(-100, -100);
			explosiontime = 1.0f;
		}
	}
}

//player class
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.0f });
}

//float direction = 0.0f;
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

	//player is not allowed to go offscreen
	if (getPosition().x + 32.0f > gameWidth) {
		setPosition(gameWidth - 32.0f, gameHeight - 32.0f);
	} else if (getPosition().x < 0) {
		setPosition(0, gameHeight - 32.0f);
	}

	//shoot 
	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
}
