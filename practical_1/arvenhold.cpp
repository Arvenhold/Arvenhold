#include "arvenhold.h"

using namespace std;
using namespace sf;

void MenuScene::update(double dt) {
	/*if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}*/
	Scene::update(dt);
	text.setString("Arvenhold");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	//Set up the text element here!
}

void GameScene::respawn()
{
}

void GameScene::update(double dt) {
	/*if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}*/
	Scene::update(dt);
	
}

//void GameScene::load() {
//	...
//		auto player = ...
//		_ents.list.push_back(player);
//	for (4 ghosts) {
//		auto ghost = ...
//			_ents.list.push_back(ghost);
//	}
//	...
//}

void GameScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void GameScene::load() {
	//Set up the text element here!
}
