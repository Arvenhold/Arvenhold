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

void SettingsScene::Update(const double& dt)
{

}

void SettingsScene::Load()
{
	// Loading overground
	cout << " Scene Settings Load" << endl;





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
