#include "scene_dungeon.h"
#include <LevelSystem.h>
#include "../arvenhold.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

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
	player = makeEntity();
	


	/*roomSpriteSheet = Resources::get<sf::Texture>("dungeon_tiles.png");

	wizardSprite = Resources::get<sf::Texture>("wizard.png");*/

	ls::generateDungeon(10);


	setLoaded(true);
	//_ents.list.push_back(player);
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