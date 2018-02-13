#include "cmp_pickup.h"
#include "system_renderer.h"
#include "maths.h"
#include "cmp_actor_movement.h"

PickUpComponent::PickUpComponent(Entity *p) : _points(20), Component(p) {}

void PickUpComponent::Update(double dt) {
	for (auto e : _entities) {
		if (length(_parent->getPosition() - e->getPosition()) < 30.0f) {
			e->setPoints(_points);

			_parent->setForDelete();

			auto cp = e->GetComponent<ActorMovementComponent>();
			if (cp != nullptr) {
				cp->increaseSpeed(1.0f);
			}

			break;
		}
	}
}

void PickUpComponent::Render() {}

void PickUpComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}

int PickUpComponent::getPoints() const {
	return _points;
}

void PickUpComponent::setPoints(int pts) {
	_points = pts;
}