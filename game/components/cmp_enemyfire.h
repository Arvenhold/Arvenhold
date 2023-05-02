#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

class EnemyFireComponent : public Component {
protected:


	//use spell
	void fire() const;

	// cooldown
	float _cooldown;
	bool _ready;

	//radius
	float _radius;
	
	//has it been cast lately
	bool _cast;

	//sprite
	sf::Sprite* _sprite;
public:
	void update(double dt) override;
	void render() override {}
	explicit EnemyFireComponent::EnemyFireComponent(Entity* p, float radius, sf::Sprite* s);
	EnemyFireComponent() = delete;
};



class EnemyAttackComponent : public Component {
protected:
	// Lifetime of spell
	float _lifetime;


	// Has it hit anything?
	bool _hit;

public:
	void update(double dt) override;
	void render() override {}
	explicit EnemyAttackComponent(Entity* p, sf::Vector2f direction, float lifetime);
	EnemyAttackComponent() = delete;
};