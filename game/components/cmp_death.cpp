#include "cmp_death.h"
#include "../filehandling.h"
#include "../arvenhold.h"


using namespace sf;
using namespace std;

DeathComponent::DeathComponent(Entity *p /*, std::shared_ptr<Entity> player*/)
	: Component(p), _isPlayer(false)/*, _player(player)*/ {}

void DeathComponent::update(double dt) {

    //get distance to player

    if (_parent->getPosition().x - _player->getPosition().x > 25.0f && _parent->getPosition().y -_player->getPosition().y > 25.0f) {
        kill();
    }
}

void DeathComponent::render() {

}

void DeathComponent::kill() {

	_parent->setVisible(false);
		//FileHandler::save(gameWidth, gameHeight);

}


bool DeathComponent::getType() {
	return _isPlayer;
}
void DeathComponent::setType(bool type) {
	_isPlayer = type;
}

void DeathComponent::setTarget(std::shared_ptr<Entity> player) {
	_player = player;
}