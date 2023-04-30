#include "cmp_spell.h"
//#include "cmp_hurt_player.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <system_physics.h>
#include <system_physics.cpp>
#include "cmp_fireball.h"
#include "cmp_frostorb.h"
#include <system_resources.h>
#include "cmp_lightbolt.h"

using namespace std;
using namespace sf;

void SpellComponent::update(double dt) {
    _firetime -= dt;
    if (_firetime <= 0.f && (Keyboard::isKeyPressed(Keyboard::Num1) || Joystick::isButtonPressed(0,2))) {
        fire();
        _firetime = 1.f;
    }
    _lighttime -= dt;
    if (_lighttime <= 0.f && (Keyboard::isKeyPressed(Keyboard::Num2) || Joystick::isButtonPressed(0, 3))) {
        lightning();
        _lighttime = 1.5f;
    }
    _coldtime -= dt;
    if (_coldtime <= 0.f && (Keyboard::isKeyPressed(Keyboard::Num3) || Joystick::isButtonPressed(0, 1))) {
        cold();
        _coldtime = 2.f;
    }
}

void SpellComponent::fire() const {

    auto xDir = 1.0f;
    auto yDir = 1.0f;

    if (true)
    {
        xDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).x - Engine::getWindowSize().x * 0.5f;
        yDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).y - Engine::getWindowSize().y * 0.5f;
    }
    else
    {
        xDir = Joystick::getAxisPosition(0, Joystick::X);
        yDir = Joystick::getAxisPosition(0, Joystick::Y);
    }

    auto direction = normalize(Vector2f(xDir, yDir));

    auto fireball = _parent->scene->makeEntity();
    fireball->setPosition(_parent->getPosition() + 20.0f*direction);
    //bullet->addComponent<HurtComponent>();
    fireball->addComponent<FireballComponent>(direction, 4.0f);
}

void SpellComponent::lightning() const
{
    auto xDir = 1.0f;
    auto yDir = 1.0f;

    if (true)
    {
        xDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).x - Engine::getWindowSize().x * 0.5f;
        yDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).y - Engine::getWindowSize().y * 0.5f;
    }
    else
    {
        xDir = Joystick::getAxisPosition(0, Joystick::X);
        yDir = Joystick::getAxisPosition(0, Joystick::Y);
    }

    auto direction = normalize(Vector2f(xDir, yDir));

    auto lightningBolt = _parent->scene->makeEntity();
    lightningBolt->setPosition(_parent->getPosition() + 20.0f * direction);
    //bullet->addComponent<HurtComponent>();
    lightningBolt->addComponent<LightningBoltComponent>(direction, true, 4.0f);
}

void SpellComponent::cold() const
{
    auto xDir = 1.0f;
    auto yDir = 1.0f;

    if (true)
    {
        xDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).x - Engine::getWindowSize().x * 0.5f;
        yDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).y - Engine::getWindowSize().y * 0.5f;
    }
    else
    {
        xDir = Joystick::getAxisPosition(0, Joystick::X);
        yDir = Joystick::getAxisPosition(0, Joystick::Y);
    }

    auto direction = normalize(Vector2f(xDir, yDir));

    auto frostOrb = _parent->scene->makeEntity();
    frostOrb->setPosition(_parent->getPosition() + 20.0f * direction);
    //bullet->addComponent<HurtComponent>();
    frostOrb->addComponent<FrostOrbComponent>(direction, 1.2f);
}

SpellComponent::SpellComponent(Entity* p, float radius)
    : Component(p), _firetime(2.f), _lighttime(1.5f), _coldtime(2.f), _radius(radius){}