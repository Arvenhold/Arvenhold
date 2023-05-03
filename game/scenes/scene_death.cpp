#include "scene_death.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include <system_resources.h>
#include "../arvenhold.h"

using namespace std;
using namespace sf;

float sDRatio;

// The view out the window
View viewD;

void DeathScene::Update(const double& dt)
{

	// If pressed "A" load save game
	if (Joystick::isButtonPressed(0, 0))
	{
		Engine::ChangeScene(&dungeonScene);
	}

	// Mouse is not clicked
	static bool mouse_down = false;

	sDRatio = (1.0f * Engine::getWindowSize().y) / 1080.0f;

	// If mouse gets clicked
	if (Mouse::isButtonPressed(Mouse::Left) && !mouse_down)
	{
		// Get position of mouse
		auto mouse_pos = Mouse::getPosition(Engine::GetWindow());

		cout << mouse_pos.x << "," << mouse_pos.y << endl;

		mouse_down = true;

		// If clicked on "Continue" load save game
		if ((mouse_pos.x >= 814 * sDRatio && mouse_pos.x <= 1104 * sDRatio && mouse_pos.y >= 680 * sDRatio && mouse_pos.y <= 760 * sDRatio))
		{
			Engine::ChangeScene(&dungeonScene);
		}
	}

	// If mouse not clicked, set mouse not clicked
	if (mouse_down && !Mouse::isButtonPressed(Mouse::Left))
	{
		mouse_down = false;
	}

	// Update scene
	Scene::Update(dt);
}

void DeathScene::Load()
{
	// Yes, this is the dungeon scene
	cout << " Scene Death Load" << endl;

	//
	sDRatio = (1.0f * gameHeight) / 1080.0f;

	// Tell the player they are dead
	auto title = makeEntity();
	{
		auto t = title->addComponent<TextComponent>("You died");
		t->getText()->setCharacterSize(192);
		t->getText()->setFillColor(Color::Red);
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 340 });
	}

	// Make a continue button
	auto btn = makeEntity();
	btn->setPosition(Vector2f(960, 720));
	{
		auto s = btn->addComponent<SpriteComponent>();
		s->setTexure(Resources::get<Texture>("button.png"));
		s->getSprite().setOrigin({ 120,40 });
		s->getSprite().setScale({ 1.2f,1 });
	}

	// Create "Continue" text
	auto start = makeEntity();
	{
		auto t = start->addComponent<TextComponent>("Continue");
		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 705 });
	}

	// Set view position
	viewD.reset(FloatRect({ 0, 0 }, { 1920, 1080 }));

	// Set view
	Engine::GetWindow().setView(viewD);

	// Loaded correctly!
	setLoaded(true);
}

void DeathScene::Render()
{
	Scene::Render();
}

void DeathScene::UnLoad()
{
	Scene::UnLoad();
}
