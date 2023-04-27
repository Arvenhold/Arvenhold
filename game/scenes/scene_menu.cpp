#include "scene_menu.h"
#include "../arvenhold.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Update(const double& dt) 
{
	if (Keyboard::isKeyPressed(Keyboard::Space)) 
	{
		Engine::ChangeScene(&dungeonScene);
	}
	Scene::Update(dt);
	//text.setString("Arvenhold");
}

//void MenuScene::render() {
//	Renderer::queue(&text);
//	Scene::render();
//}

void MenuScene::Load() {
	//Set up the text element here!
	/*text.setFillColor(Color::Yellow);
	text.setString("Arvenhold!");
	text.setScale({ 2,2 });*/
}