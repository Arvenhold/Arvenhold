#pragma once

#include <ecm.h>

class EntityTrackerComponent : public Component {
protected:
	Entity* _ttarget;

public:
	void update(double dt) override;
	void render() override {};
	explicit EntityTrackerComponent(Entity* p, Entity* ttarget);
	EntityTrackerComponent() = delete;
};