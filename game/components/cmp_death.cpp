#include "cmp_death.h"
#include "../filehandling.h"
#include "../arvenhold.h"


using namespace sf;
using namespace std;

DeathComponent::DeathComponent(Entity *p)
	: Component(p), _isPlayer(false){}

void DeathComponent::update(double dt) {
	kill();
}

void DeathComponent::render() {

}

void DeathComponent::kill() {
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		FileHandler::save(gameWidth, gameHeight);
	}
}


bool DeathComponent::getType() {
	return _isPlayer;
}
void DeathComponent::setType(bool type) {
	_isPlayer = type;
}

