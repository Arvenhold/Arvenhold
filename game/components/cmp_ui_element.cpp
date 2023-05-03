#include "cmp_ui_element.h"

using namespace sf;
using namespace std;

/// <summary>
/// Update UI element
/// </summary>
/// <param name="dt"></param>
void UIComponent::update(double dt)
{
	// Move element by offset
	getSprite().setPosition(_parent->getPosition() + _offset);
}

/// <summary>
/// Render UI element
/// </summary>
void UIComponent::render()
{
	SpriteComponent::render();
}

/// <summary>
/// UI element
/// </summary>
/// <param name="p">- Parent entity</param>
/// <param name="offset">- Offset from player</param>
UIComponent::UIComponent(Entity* p, sf::Vector2f offset) : SpriteComponent(p), _offset(offset) {}

void UITextComponent::update(double dt)
{
	// Move element by offset
	getText()->setPosition(_parent->getPosition() + _offset);
}

void UITextComponent::render()
{
	TextComponent::render();
}

UITextComponent::UITextComponent(Entity* p, string text, Vector2f offset) : TextComponent(p, text), _offset(offset) {}
