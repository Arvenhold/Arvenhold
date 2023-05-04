//enemy_states.cpp
#include "enemy_states.h"
#include "components/cmp_sprite.h"

using namespace sf;

void NormalState::execute(Entity *owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Blue);
    
    if (length(owner->getPosition() - _player->getPosition()) < 100.0f){
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("near");
    }
}

void NearState::execute(Entity *owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Green);
    
    if (length(owner->getPosition() - _player->getPosition()) > 100.0f){
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("normal");
    }
}