#pragma once

#include "scene.h"
#include "ecm.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene();
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void Respawn();

public:
	GameScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
	std::shared_ptr<Entity> makeNibble(sf::Vector2f& nl, sf::Color c, float size, int pts);
};
