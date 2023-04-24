#include "entity.h"

using namespace sf;
using namespace std;

const Vector2f Entity::getPosition() {
	return _position;
}

void Entity::setPosition(const Vector2f& pos) {
	_position = pos;
}

void Entity::move(const Vector2f& pos) {
	_position += pos;
}


void Entity::Update(const double dt) {
	_shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {

}

void Entity::Render() const {
	Renderer::queue(_shape.get());
}

void EntityManager::render()
{
	for (auto e : list)
	{
		e->Render();
	}
}

void EntityManager::update(double dt)
{
	for (auto e : list)
	{
		e->Update(dt);
	}
}