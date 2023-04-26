#include "arvenhold.h"

using namespace std;
using namespace sf;

shared_ptr<Scene> gameScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> activeScene;

shared_ptr<Player> player(new Player());

//Texture roomSpriteSheet;
//Texture wizardSprite;

void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Arvenhold");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	//Set up the text element here!
	text.setFillColor(Color::Yellow);
	text.setString("Arvenhold!");
	text.setScale({ 2,2 });
}

void GameScene::respawn()
{
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	//player->Update(dt);
	Scene::update(dt);
	
}

void GameScene::load() {
	/*if (!roomSpriteSheet.loadFromFile("res/img/dungeon_tiles.png"))
    {
        cerr << "Failed to load spritesheet!" << endl;
    }
    if (!wizardSprite.loadFromFile("res/img/wizard.png"))
    {
        cerr << "Failed to load spritesheet!" << endl;
    }*/
	ls::generateDungeon(10);
	_ents.list.push_back(player);
}

void GameScene::render() {

	Renderer::queue(&text);
	ls::Render();
	player->Render();
	Scene::render();
}