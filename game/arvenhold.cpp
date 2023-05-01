#include "arvenhold.h"
#include "engine.h"
#include "filehandling.h"

using namespace std;

DungeonScene dungeonScene;
MenuScene menuScene;
OverGroundScene ogScene;

int gameWidth;
int gameHeight;

int main() {

	FileHandler::load(gameHeight, gameWidth);

	Engine::Start(gameWidth, gameHeight, "Arvenhold", &menuScene);

	FileHandler::save(gameHeight, gameWidth);

}
