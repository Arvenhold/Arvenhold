#pragma once
#include "ecm.h"


class PotionComponent : public Component {
protected:

	// Max and current HP
	int _MaxPotions;
	int _PotionCount;
	float _cooldown;

public:
	int getPotionCoint();
	void heal();

	void update(double dt);
	void render() {};

	explicit PotionComponent(Entity* p);
	PotionComponent() = delete;
};