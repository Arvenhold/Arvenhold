#pragma once
#include "ecm.h"

/// <summary>
/// Can I get some health?
/// </summary>
class HealthComponent : public Component {
protected:

	// Max and current HP
	int _maxHP;
	int _currentHP;

	// Hit recently? When?
	float _cooldown;
	bool _hit;

public:
	HealthComponent() = delete;
	explicit HealthComponent(Entity* p, int maxHP);
	void update(double dt);
	void render() {};
	void takeDamage(int damage);
	void heal(int heal);
	int getHealth();
	int getMaxHealth();
	bool isDead();
};