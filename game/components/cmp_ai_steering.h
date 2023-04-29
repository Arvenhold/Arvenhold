#pragma once
#include <ecm.h>
#include "../steering.h"
#include "cmp_physics.h"

class SteeringComponent : public PhysicsComponent {
protected:
    Seek _seek;
    Flee _flee;
    Entity* _player;
    bool validMove(const sf::Vector2f&) const;
public:
    void update(double dt) override;
    void move(const sf::Vector2f&);
    void move(float x, float y);
    void render() override { }
    explicit SteeringComponent(Entity* p, Entity* player, const b2PolygonShape Shape);
    SteeringComponent() = delete;
};

