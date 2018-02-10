#include "cmp_pickup.h"
#include "system_renderer.h"
#include "maths.h"

PickUpComponent::PickUpComponent(Entity *p) : Component(p) {}

void PickUpComponent::Update(double dt) {
	for (auto &e : _entities) {
		if (length(_parent->getPosition() - e->getPosition()) < 30.0f) {
			_parent->setForDelete();
			auto cp = e->getComponents()[0];
			break;
		}
	}
}

void PickUpComponent::Render() {}

void PickUpComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}

