#include "steering.h"

using namespace sf;
using namespace std;

SteeringOutput Seek::getSteering() const noexcept {
    SteeringOutput steering;
    steering.direction = _target->getPosition() - _character->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}

SteeringOutput Flee::getSteering() const noexcept {
    SteeringOutput steering;
    steering.direction = _character->getPosition() - _target->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}

/// <summary>
/// Melee hit
/// </summary>
/// <returns></returns>
SteeringOutput Hit::getSteering() const noexcept
{
    SteeringOutput steering;
    steering.direction = Vector2f(0, 0);
    steering.rotation = 0.0f;
    return steering;
}


/// <summary>
/// Enemy casting steering state
/// </summary>
/// <returns></returns>
SteeringOutput Cast::getSteering() const noexcept
{
    SteeringOutput steering;
    steering.direction = Vector2f(0, 0);
    steering.rotation = 0.0f;
    return steering;
}
