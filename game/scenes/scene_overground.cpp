#include "scene_overground.h"
#include "../components/cmp_sprite.h"
#include <system_resources.h>
#include "../components/cmp_player_physics.h"
#include "../arvenhold.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

View ogView;

void OverGroundScene::Update(const double& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(60)))
	{
		Engine::ChangeScene(&menuScene);
	}
	else
	{
		if (player->getPosition().x > 850 && player->getPosition().x < 1060 && player->getPosition().y < 80)
		{
			Engine::ChangeScene(&dungeonScene);
		}
		else
		{
			player->update(dt);
			Scene::Update(dt);
			ogView.setCenter(player.get()->getPosition());
			Engine::GetWindow().setView(ogView);
		}
	}
}

void OverGroundScene::Render()
{
	Scene::Render();
}

void OverGroundScene::Load()
{

	cout << " Scene Dungeon Load" << endl;

	auto ground = makeEntity();
	//ground->setPosition({ Engine::getWindowSize().x * 0.5f, 0.0f });

	{
		auto s = ground->addComponent<SpriteComponent>();
		s->setTexure(Resources::get<Texture>("overworld.png"));
		s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
		s->getSprite().setScale({ 2, 2 });
	}

	{
		b2PolygonShape Shape;

		b2Vec2 vertices[4];
		vertices[0].Set(-1.0f, 5.0f);
		vertices[1].Set(-1.0f, -60.0f);
		vertices[2].Set(0.0f, -60.0f);
		vertices[3].Set(0.0f, 5.0f);

		Shape.Set(vertices, 4);

		ground->addComponent<PhysicsComponent>(false, Shape);
	}
	{
		b2PolygonShape Shape;

		b2Vec2 vertices[4];
		vertices[0].Set(0.0f, 0.0f);
		vertices[1].Set(0.0f, -1.0f);
		vertices[2].Set(100.0f, -1.0f);
		vertices[3].Set(100.0f, 0.0f);

		Shape.Set(vertices, 4);

		ground->addComponent<PhysicsComponent>(false, Shape);
	}
	{
		b2PolygonShape Shape;

		b2Vec2 vertices[4];
		vertices[0].Set(66.3f, 5.0f);
		vertices[1].Set(66.3f, -60.0f);
		vertices[2].Set(67.3f, -60.0f);
		vertices[3].Set(67.3f, 5.0f);

		Shape.Set(vertices, 4);

		ground->addComponent<PhysicsComponent>(false, Shape);
	}
	{
		b2PolygonShape Shape;

		b2Vec2 vertices[4];
		vertices[0].Set(-1.0f, -50.0f);
		vertices[1].Set(-1.0f, -51.0f);
		vertices[2].Set(70.0f, -50.0f);
		vertices[3].Set(70.0f, -51.0f);

		Shape.Set(vertices, 4);

		ground->addComponent<PhysicsComponent>(false, Shape);
	}

	player = makeEntity();
	player->setPosition({ 960, 340 });

	auto s = player->addComponent<SpriteComponent>();
	s->setTexure(Resources::get<Texture>("wizard.png"));
	s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
	s->getSprite().setScale({ 2, 2 });


	b2PolygonShape Shape;

	b2Vec2 vertices[4];
	vertices[0].Set(-1.0f, -1.0f);
	vertices[1].Set(0.0f, -2.0f);
	vertices[2].Set(1.0f, -1.0f);
	vertices[3].Set(0.0f, 0.0f);

	Shape.Set(vertices, 4);

	player->addComponent<PlayerPhysicsComponent>(Shape);

	auto trees = makeEntity();
	//trees->setPosition({ Engine::getWindowSize().x * 0.5f, 0.0f });

	{
		auto s = trees->addComponent<SpriteComponent>();
		s->setTexure(Resources::get<Texture>("overworld_trees.png"));
		s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
		s->getSprite().setScale({ 2, 2 });
	}

	ogView.reset(FloatRect({ 0, 0 }, { 1920, 1080 }));

	Engine::GetWindow().setView(ogView);

	setLoaded(true);
}

void OverGroundScene::UnLoad()
{
	player.reset();
	Scene::UnLoad();
}
