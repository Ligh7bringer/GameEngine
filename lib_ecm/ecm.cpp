#include "ecm.h"

Entity::Entity()
{
}

void Entity::Update(double dt) {
	for (auto &_c : _components)
		_c->Update(dt);
}

void Entity::Render()
{
	for(auto &_c : _components)
		_c->Render();
}

sf::Vector2f& Entity::getPosition()
{
	return _position;
}

void Entity::setPosition(const sf::Vector2f &pos) {
	_position = pos;
}

bool Entity::is_forDeletion() const
{
	return false;
}

float Entity::getRotation() const
{
	return 0.0f;
}

void Entity::setRotation(float _rot)
{
}

bool Entity::isAlive() const
{
	return false;
}

void Entity::setAlive(bool _value)
{
}

void Entity::setForDelete()
{
}

bool Entity::isVisible() const
{
	return false;
}

void Entity::setVisible(bool _value)
{
}

Component::Component(Entity * p)
{
	_parent = p;
}

bool Component::is_forDeletion() const
{
	return false;
}

Component::~Component()
{
}

void EntityManager::Render() {

}

void EntityManager::Update(double dt) {
	for (auto &e : list) {
		e->Update(dt);
	}
}
