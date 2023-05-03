#include "cmp_enemyfire.h"
#include <system_resources.h>
#include "cmp_explosion.h"
#include "cmp_health.h"
#include "../arvenhold.h"
#include "cmp_player_physics.h"

using namespace std;
using namespace sf;

/// <summary>
/// Update fireball
/// </summary>
/// <param name="dt">- delta time</param>

void EnemyAttackComponent::update(double dt) {


    // Update lifetime
    _lifetime -= dt;

    // If expired delete
    if (_lifetime <= 0.f) {
        _parent->setForDelete();
    }
    else
    {
        // Get enemies and walls
        //auto anemonies = _parent->scene->ents.find("enemy");
        auto walls = _parent->scene->ents.find("wall");

        auto p_list = _parent->scene->ents.find("player");
        auto player = p_list[0];

        //auto player = _parent->scene->ents.find("player");

        if (length(_parent->getPosition() - player->getPosition()) < 48.0f)
        {
            _parent->setForDelete();
            _hit = true;
            player->get_components<HealthComponent>()[0]->takeDamage(_damage);
        }

        // If not hit enemy has it hit a wall?
        if (!_hit)
        {
            for (auto w : walls)
            {
                if (length(_parent->getPosition() - w->getPosition()) < 64.0f)
                {
                    _parent->setForDelete();
                    //_hit = true;
                }
            }
        }
    }
}

/// <summary>
/// Create me a fireball
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="direction">- Direction of travel</param>
/// <param name="lifetime">- Time spell lasts</param>
EnemyAttackComponent::EnemyAttackComponent(Entity* p, Vector2f direction, float damage, int type, float lifetime = 4.0f)
    : Component(p), _damage(damage), _lifetime(lifetime){

    // It has not hit yet...
    _hit = false;

    // Give the fireball a new look
    auto s = p->addComponent<SpriteComponent>();

    if (type == 0 || type == 2)
    {
        s->setTexure(Resources::get<Texture>("death_ball.png"));
    }
    else if (type == 1)
    {
        s->setTexure(Resources::get<Texture>("arrow.png"));
    }
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
    if (type == 0 || type == 2)
    {
        s->setTexure(Resources::get<Texture>("death_ball.png"));
        pc->impulse(direction * 30.0f);
        /*if (eCast->getStatus() != 2)
        {
            eCast->play();
        }*/
    }
    else if (type == 1)
    {
        s->setTexure(Resources::get<Texture>("arrow.png"));
        pc->impulse(direction * 50.0f);
        /*if (eShoot->getStatus() != 2)
        {
            eShoot->play();
        }*/
    }
    pc->getFixture()->SetSensor(true);
}


void EnemyFireComponent::update(double dt)
{
    _cooldown -= dt;
}

void EnemyFireComponent::fire()
{
    if (_cooldown <= 0.f)
    {
        if (_type < 2)
        {
            _cooldown = 1.f;

            // Which direction to cast?
            auto xDir = 1.0f;
            auto yDir = 1.0f;

            auto p_list = _parent->scene->ents.find("player");
            auto player = p_list[0];

            xDir = (player->getPosition().x - _parent->getPosition().x) + 25 * normalize(player->get_components<PlayerPhysicsComponent>()[0]->getVelocity()).x;
            yDir = (player->getPosition().y - _parent->getPosition().y) - 25 * normalize(player->get_components<PlayerPhysicsComponent>()[0]->getVelocity()).y;

            // Normalise direction vector
            auto direction = normalize(Vector2f(xDir, yDir));

            // Cast the fireball
            auto fireball = _parent->scene->makeEntity();
            fireball->setPosition(_parent->getPosition() + 20.0f * direction);
            fireball->addComponent<EnemyAttackComponent>(direction, _damage, _type, 4.0f);
        }
        else
        {
            _cooldown = 4.f;

            for (int i = 0; i < 6; i++)
            {
                // Have the children each go off in their own directions in life
                auto direction = rotate(normalize(Vector2f(1, 0)), _parent->getRotation() + i * 45.f);
                // Cast the fireball
                auto fireball = _parent->scene->makeEntity();
                fireball->setPosition(_parent->getPosition() + 20.0f * direction);
                fireball->addComponent<EnemyAttackComponent>(direction, _damage, _type, 4.0f);
            }
        }
    }
}


EnemyFireComponent::EnemyFireComponent(Entity* p, float damage, int type)
    : Component(p), _cooldown(1.f), _damage(damage), _type(type) {}

void EnemyHitComponent::hit()
{
    // Hit player
    _player->get_components<HealthComponent>()[0]->takeDamage(_damage);
}

EnemyHitComponent::EnemyHitComponent(Entity* p, Entity* player, int damage) : Component(p), _player(player), _damage(damage)
{}
