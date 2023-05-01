#include "scene_overground.h"
#include "../components/cmp_sprite.h"
#include <system_resources.h>
#include "../components/cmp_player_physics.h"
#include "../arvenhold.h"

using namespace std;
using namespace sf;

// Create player
static shared_ptr<Entity> player;

// Overground view
View ogView;

/// <summary>
/// Update overground
/// </summary>
/// <param name="dt"></param>
void OverGroundScene::Update(const double& dt)
{
	// If pressed "Tab" go back to main menu
	if (Keyboard::isKeyPressed(Keyboard::Key(60)))
	{
		Engine::ChangeScene(&menuScene);
	}
	else
	{
		// If player enters cave go to dungoen
		if (player->getPosition().x > 850 && player->getPosition().x < 1060 && player->getPosition().y < 80)
		{
			Engine::ChangeScene(&dungeonScene);
		}
		else
		{
			// Update scene
			player->update(dt);
			Scene::Update(dt);
			ogView.setCenter(player.get()->getPosition());
			Engine::GetWindow().setView(ogView);
		}
	}
}

/// <summary>
/// Render scene
/// </summary>
void OverGroundScene::Render()
{
	Scene::Render();
}

/// <summary>
/// Load the overground, definitely isn't supposed to be called the overworld
/// </summary>
void OverGroundScene::Load()
{
	// Loading overground
	cout << " Scene Dungeon Load" << endl;

	// Make the ground
	auto ground = makeEntity();
	{
		auto s = ground->addComponent<SpriteComponent>();
		s->setTexure(Resources::get<Texture>("overworld.png"));
		s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
		s->getSprite().setScale({ 2, 2 });
	}

	// Left wall of area
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

	// Bottom wall of area
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

	// Right wall of area
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
	// Top wall of area
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

	// Make the player
	player = makeEntity();
	player->setPosition({ 960, 340 });

	// Give them a sprite
	{
		auto s = player->addComponent<SpriteComponent>();
		s->setTexure(Resources::get<Texture>("wizard.png"));
		s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
		s->getSprite().setScale({ 2, 2 });
	}

	// Give them a physical body
	{
		b2PolygonShape Shape;
		b2Vec2 vertices[4];
		vertices[0].Set(-1.0f, -1.0f);
		vertices[1].Set(0.0f, -2.0f);
		vertices[2].Set(1.0f, -1.0f);
		vertices[3].Set(0.0f, 0.0f);
		Shape.Set(vertices, 4);
		player->addComponent<PlayerPhysicsComponent>(Shape);
	}

	// The forest must grow
	auto trees = makeEntity();
	{
		auto s = trees->addComponent<SpriteComponent>();
		s->setTexure(Resources::get<Texture>("overworld_trees.png"));
		s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
		s->getSprite().setScale({ 2, 2 });
	}

	// Set the view correctly
	ogView.reset(FloatRect({ 0, 0 }, { 1920, 1080 }));
	Engine::GetWindow().setView(ogView);

	// Overground is loaded
	setLoaded(true);
}

/// <summary>
/// Unload overground
/// </summary>
void OverGroundScene::UnLoad()
{
	player.reset();
	Scene::UnLoad();
}
