#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class SpellComponent : public Component {
protected:
	void fire() const;
	void lightning() const;
	void cold() const;

	float _firetime;
	float _lighttime;
	float _coldtime;
	float _radius;

public:
	void update(double dt) override;
	void render() override {}
	explicit SpellComponent(Entity* p, float radius);
	SpellComponent() = delete;
};