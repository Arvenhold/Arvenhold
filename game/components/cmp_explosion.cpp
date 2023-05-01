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
        if (!_hit)
        {
            for (auto e : _parent->scene->ents.list)
            {
                auto t = e->getTags();

                if (t.find("enemy") != t.end())
                {
                    if (length(_parent->getPosition() - e->getPosition()) < 180.0f)
                    {
                        _hit = true;

                        e->setForDelete();

                        if (_hits < 4 && _cast)
                        {
                            auto explosion = _parent->scene->makeEntity();

                            explosion->setPosition(e->getPosition());
                            //bullet->addComponent<HurtComponent>();
                            explosion->addComponent<ExplodeComponent>(false);
                            _hits++;
                        }
                    }
                }
            }
        }

        auto scale = _parent->get_components<SpriteComponent>()[0]->getSprite().getScale().x;

        _parent->get_components<SpriteComponent>()[0]->getSprite().setScale(Vector2f(scale + dt * 40, scale + dt* 40));
    }
}

ExplodeComponent::ExplodeComponent(Entity* p, bool cast)
    : Component(p), _cast(cast) {

    _hit = false;
    _hits = 0;
    _lifetime = 0.12f;

    auto s = p->addComponent<SpriteComponent>();

    s->setTexure(Resources::get<Texture>("fireball_explode.png"));
    s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));
    s->getSprite().setScale({ 1.0f, 1.0f });
}