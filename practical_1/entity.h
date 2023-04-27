#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "system_renderer.h"


class Entity {
protected:
	std::unique_ptr<sf::Shape> _shape;
	sf::Vector2f _position;
	Entity(std::unique_ptr<sf::Shape> shape);

public:
	Entity() = delete;
	virtual ~Entity() = default;

	virtual void Update(const double dt);
	void Render() const;

	const sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& pos);
	void move(const sf::Vector2f& pos);

};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
};