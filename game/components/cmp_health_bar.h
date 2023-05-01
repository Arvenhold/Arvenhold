#pragma once

#include <ecm.h>
#include "engine.h"
#include "cmp_entity_tracker.h"

class HealthBarComponent : public EntityTrackerComponent {
protected:
	Entity* _hpTarget;
	float _ttime;

public:
	void update(double dt) override;
	void render() override {};
	bool isTargetAlive();
	explicit HealthBarComponent(Entity* p, Entity* ttarget, Entity* hpTarget);
	HealthBarComponent() = delete;
};