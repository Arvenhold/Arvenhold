#include "player.h"
using namespace sf;
using namespace std;

void Player::Update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
			move(Vector2f(0.f, -_speed));
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		move(Vector2f(0.f, _speed));
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f(-_speed, 0.0f));
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f(-_speed, 0.0f));
	}
	Entity::Update(dt);
}

Player::Player() 
	: _speed(5.0f), _hp(50), _armour(2), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}


void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}