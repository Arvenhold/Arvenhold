#include "arvenhold.h"
#include "engine.h"
#include "filehandling.h"

using namespace std;

// Scenes
DungeonScene dungeonScene;
MenuScene menuScene;
OverGroundScene ogScene;

// Sindow size
int gameWidth;
int gameHeight;

// Start the damn thing
int main() {

	FileHandler::load(gameHeight, gameWidth);


	cout << gameWidth << endl;
	Engine::Start(gameWidth, gameHeight, "Arvenhold", &menuScene);

	FileHandler::save(gameHeight, gameWidth);

}
