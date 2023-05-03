#include "cmp_potion.h"
#include "cmp_health.h"
#include <SFML/graphics.hpp>
#include "../arvenhold.h"

using namespace sf;
using namespace std;

int PotionComponent::getPotionCoint() {
	return _PotionCount;
}

void PotionComponent::update(double dt) {

	_cooldown -= dt;
	if (controls[5] >= 200) {
		if (Mouse::isButtonPressed(Mouse::Button(controls[5]-200)) && _cooldown <= 0 && _PotionCount > 0) {
			auto phealth = _parent->get_components<HealthComponent>()[0];

			cout << "HEAL!!!" << endl;

			phealth->heal(phealth->getMaxHealth() / 3);

			_cooldown = 2.0f;
			_PotionCount--;
		}

	}
	else{
		if (Keyboard::isKeyPressed(Keyboard::Key(controls[5])) && _cooldown <= 0 && _PotionCount > 0) {
			auto phealth = _parent->get_components<HealthComponent>()[0];

			cout << "HEAL!!!" << endl;

			phealth->heal(phealth->getMaxHealth() / 3);

			_cooldown = 2.0f;
			_PotionCount--;
		}

	}
	if(_cooldown < 0) {
		_cooldown = 0;
	}
}


PotionComponent::PotionComponent(Entity* p) : Component(p), _MaxPotions(5), _PotionCount(5), _cooldown(0){}