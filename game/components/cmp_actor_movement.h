
#pragma once
#include "ecm.h"
#include "cmp_physics.h"

class ActorMovementComponent : public PhysicsComponent {
protected:
	bool validMove(const sf::Vector2f&);
	float _speed;

public:
	void update(double dt) override;
	void move(const sf::Vector2f&);
	void move(float x, float y);
	void render() override {}
	explicit ActorMovementComponent(Entity* p, const b2PolygonShape Shape);
	ActorMovementComponent() = delete;
};