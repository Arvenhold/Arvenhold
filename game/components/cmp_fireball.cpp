#include "cmp_fireball.h"
#include <system_resources.h>
#include "cmp_explosion.h"
using namespace std;
using namespace sf;

void FireballComponent::update(double dt) {
    _lifetime -= dt;
    if (_lifetime <= 0.f) {
        _parent->setForDelete();
    }
    else
    {
        for (auto e : _parent->scene->ents.list)
        {
            auto t = e->getTags();

            if (t.find("enemy") != t.end())
            {
                if (length(_parent->getPosition() - e->getPosition()) < 48.0f)
                {
                    //e->setForDelete();
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

        if (_hit)
        {
            auto explosion = _parent->scene->makeEntity();

            auto offset = _parent->get_components<PhysicsComponent>()[0]->getVelocity();

            offset.y = -1.0f * offset.y;

            explosion->setPosition(_parent->getPosition() + normalize(offset) * 80.0f);
            //bullet->addComponent<HurtComponent>();
            explosion->addComponent<ExplodeComponent>();
        }
    }
}

FireballComponent::FireballComponent(Entity* p, Vector2f direction, float lifetime = 4.0f)
    : Component(p), _lifetime(lifetime) {

    _hit = false;

    auto s = p->addComponent<SpriteComponent>();

    s->setTexure(Resources::get<Texture>("fireball.png"));
    s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
    s->getSprite().setScale({ 2.0f, 2.0f });

    auto ang = 90 + direction.angle().asDegrees();
    p->setRotation(ang);

    b2PolygonShape Shape;
    Shape.SetAsBox(0.0f, 0.0f);

    auto pc = p->addComponent<PhysicsComponent>(true, Shape);

    pc->setFriction(1.0f);
    pc->impulse(direction * 40.0f);
    pc->getFixture()->SetSensor(true);
}