#include "cmp_health_bar.h"
#include <system_resources.h>
#include "cmp_sprite.h"
#include "cmp_health.h"

using namespace std;
using namespace sf;

/// <summary>
/// Update health bar
/// </summary>
/// <param name="dt">- delta time</param>
void HealthBarComponent::update(double dt)
{
	// If the target is dead then so is the healthbar
	if (_hpTarget->is_fordeletion())
	{
		_parent->setForDelete();
	}
	else
	{
		// Get health status of target
		auto health = _hpTarget->get_components<HealthComponent>()[0];
		auto current = health->getHealth();
		auto max = health->getMaxHealth();

		// Get current:max health ratio
		auto hp = (_scale * current) / (1.0f * max);

		// Update location
		EntityTrackerComponent::update(dt);

		// Healthbar sprites
		auto hpBackground = _parent->get_components<SpriteComponent>()[0];
		auto hpBar = _parent->get_components<SpriteComponent>()[1];

		// Get distance between target entity and player
		auto hpOffset = _hpTarget->getPosition() - _ttarget->getPosition();

		// Set healthbar position
		auto hpPos = hpBar->getSprite().getPosition();
		hpBar->getSprite().setScale(Vector2f(hp, _scale));
		hpBackground->getSprite().setPosition(hpOffset + hpBackground->getSprite().getPosition());
		hpBar->getSprite().setPosition(hpOffset + Vector2f(hpPos.x - 32* _scale*0.5f, hpPos.y));
	}
}

/// <summary>
/// Check if the entity this healthbar belongs to is being updated
/// </summary>
/// <returns>Status of target</returns>
bool HealthBarComponent::isTargetAlive()
{
	return _hpTarget->isAlive();
}

/// <summary>
/// Give me a healthbar
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="ttarget">- Player entity</param>
/// <param name="hpTarget">- Target entity</param>
HealthBarComponent::HealthBarComponent(Entity* p, Entity* ttarget, Entity* hpTarget) : EntityTrackerComponent(p, ttarget), _hpTarget(hpTarget) {

	_ttime = 0;

	// Track the player location
	p->addComponent<EntityTrackerComponent>(ttarget);
	{
		// Get the healthbar sprite
		auto bar = Resources::get<Texture>("hp_bar.png");

		_scale = hpTarget->get_components<SpriteComponent>()[0]->getSprite().getScale().x;

		// Set the healthbar background
		auto sbg = p->addComponent<SpriteComponent>();
		sbg->setTexure(bar);
		sbg->getSprite().setOrigin(Vector2f(16.f, 40.f));
		sbg->getSprite().setScale({ _scale, _scale });
		sbg->getSprite().setColor(Color::Black);

		// Set the healthbar health bar
		auto sh = p->addComponent<SpriteComponent>();
		sh->setTexure(bar);
		sh->getSprite().setOrigin(Vector2f(0.f, 40.f));
		sh->getSprite().setPosition(Vector2f(16, 0));
		sh->getSprite().setScale({ _scale, _scale });

		// If it is the player make it green
		if (hpTarget->getTags().find("player") != hpTarget->getTags().end())
		{
			sh->getSprite().setColor(Color::Green);
		}
		// Otherwise make it red
		else
		{
			sh->getSprite().setColor(Color::Red);
		}
	}
}
