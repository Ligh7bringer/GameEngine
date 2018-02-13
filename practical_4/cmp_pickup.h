#pragma once
#include "ecm.h"

class PickUpComponent : public Component {
protected:
	int _points;
	std::vector <std::shared_ptr<Entity>> _entities;

public:
	PickUpComponent() = delete;
	explicit PickUpComponent(Entity *p);
	void Update(double dt) override;
	void Render() override;
	void setEntities(std::vector<std::shared_ptr<Entity>>& e);
	int getPoints() const;
	void setPoints(int pts);
};