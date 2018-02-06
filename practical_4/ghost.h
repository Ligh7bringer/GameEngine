#pragma once 
#include <SFML\Graphics.hpp>
#include "entity.h"

class Ghost : public Entity {
private:
	float _speed;

public:
	void Update(double dt) override;
	void Render(sf::RenderWindow &window) const override;
	Ghost();
};