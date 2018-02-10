#pragma once
#include "ecm.h"

class ActorMovementComponent : public Component {
protected:
	bool validMove(const sf::Vector2f&);
	float _speed;

public:
	explicit ActorMovementComponent(Entity *p);
	ActorMovementComponent() = delete;

	float getSpeed() const;
	void setSpeed(float speed);

	void move(const sf::Vector2f&);
	void move(float x, float y);

	void Render() override;
	void Update(double dt) override;
};


class PlayerMovementComponent : public ActorMovementComponent {
public:
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity *p);

	void Update(double dt) override;
	void Render() override;

};

class EnemyAIComponent : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	enum STATE {DEADEND, ROAMING, ROTATING, ROTATED};
	STATE _state;

public:
	EnemyAIComponent() = delete;
	explicit EnemyAIComponent(Entity *p);

	void Update(double dt) override;
	void Render() override;
};