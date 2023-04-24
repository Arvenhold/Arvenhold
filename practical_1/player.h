#pragma once
#include "entity.h"

class Player : public Entity {

private:
	float _speed;
	float _hp;
	float _armour;

public:
	void Update(double dt) override;
	Player();
	void Render(sf::RenderWindow& window) const override;


};