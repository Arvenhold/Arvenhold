#pragma once

#include "scenes/scene_menu.h"
#include "scenes/scene_dungeon.h"
#include "scenes/scene_overground.h"
#include <sfml/graphics.hpp>
#include "scenes/scene_settings.h"
#include <system_resources.h>
#include "scenes/scene_death.h"

// Scenes
extern DungeonScene dungeonScene;
extern MenuScene menuScene;
extern OverGroundScene ogScene;
extern SettingsScene sScene;
extern DeathScene dScene;

// Resolution
extern int gameWidth;
extern int gameHeight;

extern int controls[6];

extern int level;
