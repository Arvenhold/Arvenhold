#include "cmp_health_bar.h"
#include <system_resources.h>
#include "cmp_sprite.h"

using namespace sf;

void HealthBarComponent::update(double dt)
{
	if (_hpTarget->is_fordeletion())
	{
		_parent->setForDelete();
	}
	else
	{
		_ttime += dt;

		auto hp = (sin(_ttime) + 1);

		EntityTrackerComponent::update(dt);

		auto hpBackground = _parent->get_components<SpriteComponent>()[0];
		auto hpBar = _parent->get_components<SpriteComponent>()[1];

		auto hpOffset = _hpTarget->getPosition() - _ttarget->getPosition();

		auto hpPos = hpBar->getSprite().getPosition();

		hpBar->getSprite().setScale(Vector2f(hp, 2.0f));
		hpBackground->getSprite().setPosition(hpOffset + hpBackground->getSprite().getPosition());
		hpBar->getSprite().setPosition(hpOffset + Vector2f(hpPos.x - 32, hpPos.y));
	}
}

bool HealthBarComponent::isTargetAlive()
{
	return _hpTarget->isAlive();
}

HealthBarComponent::HealthBarComponent(Entity* p, Entity* ttarget, Entity* hpTarget) : EntityTrackerComponent(p, ttarget), _hpTarget(hpTarget) {

	_ttime = 0;

	p->addComponent<EntityTrackerComponent>(ttarget);
	{

		auto bar = Resources::get<Texture>("hp_bar.png");

		auto sbg = p->addComponent<SpriteComponent>();
		sbg->setTexure(bar);
		sbg->getSprite().setOrigin(Vector2f(16.f, 40.f));
		sbg->getSprite().setScale({ 2, 2 });
		sbg->getSprite().setColor(Color::Black);

		auto sh = p->addComponent<SpriteComponent>();
		sh->setTexure(bar);
		sh->getSprite().setOrigin(Vector2f(0.f, 40.f));
		sh->getSprite().setPosition(Vector2f(16, 0));
		sh->getSprite().setScale({ 2, 2 });

		if (hpTarget->getTags().find("player") != hpTarget->getTags().end())
		{
			sh->getSprite().setColor(Color::Green);
		}
		else
		{
			sh->getSprite().setColor(Color::Red);
		}
	}
}
