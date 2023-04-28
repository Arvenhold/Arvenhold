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

View views;

void MenuScene::Update(const double& dt) 
{
	static bool mouse_down = false;

	if (Mouse::isButtonPressed(Mouse::Left) && !mouse_down) {
		auto mouse_pos = Mouse::getPosition(Engine::GetWindow());
		mouse_down = true;
		
		if (mouse_pos.x >= Engine::getWindowSize().x * 0.417 && mouse_pos.x <= Engine::getWindowSize().x * 0.568)
		{
			if (mouse_pos.y >= Engine::getWindowSize().y * 0.347 && mouse_pos.y <= Engine::getWindowSize().y * 0.421)
			{
				Engine::ChangeScene(&dungeonScene);
			}
			if (mouse_pos.y >= Engine::getWindowSize().y * 0.444 && mouse_pos.y <= Engine::getWindowSize().y * 0.519)
			{

			}
			if (mouse_pos.y >= Engine::getWindowSize().y * 0.546 && mouse_pos.y <= Engine::getWindowSize().y * 0.620)
			{

			}
			if (mouse_pos.y >= Engine::getWindowSize().y * 0.648 && mouse_pos.y <= Engine::getWindowSize().y * 0.722)
			{
				Engine::GetWindow().close();
			}
		}
	}
	if (mouse_down && !Mouse::isButtonPressed(Mouse::Left)) {
		mouse_down = false;
	}

	Scene::Update(dt);
}

void MenuScene::Render() {
	Scene::Render();
}

void MenuScene::Load() {

	cout << " Scene Menu Load" << endl;

	auto background = makeEntity();
	background->setPosition({ Engine::getWindowSize().x * 0.5f, Engine::getWindowSize().y * 0.5f });

	{
		auto s = background->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("mainmenu.png"));
		s->getSprite().setOrigin({ 430,448 });
		s->getSprite().setScale({ 2,2 });
	}

	auto title = makeEntity();

	{
		auto t = title->addComponent<TextComponent>("Arvenhold");

		t->getText()->setCharacterSize(192);
		t->getText()->setFillColor(Color(230, 230, 0));
		t->getText()->setPosition({ Engine::getWindowSize().x * 0.375f, Engine::getWindowSize().y * 0.15f });
		t->getText()->setOrigin({ 80,20 });
	}

	for (int i = 0; i < 4; i++)
	{
		auto btn = makeEntity();

		btn->setPosition({ Engine::getWindowSize().x * 0.5f, Engine::getWindowSize().y * (0.55f + (i * 0.1f)) });
		auto s = btn->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("button.png"));
		s->getSprite().setOrigin({ 48,120 });
		s->getSprite().setScale({ 1.2f,1 });

		if (i == 1)
		{
			s->getSprite().setColor(Color(50, 50, 50));
		}
	}


	auto start = makeEntity();
	{

		auto t = start->addComponent<TextComponent>("New Game");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		t->getText()->setPosition({ Engine::getWindowSize().x * 0.485f, Engine::getWindowSize().y * 0.445f });
		//t->getText()->setOrigin({ 80,20 });
	}

	auto contin = makeEntity();
	{
		auto t = contin->addComponent<TextComponent>("Continue");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));

		if (true)
		{
			t->getText()->setFillColor(Color(130, 130, 0));
		}

		t->getText()->setPosition({ Engine::getWindowSize().x * 0.5f, Engine::getWindowSize().y * 0.545f });
		//t->getText()->setOrigin({ 80,20 });
	}

	auto settings = makeEntity();
	{
		auto t = settings->addComponent<TextComponent>("Settings");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		t->getText()->setPosition({ Engine::getWindowSize().x * 0.505f, Engine::getWindowSize().y * 0.645f });
		//t->getText()->setOrigin({ 80,20 });
	}

	auto exit = makeEntity();
	{
		auto t = exit->addComponent<TextComponent>("Exit");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		t->getText()->setPosition({ Engine::getWindowSize().x * 0.52f, Engine::getWindowSize().y * 0.745f });
		//t->getText()->setOrigin({ 80,20 });
	}
	
	views.reset(FloatRect({ 100, 100 }, { 1920, 1080 }));

	Engine::GetWindow().setView(views);

	setLoaded(true);
}

void MenuScene::UnLoad()
{
	Scene::UnLoad();
}
