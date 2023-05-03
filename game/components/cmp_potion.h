#pragma once
#include "ecm.h"
#include <SFML/graphics.hpp>

class PotionComponent : public Component {
protected:

	// Max and current HP
	int _MaxPotions;
	int _PotionCount;
	float _cooldown;

	// Used recently
	bool _used;

	// UI elements
	sf::Sprite* _potionS;
	sf::Text* _potionT;

public:
	int getPotionCoint();
	void heal();

	void update(double dt);
	void render() {};

	explicit PotionComponent(Entity* p, sf::Sprite* potionS, sf::Text* potionN);
	PotionComponent() = delete;
};