#pragma once

#include <ecm.h>
#include "cmp_sprite.h"

/// <summary>
/// UI element
/// </summary>
class UIComponent : public SpriteComponent {
protected:

	// Offset amount from player position
	sf::Vector2f _offset;

public:
	void update(double dt) override;
	void render() override;
	explicit UIComponent(Entity* p, sf::Vector2f offset);
	UIComponent() = delete;
};