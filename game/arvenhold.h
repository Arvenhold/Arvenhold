#pragma once

#include "scenes/scene_menu.h"
#include "scenes/scene_dungeon.h"
#include "scenes/scene_overground.h"
#include <sfml/graphics.hpp>
#include "scenes/scene_settings.h"
#include <system_resources.h>
//#include <SFML/Audio/Sound.hpp>

// Scenes
extern DungeonScene dungeonScene;
extern MenuScene menuScene;
extern OverGroundScene ogScene;
extern SettingsScene sScene;

// Player sfx
extern std::shared_ptr<sf::Sound> pHit;
extern std::shared_ptr<sf::Sound> pCast;
extern std::shared_ptr<sf::Sound> pDeath;

// Explosions make sound
extern std::shared_ptr<sf::Sound> explode;

// Enemy sfx
extern std::shared_ptr<sf::Sound> eHit;
extern std::shared_ptr<sf::Sound> eCast;
extern std::shared_ptr<sf::Sound> eShoot;
extern std::shared_ptr<sf::Sound> eDeath;

// Resolution
extern int gameWidth;
extern int gameHeight;

extern int controls[6];

