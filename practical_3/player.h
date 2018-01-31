#pragma once
#include "entity.h"

class Player : public Entity {
private:
	float _speed;

public:
	void Update(double dt) override;
	Player();
	void Render(sf::RenderWindow &window) const override;
	bool validMove(sf::Vector2f pos);
};
