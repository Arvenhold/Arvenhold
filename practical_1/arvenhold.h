//pacman.h
#include <memory>
#include "scene.h"
#include <SFML/Graphics.hpp>
#include <LevelSystem.h>
#include "system_renderer.h"
#include <iostream>
#include "player.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

extern std::shared_ptr<Player> player;

extern sf::Texture roomSpriteSheet;
extern sf::Texture wizardSprite;

class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(double dt) override;
	void render() override;
	void load()override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};

