#pragma once
#include "entity.h"
#include "system_renderer.h"

class Player : public Entity {

private:
	float _speed;
	float _hp;
	float _armour;

public:
	void Update(double dt) override;
	Player();
};