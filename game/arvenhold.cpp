#include "arvenhold.h"
#include "engine.h"

using namespace std;

DungeonScene dungeonScene;
MenuScene menuScene;
//OverGroundScene ogScene;

int main() {

	Engine::Start(1920, 1080, "Arvenhold", &menuScene);
}
