#include "scene_dungeon.h"
#include <LevelSystem.h>
#include "../arvenhold.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_enemy_ai.h"
#include <system_resources.h>
#include "../components/cmp_ai_steering.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

View view;

Vector2f startPos;

vector<Vector2f> floors;

vector<Vector2f> pillarPos;

int level;

void DungeonScene::Update(const double& dt) 
{
	if (Keyboard::isKeyPressed(Keyboard::Key(60))) 
	{
		Engine::ChangeScene(&menuScene);
	}
	else
	{
		player->update(dt);
		Scene::Update(dt);
		view.setCenter(player.get()->getPosition());
		Engine::GetWindow().setView(view);
	}
}

void DungeonScene::Load() 
{

	cout << " Scene Dungeon Load" << endl;

	pillarPos.clear();
	floors.clear();

	level = 1;

	

	auto t = ls::generateDungeon(level);
	
	generateDungeonEntities(t);

	player = makeEntity();
	player->setPosition(startPos);

	generateEnemies();

	auto s = player->addComponent<SpriteComponent>();
	s->setTexure(Resources::get<Texture>("wizard.png"));
	s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
	s->getSprite().setScale({ 2, 2 });
	//s->getSprite().setTextureRect(sf::IntRect(Vector2(16, 16), Vector2(32, 32)));

	b2PolygonShape Shape;

	b2Vec2 vertices[4];
	vertices[0].Set(-1.0f, -1.0f);
	vertices[1].Set(0.0f, -2.0f);
	vertices[2].Set(1.0f, -1.0f);
	vertices[3].Set(0.0f, 0.0f);

	Shape.Set(vertices, 4);

	player->addComponent<PlayerPhysicsComponent>(Shape);

	for (int i = 0; i < pillarPos.size(); i++)
	{
		auto pillar = makeEntity();

		pillar->setPosition(pillarPos[i]);

		auto s = pillar->addComponent<SpriteComponent>();
		s->setTexure(Resources::get<Texture>("pillar.png"));
		s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
		s->getSprite().setScale({ 2, 2 });
	}

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

				if (t[i * 135 + j] == 95)
				{
					pillarPos.push_back(Vector2f(j * 128, (i - 1) * 128));
				}

				auto s = tile->addComponent<SpriteComponent>();
				s->setTexure(text);
				s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));

				auto xpos = t[i * 135 + j] % 12;
				auto ypos = t[i * 135 + j] / 12;
				s->getSprite().setTextureRect(sf::IntRect(Vector2(xpos * 64, ypos * 64), Vector2(64, 64)));
				s->getSprite().setScale({ 2, 2 });

				if (t[i * 135 + j] != 72 && t[i * 135 + j] != 73 && t[i * 135 + j] != 74 && t[i * 135 + j] != 84 && t[i * 135 + j] != 85 && t[i * 135 + j] != 86 && t[i * 135 + j] != 118 && t[i * 135 + j] != 119)
				{
					b2PolygonShape Shape;

					Shape.Set(_polygons[t[i * 135 + j]], 6);

					tile->addComponent<PhysicsComponent>(false, Shape);
				}
				else
				{
					floors.push_back(Vector2f(j * 128, (i - 1) * 128));
				}
			}
		}
	}
}

void DungeonScene::generateEnemies()
{
	srand(time(NULL));

	for (int i = 0; i < floors.size(); i++)
	{
		if (length(floors[i] - startPos) > 960.0)
		{

			int spawnChance = (rand() % 100) + 1;

			if (spawnChance <= (10 + 3 * level))
			{
				auto enemy = makeEntity();

				enemy->setPosition({ floors[i].x , floors[i].y + 64 });

				int enemyType = (rand() % 100) + 1;

				auto s = enemy->addComponent<SpriteComponent>();

				if (enemyType < (100 - level * 5))		s->setTexure(Resources::get<Texture>("skelly.png"));
				else if (enemyType < (100 - level * 3))		s->setTexure(Resources::get<Texture>("skelly-warrior.png"));
				else if (enemyType < (100 - level * 1.5f))	s->setTexure(Resources::get<Texture>("skelly-ranger.png"));
				else									s->setTexure(Resources::get<Texture>("skelly-wizard.png"));

				s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
				s->getSprite().setScale({ 2, 2 });

				b2PolygonShape Shape;

				b2Vec2 vertices[4];
				vertices[0].Set(-1.0f, -1.0f);
				vertices[1].Set(0.0f, -2.0f);
				vertices[2].Set(1.0f, -1.0f);
				vertices[3].Set(0.0f, 0.0f);

				Shape.Set(vertices, 4);

				enemy->addComponent<SteeringComponent>(player.get(), Shape);
			}
		}
	}
}

void DungeonScene::UnLoad()
{
	player.reset();
	floors.clear();
	pillarPos.clear();
	Scene::UnLoad();
}

void DungeonScene::Render() {

	//Renderer::queue(&text);
	//ls::Render(Engine::GetWindow());
	//player->Render();
	Scene::Render();
}

// Collision polygons
b2Vec2 DungeonScene::_polygons[120][6] =
{
	// Row 1
	{{ 0.5f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{ 0.0f,-0.5f},{ 0.0f,-2.1f}}, // 0
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 1
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 2
	{{-2.1f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f,-0.5f},{-0.5f, 0.0f},{-2.1f, 0.0f}}, // 3
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 4
	{{ 0.5f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{ 0.0f,-0.5f},{ 0.0f,-2.1f}}, // 5
	{{-2.1f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f,-0.5f},{-0.5f, 0.0f},{-2.1f, 0.0f}}, // 6
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 7
	{{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 2.1f}}, // 8
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 9
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 10
	{{-0.5f, 2.1f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 11
	// Row 2
	{{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 2.1f}}, // 12
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 13
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 14
	{{-0.5f, 2.1f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 15
	{{-2.1f,-0.5f},{-0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 16
	{{-2.1f,-2.1f},{ 0.5f, 0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 0.5f},{-2.1f, 0.0f}}, // 17
	{{-0.5f, 2.1f},{-0.5f, 0.5f},{ 2.1f,-2.1f},{ 2.1f, 0.0f},{ 0.5f, 0.5f},{ 0.5f, 2.1f}}, // 18
	{{-0.5f, 2.1f},{-0.5f, 0.5f},{ 0.5f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 2.1f}}, // 19
	{{ 2.1f, 2.1f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f}}, // 20
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 21
	{{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 22
	{{-2.1f, 2.1f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f},{-0.5f, 2.1f}}, // 23
	// Row 3
	{{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 2.1f}}, // 24
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 25
	{{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 26
	{{-0.5f, 2.1f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 27
	{{-2.1f,-0.5f},{-0.5f,-0.5f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 0.5f},{-2.1f, 0.0f}}, // 28
	{{-2.1f,-2.1f},{ 0.0f, 0.0f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 0.5f},{-2.1f, 0.0f}}, // 29
	{{-2.1f, 2.1f},{ 0.0f, 0.0f},{ 2.1f,-2.1f},{ 2.1f, 0.0f},{ 0.5f, 0.5f},{ 0.5f, 2.1f}}, // 30
	{{-2.1f, 2.1f},{ 0.5f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.5f, 0.5f},{ 0.5f, 2.1f}}, // 31
	{{-2.1f,-2.1f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f},{-2.1f,-0.5f}}, // 32
	{{-2.1f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f},{-2.1f,-0.5f}}, // 33
	{{-2.1f, 2.1f},{-0.5f,-0.5f},{ 2.1f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 2.1f}}, // 34
	{{-0.5f, 2.1f},{-0.5f,-0.5f},{ 2.1f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 2.1f}}, // 35
	// Row 4
	{{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f}}, // 36
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 37
	{{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 38
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 39
	{{ 2.1f,-2.1f},{-0.5f, 0.5f},{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f}}, // 40
	{{ 2.1f,-2.1f},{ 0.0f, 0.0f},{-2.1f, 2.1f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f}}, // 41
	{{ 2.1f, 2.1f},{ 0.0f, 0.0f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 0.0f}}, // 42
	{{ 2.1f, 0.5f},{ 0.5f, 0.5f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 0.0f}}, // 43
	{{-2.1f, 2.1f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f}}, // 44
	{{-2.1f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f},{-2.1f,-0.5f}}, // 45
	{{-2.1f,-0.5f},{ 2.1f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 46
	{{ 2.1f, 2.1f},{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 47
	// Row 5
	{{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f}}, // 48
	{{ 2.1f,-2.1f},{ 0.5f, 2.1f},{-0.5f, 2.1f},{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f,-2.1f}}, // 49
	{{ 2.1f, 0.5f},{ 0.5f, 2.1f},{-0.5f, 2.1f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 50
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 51
	{{ 0.5f,-2.1f},{ 0.5f,-0.5f},{-0.5f, 0.5f},{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f,-2.1f}}, // 52
	{{ 0.5f,-2.1f},{ 0.5f,-0.5f},{-2.1f, 2.1f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f}}, // 53
	{{ 2.1f, 2.1f},{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 0.0f}}, // 54
	{{ 2.1f, 0.5f},{ 0.5f, 0.5f},{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 55
	{{ 2.1f,-2.1f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f}}, // 56
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 57
	{{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 58
	{{-0.5f, 2.1f},{-2.1f,-2.1f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 59
	// Row 6
	{{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.5f, 0.0f},{ 2.1f, 0.0f},{ 2.1f, 0.5f}}, // 60
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 61
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 62
	{{-0.5f, 2.1f},{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f, 0.0f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 63
	{{ 0.5f,-2.1f},{ 0.5f,-0.5f},{-0.5f, 0.5f},{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f,-2.1f}}, // 64
	{{ 0.5f,-2.1f},{ 0.5f,-0.5f},{-2.1f, 2.1f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f}}, // 65
	{{ 2.1f, 2.1f},{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 0.0f}}, // 66
	{{ 2.1f, 0.5f},{ 0.5f, 0.5f},{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 67
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 2.1f,-2.1f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f}}, // 68
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 2.1f,-2.1f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 69
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 70
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 71
	// Row 7
	{{},{},{},{},{},{}}, // 72 - Unused
	{{},{},{},{},{},{}}, // 73 - Unused
	{{},{},{},{},{},{}}, // 74 - Unused
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 75
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 76
	{{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.5f, 0.0f},{ 2.1f, 0.0f},{ 2.1f, 0.5f}}, // 77
	{{-0.5f, 2.1f},{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f, 0.0f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 78
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 79
	{{-2.1f, 2.1f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f},{-0.5f, 2.1f}}, // 80
	{{-2.1f, 2.1f},{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f, 0.0f},{ 2.1f, 0.0f},{ 2.1f, 0.5f}}, // 81
	{{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f, 0.0f},{ 2.1f, 0.0f},{ 2.1f, 0.5f},{ 2.1f, 2.1f}}, // 82
	{{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f,-0.5f},{ 0.0f,-0.5f}}, // 83
	// Row 8
	{{},{},{},{},{},{}}, // 84 - Unused
	{{},{},{},{},{},{}}, // 85 - Unused
	{{},{},{},{},{},{}}, // 86 - Unused
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 87
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 88
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 89
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 90
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 91
	{{ 2.1f, 2.1f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f}}, // 92
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 2.1f,-2.1f},{ 0.5f, 0.5f},{-2.1f, 2.1f},{-2.1f, 0.5f}}, // 93
	{{ 2.1f, 2.1f},{-0.5f, 0.5f},{-2.1f,-2.1f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 94
	{{-0.5f, 2.1f},{-0.5f, 0.5f},{ 0.0f, 0.5f},{ 0.5f, 0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f}}, // 95
	// Row 9
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 96
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 97
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f}}, // 98
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f}}, // 99
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 100
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 101
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 102
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 103
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 104
	{{-2.1f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f,-0.5f},{-0.5f, 0.0f},{-2.1f, 0.0f}}, // 105
	{{ 0.5f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{ 0.0f,-0.5f},{ 0.0f,-2.1f}}, // 106
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 107
	// Row 10
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 108
	{{-0.5f, 2.1f},{-0.5f, 0.0f},{-0.5f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.0f},{ 0.5f, 2.1f}}, // 109
	{{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 0.5f}}, // 110
	{{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 0.5f}}, // 111
	{{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 0.5f}}, // 112
	{{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 0.5f}}, // 113
	{{ 2.1f, 0.0f},{ 0.0f, 2.1f},{-0.5f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 114
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 115
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 116
	{{ 2.1f, 0.0f},{ 0.0f, 2.1f},{-0.5f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 117
	{{},{},{},{},{},{}}, // 118 - Unused
	{{},{},{},{},{},{}}  // 119 - Unused
};
