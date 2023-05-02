#include "scene_settings.h"
#include "../arvenhold.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_text.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <system_resources.h>

using namespace std;
using namespace sf;

View viewSettings;
sf::Event event;

int GetButton() {
	while (Engine::GetWindow().waitEvent(event)) //.GetEvent(event))
	{
		if (event.type == Event::KeyPressed) {
			return event.key.code;
		}
	}
}

void SettingsScene::Update(const double& dt)
{
	// Mouse is not clicked
	static bool mouse_down = false;

	if (Mouse::isButtonPressed(Mouse::Left) && !mouse_down)
	{
		// Get position of mouse
		auto mouse_pos = Mouse::getPosition(Engine::GetWindow());

		mouse_down = true;


		if (mouse_pos.x >= 840 && mouse_pos.x <= 1080)
		{
			// If clicked on "Confirm" save settings
			if (mouse_pos.y >= 860 && mouse_pos.y <= 940)
			{


				// Save settings


				Engine::ChangeScene(&menuScene);
			}
		}

		else 
		{
			// If mouse is within the row of buttons
			if (mouse_pos.y >= 183 && mouse_pos.y <=  247)
			{
				// If clicked on "720p" start new game
				if (mouse_pos.x >= 644 && mouse_pos.x <= 836)
				{
				

					// Change resolution to 1280 x 720
					gameHeight = 720;
					gameWidth = 1280;
					Engine::GetWindow().setSize(Vector2u(gameWidth, gameHeight));

				}
				// If clicked on "1080p" load save game
				if (mouse_pos.x >= 864 && mouse_pos.x <= 1056)
				{
				

					// Change resolution to 1920 x 1080
					gameHeight = 1080;
					gameWidth = 1920;
					Engine::GetWindow().setSize(Vector2u(gameWidth, gameHeight));

				}
				// If clicked on "1440p" go to settings
				if (mouse_pos.x >= 1084 && mouse_pos.x <= 1276)
				{
				

					// Change resolution to 2560 x 1440
					gameHeight = 1440;
					gameWidth = 2560;

					Engine::GetWindow().setSize(Vector2u(gameWidth, gameHeight));


				}
			}

			// If mouse is within the column of buttons
			if (mouse_pos.x >= 720 && mouse_pos.x <= 960)
			{
				// If clicked on "Up" start new game
				if (mouse_pos.y >= 348 && mouse_pos.y <= 412)
				{
					auto text = ents.find("text")[0]->get_components<TextComponent>()[0];


					// Change text to that of button

					controls[0] = GetButton();


					text->SetText(to_string(controls[0]));

					// Reset origin
					auto width = text->getText()->getLocalBounds().width / 2.f;
					auto height = text->getText()->getLocalBounds().height / 2.f;
					text->getText()->setOrigin({ width, height });
				}
				// If clicked on "Down" load save game
				if (mouse_pos.y >= 428 && mouse_pos.y <= 492)
				{
					auto text = ents.find("text")[1]->get_components<TextComponent>()[0];


					// Change text to that of button

					controls[2] = GetButton();

					text->SetText(to_string(controls[2]));

					// Reset origin
					auto width = text->getText()->getLocalBounds().width / 2.f;
					auto height = text->getText()->getLocalBounds().height / 2.f;
					text->getText()->setOrigin({ width, height });
				}
				// If clicked on "Left" go to settings
				if (mouse_pos.y >= 508 && mouse_pos.y <= 572)
				{
					auto text = ents.find("text")[2]->get_components<TextComponent>()[0];


					// Change text to that of button

					controls[1] = GetButton();

					text->SetText(to_string(controls[1]));

					// Reset origin
					auto width = text->getText()->getLocalBounds().width / 2.f;
					auto height = text->getText()->getLocalBounds().height / 2.f;
					text->getText()->setOrigin({ width, height });
				}
				// If clicked on "Right" exit game
				if (mouse_pos.y >= 588 && mouse_pos.y <= 652)
				{
					auto text = ents.find("text")[3]->get_components<TextComponent>()[0];


					// Change text to that of button

					controls[3] = GetButton();

					text->SetText(to_string(controls[3]));

					// Reset origin
					auto width = text->getText()->getLocalBounds().width / 2.f;
					auto height = text->getText()->getLocalBounds().height / 2.f;
					text->getText()->setOrigin({ width, height });
				}
				// If clicked on "Attack" go to settings
				if (mouse_pos.y >= 668 && mouse_pos.y <= 732)
				{
					auto text = ents.find("text")[4]->get_components<TextComponent>()[0];


					// Change text to that of button

					controls[4] = GetButton();

					text->SetText(to_string(controls[4]));

					// Reset origin
					auto width = text->getText()->getLocalBounds().width / 2.f;
					auto height = text->getText()->getLocalBounds().height / 2.f;
					text->getText()->setOrigin({ width, height });
				}
				// If clicked on "Potion" exit game
				if (mouse_pos.y >= 748 && mouse_pos.y <= 812)
				{
					auto text = ents.find("text")[5]->get_components<TextComponent>()[0];


					// Change text to that of button

					controls[5] = GetButton();

					text->SetText(to_string(controls[5]));

					// Reset origin
					auto width = text->getText()->getLocalBounds().width / 2.f;
					auto height = text->getText()->getLocalBounds().height / 2.f;
					text->getText()->setOrigin({ width, height });
				}
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

void SettingsScene::Load()
{
	// Loading overground
	cout << " Scene Settings Load" << endl;

	// Make background and put it in the middle of the screen
	auto background = makeEntity();
	{
		auto s = background->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("mainmenu.png"));
		s->getSprite().setOrigin({ 0,80 });
		s->getSprite().setScale({ 2,2 });
	}

	// Menu box background
	auto menu = makeEntity();
	{
		auto sh = menu->addComponent<ShapeComponent>();
		sh->setShape<RectangleShape>(Vector2f(700, 900));
		sh->getShape().setOrigin({ 350,450 });
		sh->getShape().setFillColor({ 60,60,60 });
		menu->setPosition({ 960,540 });
	}

	auto resolution = makeEntity();
	{
		auto t = resolution->addComponent<TextComponent>("Resolution");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 120 });
	}

	// Create buttons
	for (int i = 0; i < 3; i++)
	{
		auto btn = makeEntity();

		//btn->setPosition({ 840.0f, (400.0f + (i * 120.0f)) });
		auto s = btn->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("button.png"));
		s->getSprite().setOrigin({ 120,40 });
		s->getSprite().setScale({ 0.8f,0.8f });
		btn->setPosition({ (740.0f + (i * 220.0f)), 215 });
	}

	auto _720p = makeEntity();
	{
		auto t = _720p->addComponent<TextComponent>("720p");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 740, 200 });
	}

	auto _1080p = makeEntity();
	{
		auto t = _1080p->addComponent<TextComponent>("1080p");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 205 });
	}
	auto _1440p = makeEntity();
	{
		auto t = _1440p->addComponent<TextComponent>("1440p");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 1180, 200 });
	}


	auto keybindsT = makeEntity();
	{
		auto t = keybindsT->addComponent<TextComponent>("Controls");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 280 });
	}

	// Create buttons
	for (int i = 0; i < 6; i++)
	{
		auto btn = makeEntity();

		auto s = btn->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("button.png"));
		s->getSprite().setOrigin({ 120,40 });
		s->getSprite().setScale({ 1,0.8f });
		btn->setPosition({ 840.0f, (380.0f + (i * 80.0f)) });

		auto textbox = makeEntity();

		auto sh = textbox->addComponent<ShapeComponent>();

		sh->setShape<RectangleShape>(Vector2f(240, 64));
		sh->getShape().setOrigin({ 120,32 });
		sh->getShape().setFillColor({ 200,200,200 });
		textbox->setPosition({ 1080.0f, (380.0f + (i * 80.0f)) });
	}

	auto _Up = makeEntity();
	{
		auto t = _Up->addComponent<TextComponent>("Up");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 840, 370 });
	}

	auto _Down = makeEntity();
	{
		auto t = _Down->addComponent<TextComponent>("Down");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 840, 450 });
	}
	auto _Left = makeEntity();
	{
		auto t = _Left->addComponent<TextComponent>("Left");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 840, 530 });
	}

	auto _Right = makeEntity();
	{
		auto t = _Right->addComponent<TextComponent>("Right");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 840, 610 });
	}

	auto _Spell = makeEntity();
	{
		auto t = _Spell->addComponent<TextComponent>("Attack");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 840, 690 });
	}
	auto _Potion = makeEntity();
	{
		auto t = _Potion->addComponent<TextComponent>("Potion");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 840, 770 });
	}

	auto btn = makeEntity();
	{
		auto s = btn->addComponent<SpriteComponent>();

		s->setTexure(Resources::get<Texture>("button.png"));
		s->getSprite().setOrigin({ 120,40 });
		btn->setPosition({ 960.0f, 900 });
	}
	auto confirm = makeEntity();
	{
		auto t = confirm->addComponent<TextComponent>("Confirm");

		t->getText()->setCharacterSize(48);
		t->getText()->setFillColor(Color(230, 230, 0));
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 960, 890 });
	}
	
	auto _UpT = makeEntity();
	_UpT->addTag("text");
	{
		auto t = _UpT->addComponent<TextComponent>("W");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color::Black);
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 1080, 370 });
	}

	auto _DownT = makeEntity();
	_DownT->addTag("text");
	{
		auto t = _DownT->addComponent<TextComponent>("S");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color::Black);
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 1080, 450 });
	}
	auto _LeftT = makeEntity();
	_LeftT->addTag("text");
	{
		auto t = _LeftT->addComponent<TextComponent>("A");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color::Black);
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 1080, 530 });
	}

	auto _RightT = makeEntity();
	_RightT->addTag("text");
	{
		auto t = _RightT->addComponent<TextComponent>("D");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color::Black);
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 1080, 610 });
	}

	auto _SpellT = makeEntity();
	_SpellT->addTag("text");
	{
		auto t = _SpellT->addComponent<TextComponent>("L-Click");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color::Black);
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 1080, 690 });
	}
	auto _PotionT = makeEntity();
	_PotionT->addTag("text");
	{
		auto t = _PotionT->addComponent<TextComponent>("R-Click");

		t->getText()->setCharacterSize(40);
		t->getText()->setFillColor(Color::Black);
		auto width = t->getText()->getLocalBounds().width / 2.f;
		auto height = t->getText()->getLocalBounds().height / 2.f;
		t->getText()->setOrigin({ width, height });
		t->getText()->setPosition({ 1080, 770 });
	}

	// Set view position
	viewSettings.reset(FloatRect({ 0, 0 }, { 1920, 1080 }));

	// Set view
	Engine::GetWindow().setView(viewSettings);

	// Loaded correctly!
	setLoaded(true);
}

void SettingsScene::Render()
{
	Scene::Render();
}

void SettingsScene::UnLoad()
{
	Scene::UnLoad();
}
