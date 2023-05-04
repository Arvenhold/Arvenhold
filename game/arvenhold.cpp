#include "arvenhold.h"
#include "engine.h"
#include "filehandling.h"

using namespace std;
using namespace sf;

// Scenes
DungeonScene dungeonScene;
MenuScene menuScene;
OverGroundScene ogScene;
SettingsScene sScene;
DeathScene dScene;

// Sindow size
int gameWidth;
int gameHeight;

// Start the damn thing
int main() {

	FileHandler::load(gameHeight, gameWidth, level);

	Engine::Start(gameWidth, gameHeight, "Arvenhold", &menuScene);

	FileHandler::save(gameHeight, gameWidth, level);
}
