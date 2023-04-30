#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

class ExplodeComponent : public Component {
protected:
	float _lifetime;

public:
	void update(double dt) override;
	void render() override {}
	explicit ExplodeComponent(Entity* p);
	ExplodeComponent() = delete;
};