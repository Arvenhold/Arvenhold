#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

class EnemyFireComponent : public Component {
protected:

	// cooldown
	float _cooldown;
	//bool _ready;

	//radius
	//float _radius;

	float _damage;

	int _type;
	
	//has it been cast lately
	//bool _cast;

	//sprite
	//sf::Sprite* _sprite;
public:

	void fire();
	void update(double dt) override;
	void render() override {}
	explicit EnemyFireComponent::EnemyFireComponent(Entity* p, float damage, int type);
	EnemyFireComponent() = delete;
};



class EnemyAttackComponent : public Component {
protected:

	// Lifetime of spell
	float _lifetime;

	// Has it hit anything?
	bool _hit;

	float _damage;

public:
	void update(double dt) override;
	void render() override {}
	explicit EnemyAttackComponent(Entity* p, sf::Vector2f direction, float damage, int type, float lifetime);
	EnemyAttackComponent() = delete;
};