#include "cmp_enemy_ai.h"
#include "system_physics.h"

using namespace std;
using namespace sf;

void EnemyAIComponent::update(double dt) {
    /*auto mov = _direction * (float)(dt * _speed);
    mov.x += _direction.x * 16.f;
    if (!validMove(_parent->getPosition() + mov)) {
        _direction *= -1.f;
    }*/




    
    Vector2f p = (_parent->getPosition() - _player->getPosition());

    _direction = normalize(p);

    impulse(_direction * (float)(dt * _speed));

    auto v = getVelocity();
    v.x = copysign(min(abs(v.x), 200.0f), v.x);
    v.y = copysign(min(abs(v.y), 200.0f), v.y);
    setVelocity(v);


    ActorMovementComponent::update(dt);
}

EnemyAIComponent::EnemyAIComponent(Entity* p, Entity* player, const b2PolygonShape Shape) : ActorMovementComponent(p, Shape){
    _direction = Vector2f(1.0f, 0);
    _speed = 100.0f;
    _player = player;
}