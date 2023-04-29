#pragma once

#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	Entity* _player;
public:
	void update(double dt) override;

	explicit EnemyAIComponent(Entity* p, Entity* player, const b2PolygonShape Shape);

	EnemyAIComponent() = delete;
};