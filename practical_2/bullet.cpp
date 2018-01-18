#include "bullet.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer = '0';
Bullet Bullet::bullets[256];

Bullet::Bullet() {}

Bullet::Bullet(const sf::Vector2f &pos, const bool mode) {
	setPosition(pos);
	_mode = mode;
	setTexture(spritesheet);

	if (_mode)
		setTextureRect(IntRect(32, 32, 32, 32));
	else
		setTextureRect(IntRect(72, 32, 32, 32));
}

void Bullet::Update(const float &dt) {
	for (auto &b : bullets) {
		if (b._mode) {
			b.move({ 0, 35 * dt });			
		}
		else {
			b.move({ 0, -35 * dt });
		}
		b._Update(dt);
	}

}

void Bullet::_Update(const float & dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			//player bullets dont collide with player
			if (!_mode && s == player) {
				continue;
			}
			//invader bullets dont collide with invaders
			if (_mode && s != player) {
				continue;
			}
			if (!s->isExploded() && s->getGlobalBounds().intersects(boundingBox)) {
				//explode ship
				s->Explode();
				//warp bullets off screen
				setPosition(-100, -100);
				return;
			}
		}
	}
}

void Bullet::Render(sf::RenderWindow &window) {
	for (auto &b : bullets) {
		window.draw(b);
	}
}

void Bullet::Fire(const sf::Vector2f &pos, const bool mode) {
	bullets[++bulletPointer] = Bullet(pos, mode);
}

