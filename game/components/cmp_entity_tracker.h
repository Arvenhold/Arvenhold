#pragma once

#include <ecm.h>

/// <summary>
/// Got yourself a tracker eh?
/// </summary>
class EntityTrackerComponent : public Component {
protected:

	// The target
	Entity* _ttarget;

public:
	void update(double dt) override;
	void render() override {};
	explicit EntityTrackerComponent(Entity* p, Entity* ttarget);
	EntityTrackerComponent() = delete;
};