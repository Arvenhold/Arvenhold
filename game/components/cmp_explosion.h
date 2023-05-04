#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

/// <summary>
/// Big bada boom
/// </summary>
class ExplodeComponent : public Component {
protected:

	// How long it has
	float _lifetime;

	// Has it ever hit anyone?
	bool _hit;

	// How many has it hit?
	int _hits;

	// Did someone do this?
	bool _cast;

public:
	void update(double dt) override;
	void render() override {}
	explicit ExplodeComponent(Entity* p, bool cast);
	ExplodeComponent() = delete;
};