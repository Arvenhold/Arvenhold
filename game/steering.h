#pragma once
#include <engine.h>

// Output from a steering behaviour.
struct SteeringOutput
{
    // Direction of travel.
    sf::Vector2f direction;
    // Rotation of travel.
    float rotation;
};

// Base class for steering behaviour
class SteeringBehaviour {
public:
    virtual ~SteeringBehaviour() = default;

    // Gets the output from a steering behaviour.
    virtual SteeringOutput getSteering() const noexcept = 0;
};

// Seek steering behaviour
class Seek : public SteeringBehaviour {
private:
    Entity* _character;
    Entity* _target;
    float _maxSpeed;
public:
    Seek() = delete;
    Seek(Entity* character, Entity* target, float maxSpeed)
        : _character(character), _target(target), _maxSpeed(maxSpeed) { }
    SteeringOutput getSteering() const noexcept;
};

// Flee
class Flee : public SteeringBehaviour {
private:
    Entity* _character;
    Entity* _target;
    float _maxSpeed;
public:
    Flee() = delete;
    Flee(Entity* character, Entity* target, float maxSpeed)
        : _character(character), _target(target), _maxSpeed(maxSpeed) { }
    SteeringOutput getSteering() const noexcept;
};

// Melee
class Hit : public SteeringBehaviour {
private:
    Entity* _character;
    Entity* _target;
public:
    Hit() = delete;
    Hit(Entity* character, Entity* target)
        : _character(character), _target(target) { }
    SteeringOutput getSteering() const noexcept;
};

// Arrow


// Spell
class Cast : public SteeringBehaviour {
private:
    Entity* _character;
    Entity* _target;
public:
    Cast() = delete;
    Cast(Entity* character, Entity* target)
        : _character(character), _target(target) { }
    SteeringOutput getSteering() const noexcept;
};

// Boss 

