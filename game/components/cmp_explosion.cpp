#include "cmp_explosion.h"
#include <system_resources.h>
#include "cmp_health.h"
using namespace std;
using namespace sf;

/// <summary>
/// Update explosion
/// </summary>
/// <param name="dt">- delta time</param>
void ExplodeComponent::update(double dt) 
{
    // Time is running out
    _lifetime -= dt;

    // Is it dead yet?
    if (_lifetime <= 0.f) {
        _parent->setForDelete();
    }
    else
    {
        // If the explosion hasn't hit something yet 
        if (!_hit)
        {
            // Get enemies
            auto anemonies = _parent->scene->ents.find("enemy");

            // Check if spell has hit an enemy
            for (auto e : anemonies)
            {
                if (length(_parent->getPosition() - e->getPosition()) < 180.0f)
                {
                    _hit = true;

                    // Deal big damage
                    e->get_components<HealthComponent>()[0]->takeDamage(100);

                    // Spawn more booms
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

        // Make it bigger as time goes on
        auto scale = _parent->get_components<SpriteComponent>()[0]->getSprite().getScale().x;
        _parent->get_components<SpriteComponent>()[0]->getSprite().setScale(Vector2f(scale + dt * 40, scale + dt* 40));
    }
}

/// <summary>
/// Make an exploding component
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="cast">- Did a player cast it?</param>
ExplodeComponent::ExplodeComponent(Entity* p, bool cast)
    : Component(p), _cast(cast) {

    // It hasn't hit anyone yet
    _hit = false;
    _hits = 0;

    // It's not got long
    _lifetime = 0.12f;

    // Make explosion look explodey
    auto s = p->addComponent<SpriteComponent>();
    s->setTexure(Resources::get<Texture>("fireball_explode.png"));
    s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));
    s->getSprite().setScale({ 1.0f, 1.0f });
}