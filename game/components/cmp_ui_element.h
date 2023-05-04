#pragma once

#include <ecm.h>
#include "cmp_sprite.h"
#include "cmp_text.h"

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

/// <summary>
/// UI element
/// </summary>
class UITextComponent : public TextComponent {
protected:

	// Offset amount from player position
	sf::Vector2f _offset;

public:
	void update(double dt) override;
	void render() override;
	explicit UITextComponent(Entity* p, std::string text, sf::Vector2f offset);
	UITextComponent() = delete;
};