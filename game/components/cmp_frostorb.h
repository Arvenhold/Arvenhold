#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

class FrostOrbComponent : public Component {
protected:
	float _lifetime;

public:
	void update(double dt) override;
	void render() override {}
	explicit FrostOrbComponent(Entity* p, sf::Vector2f direction, float lifetime);
	FrostOrbComponent() = delete;
};