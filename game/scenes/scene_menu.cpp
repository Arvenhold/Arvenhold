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
		mouse_down = true;
		
		// If mouse is within the column of buttons
		if (mouse_pos.x >= Engine::getWindowSize().x * 0.417 && mouse_pos.x <= Engine::getWindowSize().x * 0.568)
		{
			// If clicked on "New Game" start new game
			if (mouse_pos.y >= Engine::getWindowSize().y * 0.347 && mouse_pos.y <= Engine::getWindowSize().y * 0.421)
			{
				Engine::ChangeScene(&ogScene);
			}
			// If clicked on "Continue" load save game
			if (mouse_pos.y >= Engine::getWindowSize().y * 0.444 && mouse_pos.y <= Engine::getWindowSize().y * 0.519)
			{

			}
			// If clicked on "Settings" go to settings
			if (mouse_pos.y >= Engine::getWindowSize().y * 0.546 && mouse_pos.y <= Engine::getWindowSize().y * 0.620)
			{

			}
			// If clicked on "Exit" exit game
			if (mouse_pos.y >= Engine::getWindowSize().y * 0.648 && mouse_pos.y <= Engine::getWindowSize().y * 0.722)
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
	background->setPosition({ 960, 540 });
	{
		auto s = background->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("mainmenu.png"));
		s->getSprite().setOrigin({ 430,448 });
		s->getSprite().setScale({ 2,2 });
	}

	// Make title of the game
	auto title = makeEntity();
	{
		auto t = title->addComponent<TextComponent>("Arvenhold");

		t->getText()->setCharacterSize(192);
		t->getText()->setFillColor(Color(230, 230, 0));
		t->getText()->setPosition({ 720, 162 });
		t->getText()->setOrigin({ 80,20 });
	}

	// Create buttons
	for (int i = 0; i < 4; i++)
	{
		auto btn = makeEntity();

		btn->setPosition({ 960.0f, (594.0f + (i * 108.0f))});
		auto s = btn->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("button.png"));
		s->getSprite().setOrigin({ 48,120 });
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
		t->getText()->setPosition({ 931, 481});
	}

	// Create "Continue" text
	auto contin = makeEntity();
	{
		auto t = contin->addComponent<TextComponent>("Continue");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));

		// If no save to load
		if (true)
		{
			// Set button text darker
			t->getText()->setFillColor(Color(130, 130, 0));
		}
		t->getText()->setPosition({ 960, 589 });
	}

	// Create "Settings" text
	auto settings = makeEntity();
	{
		auto t = settings->addComponent<TextComponent>("Settings");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		t->getText()->setPosition({ 970, 697 });
	}

	// Create "Exit" text
	auto exit = makeEntity();
	{
		auto t = exit->addComponent<TextComponent>("Exit");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		t->getText()->setPosition({ 998, 805 });
	}
	
	// Set view position
	views.reset(FloatRect({ 100, 100 }, { 1920, 1080 }));

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
