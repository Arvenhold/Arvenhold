#include "cmp_fireball.h"
#include <system_resources.h>
#include "cmp_explosion.h"
using namespace std;
using namespace sf;

/// <summary>
/// Update fireball
/// </summary>
/// <param name="dt">- delta time</param>
void FireballComponent::update(double dt) 
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
            if (length(_parent->getPosition() - e->getPosition()) < 48.0f)
            {
                _parent->setForDelete();
                _hit = true;
            }
        }

        // If not hit enemy has it hit a wall?
        if (!_hit)
        {
            for (auto w : walls)
            {
                if (length(_parent->getPosition() - w->getPosition()) < 64.0f)
                {
                    _parent->setForDelete();
                    _hit = true;
                }
            }
        }

        // If it has hit, make it go boom
        if (_hit)
        {
            // Create an explosion
            auto explosion = _parent->scene->makeEntity();

            // Just infront of where the fireball was
            auto offset = _parent->get_components<PhysicsComponent>()[0]->getVelocity();
            offset.y = -1.0f * offset.y;
            explosion->setPosition(_parent->getPosition() + normalize(offset) * 60.0f);
            explosion->addComponent<ExplodeComponent>(true);
        }
    }
}

/// <summary>
/// Create me a fireball
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="direction">- Direction of travel</param>
/// <param name="lifetime">- Time spell lasts</param>
FireballComponent::FireballComponent(Entity* p, Vector2f direction, float lifetime = 4.0f)
    : Component(p), _lifetime(lifetime) {

    // It has not hit yet...
    _hit = false;

    // Give the fireball a new look
    auto s = p->addComponent<SpriteComponent>();
    s->setTexure(Resources::get<Texture>("fireball.png"));
    s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
    s->getSprite().setScale({ 2.0f, 2.0f });

    // Rotate it to be looking like it knows where it is going
    auto ang = 90 + direction.angle().asDegrees();
    p->setRotation(ang);

    // Give it some physics
    b2PolygonShape Shape;
    Shape.SetAsBox(0.0f, 0.0f);
    auto pc = p->addComponent<PhysicsComponent>(true, Shape);
    pc->setFriction(1.0f);
    pc->impulse(direction * 40.0f);
    pc->getFixture()->SetSensor(true);
}