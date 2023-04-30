#include "cmp_lightbolt.h"
#include <system_resources.h>
using namespace std;
using namespace sf;

void LightningBoltComponent::update(double dt) {
    _lifetime -= dt;
    _duration += dt;
    if (_lifetime <= 0.f) {
        _parent->setForDelete();
    }
    else if (_duration > 0.05f)
    {

        for (auto e : _parent->scene->ents.list)
        {
            auto t = e->getTags();

            if (t.find("enemy") != t.end())
            {
                if (length(_parent->getPosition() - e->getPosition()) < 54.0f)
                {
                    e->setForDelete();
                    _parent->setForDelete();
                    _hit = true;
                }
            }
            else if (t.find("wall") != t.end())
            {
                if (length(_parent->getPosition() - e->getPosition()) < 64.0f)
                {
                    _parent->setForDelete();
                    _hit = true;
                }
            }
        }

        if (_casted && _hit)
        {
            for (int i = 0; i < 4; i++)
            {
                auto xDir = cos(i * b2_pi * 0.5f) + sin(i * b2_pi * 0.5f);
                auto yDir = cos(i * b2_pi);

                auto direction = normalize(Vector2f(xDir, yDir));

                auto lightningBolt = _parent->scene->makeEntity();
                lightningBolt->setPosition(_parent->getPosition() + 10.0f * direction);
                //bullet->addComponent<HurtComponent>();
                lightningBolt->addComponent<LightningBoltComponent>(direction, false, 1.0f);
            }
        }
    }
}

LightningBoltComponent::LightningBoltComponent(Entity* p, Vector2f direction, bool cast, float lifetime = 4.0f)
    : Component(p), _lifetime(lifetime) {

    _hit = false;
    _duration = 0;
    _casted = cast;

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