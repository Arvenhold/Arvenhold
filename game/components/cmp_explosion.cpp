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

        auto scale = _parent->get_components<SpriteComponent>()[0]->getSprite().getScale().x;

        _parent->get_components<SpriteComponent>()[0]->getSprite().setScale(Vector2f(scale + dt * 30, scale + dt* 30));
    }
}

ExplodeComponent::ExplodeComponent(Entity* p)
    : Component(p) {

    _lifetime = 0.1f;

    auto s = p->addComponent<SpriteComponent>();

    s->setTexure(Resources::get<Texture>("fireball_explode.png"));
    s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));
    s->getSprite().setScale({ 1.0f, 1.0f });
}