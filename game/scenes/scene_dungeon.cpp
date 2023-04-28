#include "scene_dungeon.h"
#include <LevelSystem.h>
#include "../arvenhold.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"
#include <system_resources.h>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

View view;

Vector2f startPos;

vector<shared_ptr<Entity>> floors;

vector<Vector2f> pillarPos;

void DungeonScene::Update(const double& dt) 
{
	if (Keyboard::isKeyPressed(Keyboard::Tab)) 
	{
		/*view.setCenter({ Engine::getWindowSize().x * 0.5f, Engine::getWindowSize().y * 0.5f });
		Engine::GetWindow().setView(view);*/
		Engine::ChangeScene(&menuScene);
	}
	//player->Update(dt);
	Scene::Update(dt);
	view.setCenter(player.get()->getPosition());
	Engine::GetWindow().setView(view);
}

void DungeonScene::Load() 
{

	cout << " Scene Dungeon Load" << endl;

	auto t = ls::generateDungeon(10);

	generateDungeonEntities(t);
	player = makeEntity();
	
	player->setPosition(startPos);

	auto s = player->addComponent<SpriteComponent>();
	s->setTexure(Resources::get<Texture>("wizard.png"));
	s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
	s->getSprite().setScale({ 2, 2 });
	//s->getSprite().setTextureRect(sf::IntRect(Vector2(16, 16), Vector2(32, 32)));

	

	view.reset(FloatRect({ 100, 100 }, { 1920, 1080 }));

	Engine::GetWindow().setView(view);

	setLoaded(true);
}

void DungeonScene::generateDungeonEntities(vector<int> t)
{
	auto text = Resources::get<Texture>("dungeon_tiles.png");

	for (int i = 0; i < 135; i++)
	{
		for (int j = 0; j < 135; j++)
		{
			if (t[i * 135 + j] != -1)
			{
				auto tile = makeEntity();

				tile->setPosition(Vector2f(j * 128, i * 128));

				if (t[i * 135 + j] == 84)
				{
					startPos = Vector2f(j * 128, (i-1) * 128);
				}

				auto s = tile->addComponent<SpriteComponent>();
				s->setTexure(text);
				s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));

				auto xpos = t[i * 135 + j] % 12;
				auto ypos = t[i * 135 + j] / 12;
				s->getSprite().setTextureRect(sf::IntRect(Vector2(xpos * 64, ypos * 64), Vector2(64, 64)));
				s->getSprite().setScale({ 2, 2 });
			}
		}
	}
}

void DungeonScene::UnLoad()
{
	floors.clear();
	Scene::UnLoad();
}

void DungeonScene::Render() {

	//Renderer::queue(&text);
	//ls::Render(Engine::GetWindow());
	//player->Render();
	Scene::Render();
}