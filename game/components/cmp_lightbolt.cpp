#include "cmp_lightbolt.h"
#include <system_resources.h>
#include "cmp_health.h"
#include "cmp_sound.h"
using namespace std;
using namespace sf;

/// <summary>
/// Update lightning spell
/// </summary>
/// <param name="dt">- delta time</param>
void LightningBoltComponent::update(double dt) {
    _lifetime -= dt;
    _duration += dt;
    if (_lifetime <= 0.f) {
        _parent->setForDelete();
    }
    else if (_duration > 0.05f)
    {
        // Get enemies and walls
        auto anemonies = _parent->scene->ents.find("enemy");
        auto walls = _parent->scene->ents.find("wall");

        // Check if spell has hit an enemy
        for (auto e : anemonies)
        {
            if (length(_parent->getPosition() - e->getPosition()) < 54.0f)
            {
                // Give the enemy a message
                e->get_components<HealthComponent>()[0]->takeDamage(60);
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

        // If it was casted by a person and it hit something
        if (_casted && _hit)
        {
            // Create some offshoots
            int shoots = 6;

            for (int i = 0; i < shoots; i++)
            {
                // Have the children each go off in their own directions in life
                auto direction = rotate(normalize(Vector2f(1, 0)), _parent->getRotation() + i*(360.0f/shoots));
                auto lightningBolt = _parent->scene->makeEntity();
                lightningBolt->setPosition(_parent->getPosition() + 10.0f * direction);
                lightningBolt->addComponent<LightningBoltComponent>(direction, false, 1.0f);
            }
        }
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="p"></param>
/// <param name="direction"></param>
/// <param name="cast"></param>
/// <param name="lifetime"></param>
LightningBoltComponent::LightningBoltComponent(Entity* p, Vector2f direction, bool cast, float lifetime = 4.0f)
    : Component(p), _lifetime(lifetime) {

    _hit = false;
    _duration = 0;
    _casted = cast;

    auto hitSound = _parent->scene->ents.find("sound")[0];
    hitSound->get_components<SoundComponent>()[2]->play();

    auto s = p->addComponent<SpriteComponent>();

    s->setTexure(Resources::get<Texture>("light_bolt.png"));
    s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
    s->getSprite().setScale({ 1.5f, 1.5f });

    auto ang = 90 + direction.angle().asDegrees();
    p->setRotation(ang);

    b2PolygonShape Shape;
    Shape.SetAsBox(0.0f, 0.0f);

    auto pc = p->addComponent<PhysicsComponent>(true, Shape);

    pc->setFriction(1.0f);
    pc->getFixture()->SetSensor(true);
    pc->impulse(direction * 50.0f);
}