#include "player.h"

using namespace sf;
using namespace std;

void Player::Update(double dt) {
	//move in 4 directions
	int xdir = 0, ydir = 0;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		move(Vector2f(0, -_speed * dt));		
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		move(Vector2f(0, _speed * dt));		
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f(-_speed * dt, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f(_speed * dt, 0));
	}

	Entity::Update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
	_position = Vector2f{ 50.0f, 50.0f };
}

void Player::Render(RenderWindow &window) const {
	window.draw(*_shape);
}
