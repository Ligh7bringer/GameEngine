#include "entity.h"

using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position; }

void Entity::setPosition(const Vector2f &pos) { _position = pos; }

void Entity::move(const Vector2f &pos) { _position += pos; }

void Entity::Update(const double dt) {
	_shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

void EntityManager::Update(double dt)
{
	for (auto &_e : list) {
		_e->Update(dt);
	}
}

void EntityManager::Render(sf::RenderWindow & window)
{
	for (auto &_e : list) {
		_e->Render(window);
	}
}
