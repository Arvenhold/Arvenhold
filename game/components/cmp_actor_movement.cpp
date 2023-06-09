#include "cmp_actor_movement.h"
#include <LevelSystem.h>
#include <engine.h>
#include <iostream>

using namespace sf;
using namespace std;

void ActorMovementComponent::update(double dt) {
    PhysicsComponent::update(dt);
}

ActorMovementComponent::ActorMovementComponent(Entity* p, const b2PolygonShape Shape)
    : _speed(100.0f), PhysicsComponent(p, true, Shape) {
    _body->SetSleepingAllowed(false);
    _body->SetFixedRotation(true);
    _body->SetBullet(true);
}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
    return true;
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
    auto pp = _parent->getPosition() + p;
    if (validMove(pp)) {
        _parent->setPosition(pp);
    }
}

void ActorMovementComponent::move(float x, float y) {
    move(Vector2f(x, y));
}