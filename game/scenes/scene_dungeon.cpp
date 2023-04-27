#include "scene_dungeon.h"
#include <LevelSystem.h>
#include "../arvenhold.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_shape.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void DungeonScene::Update(const double& dt) 
{
	if (Keyboard::isKeyPressed(Keyboard::Tab)) 
	{
		Engine::ChangeScene(&menuScene);
	}
	//player->Update(dt);
	Scene::Update(dt);

}

void DungeonScene::Load() 
{

	cout << " Scene Dungeon Load" << endl;

	player = makeEntity();
	
	player->setPosition(Vector2f(20.0f,20.0f));

	auto s = player->addComponent<ShapeComponent>();
	s->getShape().setFillColor(Color::Magenta);
	s->getShape().setOrigin(Vector2f(25.0f, 25.0f));

	/*roomSpriteSheet = Resources::get<sf::Texture>("dungeon_tiles.png");

	wizardSprite = Resources::get<sf::Texture>("wizard.png");*/

	ls::generateDungeon(10);

	setLoaded(true);
}

void DungeonScene::UnLoad()
{
	Scene::UnLoad();
}

void DungeonScene::Render() {

	//Renderer::queue(&text);
	ls::Render(Engine::GetWindow());
	//player->Render();
	Scene::Render();
}