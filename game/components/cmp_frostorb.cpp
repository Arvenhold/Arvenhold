#include "cmp_frostorb.h"
#include <system_resources.h>
#include "cmp_health.h"
using namespace std;
using namespace sf;

/// <summary>
/// Update frost spell
/// </summary>
/// <param name="dt">- delta time</param>
void FrostOrbComponent::update(double dt) 
{
    // Update lifetime
    _lifetime -= dt;

    // If expired delete
    if (_lifetime <= 0.f) {
        _parent->setForDelete();
    }
    else
    {
        // Get enemies and walls
        auto anemonies = _parent->scene->ents.find("enemy");
        auto walls = _parent->scene->ents.find("wall");

        // Check if spell has hit an enemy
        for (auto e : anemonies)
        {
            if (length(_parent->getPosition() - e->getPosition()) < 100.0f)
            {
                // Hurt the enemies feelings
                e->get_components<HealthComponent>()[0]->takeDamage(25);
            }
        }

        // Has it not hit a wall yet?
        for (auto w : walls)
        {
            if (length(_parent->getPosition() - w->getPosition()) < 64.0f)
            {
                // Stop moving
                _parent->get_components<PhysicsComponent>()[0]->setVelocity({ 0, 0 });
            }
        }
    }

    // Spin to win
    static float angle = 0.f;
    angle += 3.f * dt;
    _parent->setRotation(angle* 90.0f);
}

/// <summary>
/// Create frost orb
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="direction">- Direction of travel</param>
/// <param name="lifetime">- Time spell lasts</param>
FrostOrbComponent::FrostOrbComponent(Entity* p, Vector2f direction, float lifetime = 1.5f)
    : Component(p), _lifetime(lifetime) {

    // Add frost spell sprite
    auto s = p->addComponent<SpriteComponent>();
    s->setTexure(Resources::get<Texture>("frost_orb.png"));
    s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));
    s->getSprite().setScale({ 3, 3 });

    // Give physics
    b2PolygonShape Shape;
    Shape.SetAsBox(0.0f, 0.0f);
    auto pc = p->addComponent<PhysicsComponent>(true, Shape);
    pc->setFriction(1.0f);
    pc->impulse(direction * 20.0f);
    pc->getFixture()->SetSensor(true);
}