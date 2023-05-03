#include "cmp_spell.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <system_physics.h>
#include <system_physics.cpp>
#include "cmp_fireball.h"
#include "cmp_frostorb.h"
#include <system_resources.h>
#include "cmp_lightbolt.h"
#include "../arvenhold.h"

using namespace std;
using namespace sf;

/// <summary>
/// Update spelling
/// </summary>
/// <param name="dt">- delta time</param>
void SpellComponent::update(double dt) 
{
    // Countdown cooldowns
    _firetime -= dt;
    _lighttime -= dt;
    _coldtime -= dt;

    // If fireball can be cast, reset UI for it
    if (_firetime <= 0.f && _fCast)
    {
        _fireS->setColor(Color(255, 255, 255));
        _fCast = false;
        //pCast->play();
    }

    // If lightning strike can be cast, reset UI for it
    if (_lighttime <= 0.f && _lCast)
    {
        _lightS->setColor(Color(255, 255, 255));
        _lCast = false;
        //pCast->play();
    }

    // If frost orb can be cast, reset UI for it
    if (_coldtime <= 0.f && _cCast)
    {
        _frostS->setColor(Color(255, 255, 255));
        _cCast = false;
        //pCast->play();
    }

    // Cast fireball

    if (controls[4] >= 200)
    {
        if (_firetime <= 0.f && (Mouse::isButtonPressed(Mouse::Button(controls[4] - 200)) || Joystick::isButtonPressed(0, 4)))
        {
            fire();                                     // Cast the spell
            _firetime = 1.f;                            // Set cooldown
            _fireS->setColor(Color(150, 150, 150));     // Darken UI
            _fCast = true;                              // Set casted
        }

        // Cast lightning strike
        if (_lighttime <= 0.f && (Mouse::isButtonPressed(Mouse::Button(controls[4] - 200)) || Joystick::isButtonPressed(0, 5)))
        {
            lightning();                                // Cast the spell
            _lighttime = 1.5f;                          // Set cooldown
            _lightS->setColor(Color(150, 150, 150));    // Darken UI
            _lCast = true;                              // Set casted
        }

        // Cast frost orb
        if (_coldtime <= 0.f && (Mouse::isButtonPressed(Mouse::Button(controls[4]-200)) || Joystick::getAxisPosition(0, Joystick::Z) > 0))
        {
            cold();                                     // Cast the spell
            _coldtime = 3.f;                            // Set cooldown
            _frostS->setColor(Color(150, 150, 150));    // Darken UI
            _cCast = true;                              // Set casted
        }
    }
    else if (controls[4] < 200)
    {
        if (_firetime <= 0.f && (Keyboard::isKeyPressed(Keyboard::Key(controls[4])) || Joystick::isButtonPressed(0, 4)))
        {
            fire();                                     // Cast the spell
            _firetime = 1.f;                            // Set cooldown
            _fireS->setColor(Color(150, 150, 150));     // Darken UI
            _fCast = true;                              // Set casted
        }

        // Cast lightning strike
        if (_lighttime <= 0.f && (Keyboard::isKeyPressed(Keyboard::Key(controls[4])) || Joystick::isButtonPressed(0, 5)))
        {
            lightning();                                // Cast the spell
            _lighttime = 1.5f;                          // Set cooldown
            _lightS->setColor(Color(150, 150, 150));    // Darken UI
            _lCast = true;                              // Set casted
        }

        // Cast frost orb
        if (_coldtime <= 0.f && (Keyboard::isKeyPressed(Keyboard::Key(controls[4])) || Joystick::getAxisPosition(0, Joystick::Z) > 0))
        {
            cold();                                     // Cast the spell
            _coldtime = 3.f;                            // Set cooldown
            _frostS->setColor(Color(150, 150, 150));    // Darken UI
            _cCast = true;                              // Set casted
        }
    }
}

/// <summary>
/// Cast a fire spell
/// </summary>
void SpellComponent::fire() const {

    // Which direction to cast?
    auto xDir = 1.0f;
    auto yDir = 1.0f;

    // Check for mouse or controller
    if (!Joystick::isConnected(0))
    {
        // Set direction to towards mouse
        xDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).x - Engine::getWindowSize().x * 0.5f;
        yDir = 1.0f * Mouse::getPosition(Engine::GetWindow()).y - Engine::getWindowSize().y * 0.5f;
    }
    else
    {
        // Set direction to towards player movement
        xDir = Joystick::getAxisPosition(0, Joystick::U);
        yDir = Joystick::getAxisPosition(0, Joystick::R);
    }

    // Normalise direction vector
    auto direction = normalize(Vector2f(xDir, yDir));

    // Cast the fireball
    auto fireball = _parent->scene->makeEntity();
    fireball->setPosition(_parent->getPosition() + 20.0f*direction);
    fireball->addComponent<FireballComponent>(direction, 4.0f);
}

/// <summary>
/// Cast a lightning spell
/// </summary>
void SpellComponent::lightning() const
{
    // Which direction to cast?
    auto xDir = 1.0f;
    auto yDir = 1.0f;

    // Check for mouse or controller
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

    // Normalise direction vector
    auto direction = normalize(Vector2f(xDir, yDir));

    // Cast the lightning bolt
    auto lightningBolt = _parent->scene->makeEntity();
    lightningBolt->setPosition(_parent->getPosition() + 20.0f * direction);
    lightningBolt->addComponent<LightningBoltComponent>(direction, true, 4.0f);
}

/// <summary>
/// Cast a cold spell
/// </summary>
void SpellComponent::cold() const
{
    // Which direction to cast?
    auto xDir = 1.0f;
    auto yDir = 1.0f;

    // Check for mouse or controller
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

    // Normalise direction vector
    auto direction = normalize(Vector2f(xDir, yDir));

    // Cast the lightning bolt
    auto frostOrb = _parent->scene->makeEntity();
    frostOrb->setPosition(_parent->getPosition() + 20.0f * direction);
    frostOrb->addComponent<FrostOrbComponent>(direction, 1.2f);
}

/// <summary>
/// Me want spells
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="radius">- Spell radius</param>
/// <param name="fire">- Fire spell UI</param>
/// <param name="light">- Lightning spell UI</param>
/// <param name="cold">- Frost spell UI</param>
SpellComponent::SpellComponent(Entity* p, float radius, Sprite* fire, Sprite* light, Sprite* cold)
    : Component(p), _firetime(1.f), _lighttime(1.5f), _coldtime(3.f), _radius(radius), _fireS(fire), _lightS(light), _frostS(cold), _fCast(false), _lCast(false), _cCast(false){}