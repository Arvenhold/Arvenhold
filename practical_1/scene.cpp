#include "scene.h"

void Scene::update(double dt)
{
	_ents.update(dt);
}

void Scene::render()
{
	_ents.render();
	Renderer::render();
}
