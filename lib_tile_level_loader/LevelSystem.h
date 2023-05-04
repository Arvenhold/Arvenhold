#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "../lib_maths/maths.h"
#include "../engine/system_renderer.h"

#define ls LevelSystem

/// <summary>
/// Semi-pseudo-random dungeon generation
/// </summary>
class LevelSystem {
public:

    // Dungeon blueprint generator
    static std::vector<int> generateDungeon(int level);

private:
    LevelSystem() = delete;
    ~LevelSystem() = delete;

    static int _rooms[16][4][81];
    static int _specialRooms[11][81];
    static int _clusters[15][4][9];
    static int _specialClusters[2][9];
    static int _dungeonLayouts[10][5][25];
};