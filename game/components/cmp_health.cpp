#include "cmp_health.h"
#include "cmp_sprite.h"

using namespace sf;

/// <summary>
/// Update health
/// </summary>
/// <param name="dt">- delta time</param>
void HealthComponent::update(double dt)
{
	// Reduce hit cooldown
	_cooldown -= dt;

	// If cooldown is now over
	if (_hit && _cooldown <= 0.f)
	{
		// Reset look of entity
		_parent->get_components<SpriteComponent>()[0]->getSprite().setColor(Color(255, 255, 255));
		_hit = false;
	}

	// If no health left, must be dead
	if (_currentHP <= 0)
	{
		_parent->setForDelete();
	}
}

/// <summary>
/// Take some damage
/// </summary>
/// <param name="damage">- Damage amount</param>
void HealthComponent::takeDamage(int damage)
{
	// If not hit too recently
	if (_cooldown <= 0.f)
	{
		// Take damage
		_currentHP -= damage;
		_cooldown = 0.15f;
		_hit = true;

		// Give a red look to signify damage taken
		_parent->get_components<SpriteComponent>()[0]->getSprite().setColor(Color(255, 150, 150));

		// If health below 0 make it 0
		if (_currentHP < 0)
		{
			_currentHP = 0;
		}
	}
}

/// <summary>
/// Heal entity
/// </summary>
/// <param name="heal"></param>
void HealthComponent::heal(int heal)
{
	// Heal some
	_currentHP += heal;

	// Can't over heal
	if (_currentHP > _maxHP)
	{
		_currentHP = _maxHP;
	}
}

/// <summary>
/// What is my health
/// </summary>
/// <returns>Current health</returns>
int HealthComponent::getHealth()
{
	return _currentHP;
}

/// <summary>
/// What is my max health
/// </summary>
/// <returns>Max health</returns>
int HealthComponent::getMaxHealth()
{
	return _maxHP;
}

/// <summary>
/// Am I dead?
/// </summary>
/// <returns>Hopefully not, but maybe</returns>
bool HealthComponent::isDead()
{
	// If hp 0, dead
	if (_currentHP == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Assign some health
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="maxHP">- Max HP amount</param>
HealthComponent::HealthComponent(Entity* p, int maxHP) : Component(p), _maxHP(maxHP), _currentHP(maxHP), _cooldown(0.15f), _hit(false) {}
