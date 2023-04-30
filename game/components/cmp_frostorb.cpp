#include "cmp_frostorb.h"
#include <system_resources.h>
using namespace std;
using namespace sf;

void FrostOrbComponent::update(double dt) {
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
                if (length(_parent->getPosition() - e->getPosition()) < 100.0f)
                {
                    e->setForDelete();
                }
            }
            else if(t.find("wall") != t.end())
            {
                if (length(_parent->getPosition() - e->getPosition()) < 64.0f)
                {
                    _parent->get_components<PhysicsComponent>()[0]->setVelocity({ 0, 0 });
                }
            }
        }
    }

    static float angle = 0.f;
    angle += 3.f * dt;

    _parent->setRotation(angle* 90.0f);
}

FrostOrbComponent::FrostOrbComponent(Entity* p, Vector2f direction, float lifetime = 1.5f)
    : Component(p), _lifetime(lifetime) {

    auto s = p->addComponent<SpriteComponent>();

    s->setTexure(Resources::get<Texture>("frost_orb.png"));
    s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));
    s->getSprite().setScale({ 3, 3 });

    b2PolygonShape Shape;
    Shape.SetAsBox(0.0f, 0.0f);

    auto pc = p->addComponent<PhysicsComponent>(true, Shape);

    pc->setFriction(1.0f);
    pc->impulse(direction * 20.0f);
    pc->getFixture()->SetSensor(true);
}