#include "cmp_entity_tracker.h"

void EntityTrackerComponent::update(double dt)
{
	_parent->setPosition(_ttarget->getPosition());
}

EntityTrackerComponent::EntityTrackerComponent(Entity* p, Entity* ttarget) : Component(p), _ttarget(ttarget) {}

