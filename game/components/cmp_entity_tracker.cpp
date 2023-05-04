#include "cmp_entity_tracker.h"

/// <summary>
/// Update tracking information
/// </summary>
/// <param name="dt"></param>
void EntityTrackerComponent::update(double dt)
{
	_parent->setPosition(_ttarget->getPosition());
}

/// <summary>
/// Hire a tracker
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="ttarget">- Whose the target?</param>
EntityTrackerComponent::EntityTrackerComponent(Entity* p, Entity* ttarget) : Component(p), _ttarget(ttarget) {}

