#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	Ship();
	bool _exploded = false;
		
public:	
	explicit Ship(sf::IntRect ir);	
	virtual ~Ship() = 0;	
	virtual void Update(const float &dt);	

	bool isExploded();
	virtual void Explode();
	
};

class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt);
	static bool direction;
	static float speed;
};

class Player : public Ship {
public:
	Player();
	void Update(const float &dt) override;
};