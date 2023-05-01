#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include "cmp_ui_element.h"

/// <summary>
/// Where all the magic happens
/// </summary>
class SpellComponent : public Component {
protected:

	// Spells
	void fire() const;
	void lightning() const;
	void cold() const;

	// Cooldowns
	float _firetime;
	float _lighttime;
	float _coldtime;

	// Spell radius
	float _radius;

	// Has spell been cast recently
	bool _fCast;
	bool _lCast;
	bool _cCast;

	// Spell UI sprites
	sf::Sprite* _fireS;
	sf::Sprite* _lightS;
	sf::Sprite* _frostS;

public:
	void update(double dt) override;
	void render() override {}
	explicit SpellComponent(Entity* p, float radius, sf::Sprite* fire, sf::Sprite* light, sf::Sprite* cold);
	SpellComponent() = delete;
};