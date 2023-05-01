#pragma once

#include "scenes/scene_menu.h"
#include "scenes/scene_dungeon.h"
#include "scenes/scene_overground.h"
#include <sfml/graphics.hpp>

// Scenes
extern DungeonScene dungeonScene;
extern MenuScene menuScene;
extern OverGroundScene ogScene;

// Resolution
extern int gameWidth;
extern int gameHeight;

extern int controls[6];

