#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

/// <summary>
/// Fire ballin'
/// </summary>
class FireballComponent : public Component {
protected:

	// Lifetime of spell
	float _lifetime;

	// Has it hit anything?
	bool _hit;

public:
	void update(double dt) override;
	void render() override {}
	explicit FireballComponent(Entity* p, sf::Vector2f direction, float lifetime);
	FireballComponent() = delete;
};