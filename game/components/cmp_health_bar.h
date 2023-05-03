#pragma once

#include <ecm.h>
#include "engine.h"
#include "cmp_entity_tracker.h"

/// <summary>
/// Keep track of health with onscreen element
/// </summary>
class HealthBarComponent : public EntityTrackerComponent {
protected:

	// Whose health is it
	Entity* _hpTarget;

	float _ttime;

	float _scale;

public:
	void update(double dt) override;
	void render() override {};
	bool isTargetAlive();
	explicit HealthBarComponent(Entity* p, Entity* ttarget, Entity* hpTarget);
	HealthBarComponent() = delete;
};