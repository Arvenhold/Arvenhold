#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

/// <summary>
/// Lightning Bolt! Lightning Bolt! Lightning Bolt!
/// </summary>
class LightningBoltComponent : public Component {
protected:
	float _lifetime;
	float _duration;
	bool _casted;
	bool _hit;

public:
	void update(double dt) override;
	void render() override {}
	explicit LightningBoltComponent(Entity* p, sf::Vector2f direction, bool cast, float lifetime);
	LightningBoltComponent() = delete;
};