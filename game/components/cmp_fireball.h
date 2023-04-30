#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

class FireballComponent : public Component {
protected:
	float _lifetime;
	bool _hit;

public:
	void update(double dt) override;
	void render() override {}
	explicit FireballComponent(Entity* p, sf::Vector2f direction, float lifetime);
	FireballComponent() = delete;
};