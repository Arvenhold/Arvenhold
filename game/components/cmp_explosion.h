#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

class ExplodeComponent : public Component {
protected:
	float _lifetime;
	bool _hit;
	int _hits;
	bool _cast;

public:
	void update(double dt) override;
	void render() override {}
	explicit ExplodeComponent(Entity* p, bool cast);
	ExplodeComponent() = delete;
};