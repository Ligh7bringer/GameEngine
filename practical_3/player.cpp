#include "player.h"
#include "levelsystem.h"

using namespace sf;
using namespace std;

void Player::Update(double dt) {
	//move in 4 directions
	int xdir = 0, ydir = 0;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (validMove(_position + Vector2f(0, -_speed * dt - 25.0f))) 
			move(Vector2f(0, -_speed * dt));		
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		if (validMove(_position + Vector2f(0, _speed * dt + 25.0f))) 
			move(Vector2f(0, _speed * dt));		
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (validMove(_position + Vector2f(-_speed * dt - 25.0f, 0)))
			move(Vector2f(-_speed * dt, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (validMove(_position + Vector2f(-_speed * dt + 25.0f, 0)))
			move(Vector2f(_speed * dt, 0));
	}

	Entity::Update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
	_position = ls::getTilePosition({ 1, 1 });
	_position.x += 50.0f;
	_position.y += 50.0f;
}

void Player::Render(RenderWindow &window) const {
	window.draw(*_shape);
}

bool Player::validMove(sf::Vector2f pos)
{
	return (ls::getTileAt(pos) != ls::WALL);
}