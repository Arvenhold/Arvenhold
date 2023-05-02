#include "cmp_enemyfire.h"
#include <system_resources.h>
#include "cmp_explosion.h"
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
        auto anemonies = _parent->scene->ents.find("enemy");
        auto walls = _parent->scene->ents.find("wall");

        auto p_list = _parent->scene->ents.find("wall");
        auto player = p_list[0];

        //auto player = _parent->scene->ents.find("player");

        if (length(_parent->getPosition() - player->getPosition()) < 48.0f)
        {
            _parent->setForDelete();
            _hit = true;
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
EnemyAttackComponent::EnemyAttackComponent(Entity* p, Vector2f direction, float lifetime = 4.0f)
    : Component(p), _lifetime(lifetime){

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


void EnemyFireComponent::update(double dt)
{
    _cooldown -= dt;


    if (_cooldown <= 0.f && _cast)
    {
        _sprite->setColor(Color(255, 255, 255));
        _cast = false;
    }



    // Cast fireball
    if (_cooldown <= 0.f && _ready)
    {
        fire();                                     // Cast the spell
        _cooldown = 1.f;                            // Set cooldown
        _sprite->setColor(Color(150, 150, 150));     // Darken UI
        _cast = true;                              // Set casted
    }
}




void EnemyFireComponent::fire() const{
    // Which direction to cast?
    auto xDir = 1.0f;
    auto yDir = 1.0f;

    // Check for mouse or controller
    /*
    if (true)
    {
        // Set direction to towards mouse
        xDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).x - Engine::getWindowSize().x * 0.5f;
        yDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).y - Engine::getWindowSize().y * 0.5f;
    }
    else
    {
        // Set direction to towards player movement
        xDir = Joystick::getAxisPosition(0, Joystick::X);
        yDir = Joystick::getAxisPosition(0, Joystick::Y);
    }
    */

    auto p_list = _parent->scene->ents.find("wall");
    auto player = p_list[0];

    xDir = 1.0f * player->getPosition().x;
    yDir = 1.0f * player->getPosition().y;

    // Normalise direction vector
    auto direction = normalize(Vector2f(xDir, yDir));

    // Cast the fireball
    auto fireball = _parent->scene->makeEntity();
    fireball->setPosition(_parent->getPosition() + 20.0f * direction);
    fireball->addComponent<EnemyAttackComponent>(direction, 4.0f);
}


EnemyFireComponent::EnemyFireComponent(Entity* p, float radius, Sprite* s)
    : Component(p), _cooldown(1.f), _radius(radius), _sprite(s), _cast(false){}