#pragma once
#include "ecm.h"
#include <sfml/Graphics.hpp>

#include "cmp_physics.h"
#include "system_physics.h"


class DeathComponent : public Component {
protected:
	bool _isPlayer;
	std::shared_ptr<Entity> _player;
public:
	DeathComponent() = delete;
	explicit DeathComponent(Entity* p/*, std::shared_ptr<Entity> player */);
	void update(double dt);
	void render();
	void kill();

	bool getType();
	void setType(bool type);

	void DeathComponent::setTarget(std::shared_ptr<Entity> player);

	bool isTouching(const PhysicsComponent& pc, b2Contact const* bc) const;

};