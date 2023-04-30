#include "cmp_explosion.h"
#include <system_resources.h>
using namespace std;
using namespace sf;

void ExplodeComponent::update(double dt) {
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
                if (length(_parent->getPosition() - e->getPosition()) < 128.0f)
                {
                    e->setForDelete();
                }
            }
        }
    }
}

ExplodeComponent::ExplodeComponent(Entity* p)
    : Component(p) {

    _lifetime = 0.15f;

    auto s = p->addComponent<SpriteComponent>();

    s->setTexure(Resources::get<Texture>("fireball_explode.png"));
    s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));
    s->getSprite().setScale({ 4.0f, 4.0f });

    /*auto ang = 90 + direction.angle().asDegrees();
    p->setRotation(ang);

    b2PolygonShape Shape;
    Shape.SetAsBox(0.0f, 0.0f);

    auto pc = p->addComponent<PhysicsComponent>(true, Shape);

    pc->setFriction(1.0f);
    pc->impulse(direction * 40.0f);
    pc->getFixture()->SetSensor(true);*/
}