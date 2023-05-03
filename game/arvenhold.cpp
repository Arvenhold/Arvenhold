#include "arvenhold.h"
#include "engine.h"
#include "filehandling.h"
//#include <SFML/Audio/SoundBuffer.hpp>


using namespace std;
using namespace sf;

// Scenes
DungeonScene dungeonScene;
MenuScene menuScene;
OverGroundScene ogScene;
SettingsScene sScene;

// Sindow size
int gameWidth;
int gameHeight;

// Player sfx
shared_ptr<Sound> pHit;
shared_ptr<Sound> pCast;
shared_ptr<Sound> pDeath;

// Explosions make sound
shared_ptr<Sound> explode;

// Enemy sfx
shared_ptr<Sound> eHit;
shared_ptr<Sound> eCast;
shared_ptr<Sound> eShoot;
shared_ptr<Sound> eDeath;

// Start the damn thing
int main() {

	/*pHit.setBuffer(*Resources::load<SoundBuffer>(""));
	pCast.setBuffer(*Resources::load<SoundBuffer>(""));
	pDeath.setBuffer(*Resources::load<SoundBuffer>(""));
	explode.setBuffer(*Resources::load<SoundBuffer>(""));
	eHit.setBuffer(*Resources::load<SoundBuffer>(""));
	eCast.setBuffer(*Resources::load<SoundBuffer>(""));
	eDeath.setBuffer(*Resources::load<SoundBuffer>(""));*/

	FileHandler::load(gameHeight, gameWidth);

	Engine::Start(gameWidth, gameHeight, "Arvenhold", &menuScene);

	FileHandler::save(gameHeight, gameWidth);

}
