#include "cmp_potion.h"
#include "cmp_health.h"
#include "../arvenhold.h"
#include "cmp_sound.h"

using namespace sf;
using namespace std;

int PotionComponent::getPotionCoint() {
	return _PotionCount;
}

void PotionComponent::update(double dt) {

	_cooldown -= dt;
	if (controls[5] >= 200) {
		if ((Mouse::isButtonPressed(Mouse::Button(controls[5]-200)) || Joystick::isButtonPressed(0, 2)) && _cooldown <= 0 && _PotionCount > 0) {
			auto phealth = _parent->get_components<HealthComponent>()[0];

			phealth->heal(phealth->getMaxHealth() / 3);

			_cooldown = 2.0f;
			_PotionCount--;
			_potionT->setString(to_string(_PotionCount));
			_potionS->setColor(Color(150, 150, 150));                     // Darken UI
			_used = true;
			auto hitSound = _parent->scene->ents.find("sound")[0];
			hitSound->get_components<SoundComponent>()[7]->play();
		}

	}
	else{
		if ((Keyboard::isKeyPressed(Keyboard::Key(controls[5])) || Joystick::isButtonPressed(0, 2)) && _cooldown <= 0 && _PotionCount > 0) {
			auto phealth = _parent->get_components<HealthComponent>()[0];

			phealth->heal(phealth->getMaxHealth() / 3);

			_cooldown = 2.0f;
			_PotionCount--;
			_potionT->setString(to_string(_PotionCount));
			_potionS->setColor(Color(150, 150, 150));                     // Darken UI
			_used = true;
			auto hitSound = _parent->scene->ents.find("sound")[0];
			hitSound->get_components<SoundComponent>()[7]->play();
		}

	}
	if(_PotionCount > 0 && _cooldown < 0 && _used) {
		_potionS->setColor(Color(255, 255, 255));                     // Darken UI
		_used = false;
	}
}


PotionComponent::PotionComponent(Entity* p, Sprite* potionS, Text* potionN) : Component(p), _MaxPotions(5), _PotionCount(5), _cooldown(0), _potionS(potionS), _potionT(potionN) {}