#include "cmp_pickup.h"
#include "system_renderer.h"
#include "maths.h"
#include "cmp_actor_movement.h"

PickUpComponent::PickUpComponent(Entity *p) : _points(0.0f), Component(p) {
	//std::cout << _points << std::endl;
}

void PickUpComponent::Update(double dt) {
	for (auto &e : _entities) {
		if (length(_parent->getPosition() - e->getPosition()) < 30.0f) {
			_parent->setForDelete();
			auto cp = e->GetComponent<ActorMovementComponent>();
			if (cp != nullptr) {
				cp->increaseSpeed(1.0f);
			}

			_points += 10.f;
			break;
		}
	}
}

void PickUpComponent::Render() {}

void PickUpComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}

float PickUpComponent::getPoints() const {
	return _points;
}
