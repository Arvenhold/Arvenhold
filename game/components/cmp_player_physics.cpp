#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isGrounded() const {
    auto touch = getTouching();
    const auto& pos = _body->GetPosition();
    const float halfPlrHeigt = _size.y * .5f;
    const float halfPlrWidth = _size.x * .52f;
    b2WorldManifold manifold;
    for (const auto& contact : touch) {
        contact->GetWorldManifold(&manifold);
        const int numPoints = contact->GetManifold()->pointCount;
        bool onTop = numPoints > 0;
        // If all contacts are below the player.
        for (int j = 0; j < numPoints; j++) {
            onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
        }
        if (onTop) {
            return true;
        }
    }

    return false;
}

void PlayerPhysicsComponent::update(double dt) 
{
    Vector2f direction(0.0f, 0.0f);

    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))
    {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            direction.x -= 1.0f;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            direction.x += 1.0f;
        }
    }
    else
    {
        dampen({ 0.9f, 1.0f });
    }

    if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::W))
    {
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            direction.y -= 1.0f;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            direction.y += 1.0f;
        }
    }
    else
    {
        dampen({ 1.0f, 0.9f });
    }

    impulse(normalize(direction) * _groundspeed * (float)dt);

    // Clamp velocity.
    auto v = getVelocity();
    v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
    v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
    setVelocity(v);

    PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, const b2PolygonShape Shape)
    : PhysicsComponent(p, true, Shape) {
    //_size = sv2_to_bv2(size, true);
    _maxVelocity = Vector2f(400.f, 400.f);
    _groundspeed = 40.f;
    _grounded = false;
    _body->SetSleepingAllowed(false);
    _body->SetFixedRotation(true);
    //Bullet items have higher-res collision detection
    _body->SetBullet(true);
}