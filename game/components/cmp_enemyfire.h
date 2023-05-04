#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "engine.h"

class EnemyFireComponent : public Component {
protected:

	// cooldown
	float _cooldown;

	// Damage
	float _damage;

	// Attack type
	int _type;

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

class EnemyHitComponent : public Component {
protected:

	Entity* _player;
	int _damage;

public:
	void hit();
	void update(double dt) override {};
	void render() override {}
	explicit EnemyHitComponent(Entity* p, Entity* player, int damage);
	EnemyHitComponent() = delete;
};