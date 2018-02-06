#include "ghost.h"
#include <stdlib.h>

using namespace std;
using namespace sf;

void Ghost::Update(double dt)
{
	int xdir = rand() % 2 - 1;
	int ydir = rand() % 2 - 1;
	float speed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));
	move(Vector2f{ static_cast<float>(speed * dt * xdir), static_cast<float>(speed * dt * ydir) });
	Entity::Update(dt);
}

void Ghost::Render(sf::RenderWindow & window) const
{
	window.draw(*_shape);
}

Ghost::Ghost() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f))
{
	_shape->setFillColor(Color::Red);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
	_position = Vector2f{ 120.0f, 90.0f };
}
