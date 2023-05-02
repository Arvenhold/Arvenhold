#include "scene_menu.h"
#include "../arvenhold.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include <system_resources.h>
using namespace std::filesystem;

using namespace std;
using namespace sf;

// The view out the window
View views;

/// <summary>
/// Update main menu
/// </summary>
/// <param name="dt"></param>
void MenuScene::Update(const double& dt) 
{
	// Mouse is not clicked
	static bool mouse_down = false;

	// If mouse gets clicked
	if (Mouse::isButtonPressed(Mouse::Left) && !mouse_down) 
	{
		// Get position of mouse
		auto mouse_pos = Mouse::getPosition(Engine::GetWindow());

		cout << mouse_pos.x << "," << mouse_pos.y << endl;

		mouse_down = true;
		
		// If mouse is within the column of buttons
		if (mouse_pos.x >= 814 && mouse_pos.x <= Engine::getWindowSize().x * 1104)
		{
			// If clicked on "New Game" start new game
			if (mouse_pos.y >= 560 && mouse_pos.y <= 640)
			{
				Engine::ChangeScene(&ogScene);
			}
			// If clicked on "Continue" load save game
			if (mouse_pos.y >= 680 && mouse_pos.y <= 760)
			{

			}
			// If clicked on "Settings" go to settings
			if (mouse_pos.y >= 800 && mouse_pos.y <= 880)
			{

			}
			// If clicked on "Exit" exit game
			if (mouse_pos.y >= 920 && mouse_pos.y <= 1000)
			{
				Engine::GetWindow().close();
			}
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

/// <summary>
/// Render main menu
/// </summary>
void MenuScene::Render() 
{
	Scene::Render();
}

/// <summary>
/// Load main menu
/// </summary>
void MenuScene::Load() 
{
	// Is loading
	cout << " Scene Menu Load" << endl;

	// Make background and put it in the middle of the screen
	auto background = makeEntity();
	//background->setPosition({ 0, 40 });
	{
		auto s = background->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("mainmenu.png"));
		s->getSprite().setOrigin({ 0,80 });
		s->getSprite().setScale({ 2,2 });
	}

	// Make title of the game
	auto title = makeEntity();
	{
		auto t = title->addComponent<TextComponent>("Arvenhold");

		t->getText()->setCharacterSize(192);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 180 });
	}

	// Create buttons
	for (int i = 0; i < 4; i++)
	{
		auto btn = makeEntity();

		btn->setPosition({ 960.0f, (600.0f + (i * 120.0f))});
		auto s = btn->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("button.png"));
		s->getSprite().setOrigin({ 120,40 });
		s->getSprite().setScale({ 1.2f,1 });

		// For "Continue" button, if no save to load, make it darker
		if (i == 1)
		{
			s->getSprite().setColor(Color(50, 50, 50));
		}
	}

	// Create "New Game" text
	auto start = makeEntity();
	{

		auto t = start->addComponent<TextComponent>("New Game");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 590});
	}

	// Create "Continue" text
	auto contin = makeEntity();
	{
		auto t = contin->addComponent<TextComponent>("Continue");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });

		// If no save to load
		if (true)
		{
			// Set button text darker
			t->getText()->setFillColor(Color(130, 130, 0));
		}
		t->getText()->setPosition({ 960, 705 });
	}

	// Create "Settings" text
	auto settings = makeEntity();
	{
		auto t = settings->addComponent<TextComponent>("Settings");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 830 });
	}

	// Create "Exit" text
	auto exit = makeEntity();
	{
		auto t = exit->addComponent<TextComponent>("Exit");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 945 });
	}
	
	// Set view position
	views.reset(FloatRect({ 0, 0 }, { 1920, 1080 }));

	// Set view
	Engine::GetWindow().setView(views);

	// Loaded correctly!
	setLoaded(true);
}

/// <summary>
/// Unload main menu
/// </summary>
void MenuScene::UnLoad()
{
	Scene::UnLoad();
}
