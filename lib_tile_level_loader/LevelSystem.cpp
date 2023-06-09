﻿#include "LevelSystem.h"
#include <fstream>
#include <iostream>

// ########################################
// ## SEMI-PSEUDO-RANDOM GENERATION FUN! ##
// ########################################

using namespace std;
using namespace sf;

/// <summary>
/// Generate dungeon layout
/// </summary>
/// <param name="level">- current dungeon level</param>
/// <returns>Dungeon blueprint</returns>
std::vector<int> LevelSystem::generateDungeon(int level)
{
	// Create the blueprint vector
	std::vector<int> tils;

	// Make sure it is empty
	tils.clear();

	// Random number time
	srand(time(NULL));

	// Offset for dungeon selection
	int dungOffset = rand() % 5;

	// Select layout
	int* layout = _dungeonLayouts[level-1][dungOffset];

	// Current cluster
	int* tCluster;

	// For each row of clusters in the dungeon
	for (int dRow = 0; dRow < 5; dRow++)
	{
		// Make a cluster offset
		int cOffset = rand() % 12;

		// For each row of rooms in the cluster
		for (int cRow = 0; cRow < 3; cRow++)
		{
			// Make a room offset
			int offset = rand() % 10;

			// For each row of tiles in the room
			for (int rRow = 0; rRow < 9; rRow++)
			{
				// For each column of clusters in the dungeon
				for (int dCol = 0; dCol < 5; dCol++)
				{
					// If it is a special cluster use that
					if (layout[dCol + dRow * 5] > 14)
					{
						tCluster = _specialClusters[layout[dCol + dRow * 5] - 15];
					}
					// Otherwise randomly choose a variety of that cluster
					else if (layout[dCol + dRow * 5] > -1)
					{
						int rando = ((dCol + dRow + cOffset) % 4);
						tCluster = _clusters[layout[dCol + dRow * 5]][rando];
					}					

					// For each column of rooms in the cluster
					for (int cCol = 0; cCol < 3; cCol++)
					{
						// Select Which room variety to choose from
						int rando = ((cCol + cRow + offset) % 4);

						// For each column of tiles in the room
						for (int rCol = 0; rCol < 9; rCol++)
						{
							// If the cluster was special
							if (layout[dCol + dRow * 5] > 15)
							{
								// If the room is empty
								if (tCluster[cCol + cRow * 3] == -1)
								{
									// There is no tile
									tils.push_back(-1);
								}
								// Otherwise
								else
								{
									// Designate tile
									tils.push_back(_specialRooms[tCluster[cCol + cRow * 3]][rCol + rRow * 9]);
								}
							}
							// If the cluster was not so special
							else
							{
								// If the cluster or room are empty
								if (layout[dCol + dRow * 5] == -1 || tCluster[cCol + cRow * 3] == -1 )
								{
									// There is no tile
									tils.push_back(-1);
								}
								// Otherwise
								else
								{
									// Designate tile
									tils.push_back(_rooms[tCluster[cCol + cRow * 3]][rando][rCol + rRow * 9]);
								}
							}
						}					
					}
				}
			}
		}
	}
	// Return blueprint
	return tils;
}

// Normal rooms
int LevelSystem::_rooms[16][4][81] =
{
	{
		// █ █
		// █ █ 0
		// ███
		{0,2,37,72,72,72,38,2,3,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,24,72,72,72,72,72,72,72,27,60,107,61,107,61,107,61,107,63},
		{-1,0,37,72,72,72,38,3,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,24,72,72,72,72,72,27,-1,-1,60,61,107,87,107,61,63,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,9,32,72,72,72,35,10,-1,-1,20,73,72,72,72,74,23,-1,-1,12,72,72,72,72,72,15,-1,-1,56,85,72,72,72,86,59,-1,-1,76,41,85,72,86,42,79,-1,-1,-1,76,81,107,82,79,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,4,32,72,72,72,35,7,-1,9,29,73,72,72,72,74,30,10,20,73,72,72,72,72,72,74,23,12,72,72,72,72,72,72,72,15,56,85,72,72,72,72,72,86,59,76,41,85,72,72,72,86,42,79,-1,76,41,85,72,86,42,79,-1,-1,-1,76,81,107,82,79,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	},
	{
		// ███
		// █   1
		// ███
		{0,2,1,75,1,2,3,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,26,2,1,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,24,72,72,72,72,72,72,72,72,60,107,36,72,72,72,72,72,39,-1,-1,24,72,72,72,72,72,27,-1,-1,60,107,61,87,61,107,63},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,2,1,2,2,1,2,2,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,24,72,72,72,72,72,72,72,72,60,107,107,61,107,107,61,107,107,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,9,45,2,2,2,2,2,2,3,20,73,72,72,72,72,72,72,26,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,56,85,72,72,72,72,72,72,51,76,81,107,107,107,107,107,107,78,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,4,45,2,46,7,-1,-1,-1,9,29,73,72,74,30,10,-1,-1,20,73,72,72,72,74,22,2,2,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,56,85,72,72,72,86,71,107,107,76,41,85,72,86,42,79,-1,-1,-1,76,81,107,82,79,-1,-1,-1}
	},
	{
		// ███
		// █ █ 2
		// █ █
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,2,1,2,1,3,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,24,72,72,72,72,72,27,-1,-1,60,36,72,72,72,39,63,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,0,2,2,2,3,-1,-1,-1,0,25,72,72,72,26,3,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,24,72,72,72,72,72,27,-1,-1,60,36,72,72,72,39,63,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,1,2,2,1,2,3,-1,12,72,72,72,72,72,72,15,-1,12,72,72,72,72,72,72,15,-1,12,72,72,72,72,72,72,15,-1,24,72,72,72,72,72,72,27,-1,60,107,36,72,72,72,39,63,-1},
		{-1,9,45,2,2,2,46,10,-1,9,33,73,72,72,72,74,34,10,20,73,72,72,72,72,72,74,23,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,56,85,72,72,72,72,72,86,59,76,93,85,72,72,72,86,94,79,-1,76,44,72,72,72,47,79,-1}
	},
	{
		// ███
		//   █ 3
		// ███
		{-1,-1,5,2,2,2,6,-1,-1,-1,4,17,72,72,72,18,7,-1,2,28,73,72,72,72,74,31,3,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,27,107,40,85,72,72,72,86,43,63,-1,76,65,72,72,72,66,79,-1,-1,-1,77,107,107,107,78,-1,-1},
		{-1,-1,0,2,2,2,3,-1,-1,-1,-1,12,72,72,72,15,-1,-1,2,2,25,72,72,72,26,2,3,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,27,107,107,36,72,72,72,39,107,63,-1,-1,24,72,72,72,27,-1,-1,-1,-1,60,107,107,107,63,-1,-1},
		{-1,-1,-1,0,1,2,2,1,3,-1,-1,-1,12,72,72,72,72,15,2,2,1,25,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,27,107,107,61,36,72,72,72,72,15,-1,-1,-1,24,72,72,72,72,27,-1,-1,-1,60,61,107,107,61,63},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,1,2,2,1,2,3,-1,37,72,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,89,72,72,72,72,72,72,27,-1,77,107,61,107,107,61,107,63,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	},
	{
		// ███
		//     4
		// ███
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,1,75,1,2,3,-1,2,37,72,72,72,72,72,38,2,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,107,89,72,72,72,72,72,90,107,-1,77,107,61,87,61,107,78,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,2,75,2,1,2,75,2,1,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,61,107,87,107,61,107,87,107,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,4,45,2,1,2,46,7,-1,4,29,73,72,72,72,74,30,7,28,73,72,72,72,72,72,74,31,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,40,85,72,72,72,72,72,86,43,76,41,85,72,72,72,86,42,79,-1,76,81,107,61,107,82,79,-1},
		{-1,9,45,1,75,1,46,10,-1,-1,92,73,72,72,72,72,80,-1,1,16,72,72,83,72,72,19,1,72,72,72,72,95,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,83,72,72,72,72,61,52,72,72,95,72,72,55,61,-1,56,85,72,72,72,86,59,-1,-1,76,81,61,87,61,82,79,-1}
	},
	{
		// █ █
		// █ █ 5
		// █ █
		{-1,-1,12,72,72,72,15,-1,-1,0,2,25,72,72,72,26,2,3,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,24,72,72,72,72,72,72,72,27,60,107,36,72,72,72,39,107,63,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{0,2,37,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,38,2,3,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,24,72,72,72,72,72,72,72,15,60,107,88,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,27,-1,-1,12,72,72,72,91,107,63},
		{-1,9,32,72,72,72,35,10,-1,9,33,73,72,72,72,74,34,10,20,73,72,72,72,72,72,74,23,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,56,85,72,72,72,72,72,86,59,76,93,85,72,72,72,86,94,79,-1,76,44,72,72,72,47,79,-1}
	},
	{
		// █ █
		// █   6
		// ███
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,0,25,72,72,72,26,2,2,-1,12,72,72,72,72,72,72,72,-1,12,72,72,72,72,72,72,72,-1,24,72,72,72,72,72,72,72,-1,60,48,72,72,72,51,107,107,-1,-1,60,107,107,107,63,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,0,25,72,72,72,26,2,3,-1,12,72,72,72,72,72,72,26,-1,12,72,72,72,72,72,72,72,-1,12,72,72,72,72,72,72,72,-1,12,72,72,72,72,72,72,72,-1,12,72,72,72,72,72,72,39,-1,24,72,72,72,72,72,72,27,-1,60,107,107,107,107,107,107,63},
		{9,45,25,72,72,72,26,46,10,20,73,72,72,72,72,72,74,23,12,72,72,72,72,72,72,72,26,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,39,56,85,72,72,72,72,72,86,59,76,81,107,107,107,107,107,82,79},
		{-1,-1,12,72,72,72,26,2,3,-1,0,25,72,72,72,72,72,15,-1,12,72,72,72,72,72,72,26,-1,12,72,72,72,72,72,72,72,-1,12,72,72,72,72,72,72,72,-1,12,72,72,72,72,72,72,72,-1,24,72,72,72,72,72,51,107,-1,60,107,107,107,107,107,78,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	},
	{
		// ███
		// █   7
		// █ █
		{-1,-1,4,45,2,46,7,-1,-1,-1,4,29,73,72,74,30,7,-1,9,29,73,72,72,72,74,31,2,20,73,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,56,85,72,72,72,72,72,72,72,76,41,85,72,72,72,86,43,107,-1,76,53,72,72,72,54,79,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,2,2,2,2,2,-1,-1,12,72,72,72,72,72,72,-1,-1,12,72,72,72,72,72,72,-1,-1,12,72,72,72,72,72,72,-1,-1,12,72,72,72,39,107,107,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,1,2,75,2,1,2,3,12,72,72,72,72,72,72,72,26,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,24,72,72,72,72,72,72,72,51,60,107,88,72,72,72,91,107,78,-1,-1,12,72,72,72,15,-1,-1},
		{9,45,2,2,2,46,10,-1,-1,20,73,72,72,72,74,80,-1,-1,12,72,72,72,72,72,19,2,2,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,56,85,72,72,72,72,72,72,72,76,81,52,72,72,72,55,107,107,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1}
	},
	{
		// ███
		//   █ 8
		// █ █
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,2,46,7,-1,-1,-1,-1,-1,72,72,74,30,7,-1,-1,-1,-1,72,72,72,74,30,7,-1,-1,-1,72,72,72,72,74,30,10,-1,-1,107,40,85,72,72,74,23,-1,-1,-1,76,53,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,0,2,75,2,3,-1,-1,-1,-1,12,72,72,72,15,-1,-1,2,2,37,72,72,72,38,2,3,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,27,107,107,88,72,72,72,91,107,63,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,2,2,2,2,2,3,-1,25,72,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,36,72,72,72,72,72,72,15,-1,24,72,72,72,72,72,72,27,-1,60,107,36,72,72,72,39,63,-1},
		{-1,4,45,2,2,2,46,7,-1,4,29,73,72,72,72,74,30,10,28,73,72,72,72,72,72,74,23,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,40,85,72,72,72,72,72,86,59,76,41,85,72,72,72,86,42,79,-1,76,53,72,72,72,54,79,-1}
	},
	{
		// █ █
		//   █ 9
		// ███
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,2,2,25,72,72,72,26,2,3,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,107,107,36,72,72,72,72,72,15,-1,-1,24,72,72,72,72,72,27,-1,-1,60,107,107,107,107,107,63},
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,2,2,25,72,72,72,15,-1,-1,72,72,72,72,72,72,15,-1,-1,72,72,72,72,72,72,15,-1,-1,72,72,72,72,72,72,27,-1,-1,107,107,107,107,87,107,63,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,9,32,72,72,72,35,10,-1,-1,20,73,72,72,72,74,23,-1,2,25,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,72,72,72,72,72,72,72,15,-1,107,36,72,72,72,72,72,15,-1,-1,56,85,72,72,72,86,59,-1,-1,76,81,107,107,107,82,79,-1},
		{-1,-1,8,72,72,72,11,-1,-1,-1,4,17,72,72,72,18,7,-1,2,28,73,72,72,72,74,30,10,72,72,72,72,72,72,72,74,23,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,86,59,107,40,85,72,72,72,86,42,79,-1,76,41,85,72,86,42,79,-1,-1,-1,76,81,107,82,79,-1,-1}
	},
	{
		// █ █
		//     10
		// ███
		{-1,-1,8,72,72,72,11,-1,-1,-1,4,17,72,72,72,18,7,-1,1,28,73,72,72,72,74,31,1,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,61,107,87,107,61,107,87,107,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,2,2,37,72,72,72,38,2,2,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,107,107,61,107,87,107,61,107,107,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,0,25,72,72,72,26,2,3,2,37,72,72,72,72,72,72,38,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,107,88,72,72,72,72,72,72,91,-1,24,72,72,72,72,72,72,27,-1,60,107,107,107,107,107,107,63},
		{-1,-1,12,72,72,72,15,-1,-1,5,2,37,72,72,72,38,2,6,16,72,72,72,72,72,72,72,19,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,64,72,72,72,72,72,72,72,67,77,107,61,107,107,107,61,107,78,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	},
	{
		// █ █
		// █   11
		// █ █
		{-1,-1,12,72,72,72,15,-1,-1,0,2,25,72,72,72,26,3,-1,12,72,72,72,72,72,72,26,2,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,39,107,24,72,72,72,72,72,72,27,-1,60,107,36,72,72,72,39,63,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,38,2,2,-1,-1,12,72,72,72,72,72,72,-1,-1,12,72,72,72,72,72,72,-1,-1,12,72,72,72,72,72,72,-1,-1,12,72,72,72,91,107,107,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,0,25,72,72,72,26,3,-1,-1,12,72,72,72,72,72,26,2,-1,12,72,72,72,72,72,72,72,-1,12,72,72,72,72,72,72,72,-1,12,72,72,72,72,72,72,72,-1,24,72,72,72,72,72,51,107,-1,60,36,72,72,72,39,78,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,4,32,72,72,72,35,7,-1,9,29,73,72,72,72,74,30,10,20,73,72,72,72,72,72,74,22,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,56,85,72,72,72,72,72,86,71,76,41,85,72,72,72,86,42,79,-1,76,44,72,72,72,47,79,-1}
	},
	{
		// ███
		//     12
		// █ █
		{0,2,2,1,2,2,3,-1,-1,12,72,72,72,72,72,15,-1,-1,37,72,72,72,72,72,26,2,1,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,61,107,36,72,72,72,72,72,91,-1,-1,12,72,72,72,72,72,27,-1,-1,12,72,72,72,39,107,63},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,1,2,2,75,2,2,1,2,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,107,61,36,72,72,72,39,61,107,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{0,2,1,2,75,2,1,2,3,12,72,72,72,72,72,72,72,15,25,72,72,72,72,72,72,72,26,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,36,72,72,72,72,72,72,72,39,24,72,72,72,72,72,72,72,27,60,107,88,72,72,72,91,107,63},
		{-1,4,45,2,2,2,46,7,-1,9,29,73,72,72,72,74,30,10,21,73,72,72,72,72,72,74,22,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,107,107,52,72,72,72,55,107,107,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1}
	},
	{
		// █ █
		//   █ 13
		// █ █
		{-1,-1,12,72,72,72,15,-1,-1,0,1,25,72,72,72,26,1,3,25,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,48,72,72,72,72,72,72,72,27,77,61,36,72,72,72,39,61,63,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,2,2,25,72,72,72,15,-1,-1,72,72,72,72,72,72,15,-1,-1,72,72,72,72,72,72,15,-1,-1,72,72,72,72,72,72,15,-1,-1,107,107,36,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,8,72,72,72,11,-1,-1,-1,4,17,72,72,72,18,7,-1,2,28,73,72,72,72,74,30,10,72,72,72,72,72,72,72,74,23,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,86,59,107,40,85,72,72,72,86,42,79,-1,76,53,72,72,72,54,79,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,12,72,72,72,26,2,3,-1,9,32,72,72,72,72,72,15,2,21,73,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,107,68,85,72,72,72,72,72,15,-1,76,44,72,72,72,72,72,27,-1,-1,12,72,72,72,39,107,63}
	},
	{
		// █ █
		//     14
		// █ █
		{-1,4,32,72,72,72,15,-1,-1,9,29,73,72,72,72,15,-1,-1,21,73,72,72,72,72,26,2,2,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,107,107,36,72,72,72,72,86,71,-1,-1,12,72,72,72,86,42,79,-1,-1,12,72,72,72,47,79,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,8,72,72,72,11,-1,-1,2,2,16,72,72,72,19,2,2,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,107,107,52,72,72,72,55,107,107,-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1},
		{-1,-1,12,72,72,72,15,-1,-1,0,2,25,72,72,72,26,2,3,25,72,72,72,72,72,72,72,26,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,48,72,72,72,72,72,72,72,51,77,107,36,72,72,72,39,107,78,-1,-1,12,72,72,72,15,-1,-1},
		{9,45,25,72,72,72,26,46,10,20,73,72,72,72,72,72,74,23,25,72,72,72,72,72,72,72,26,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,36,72,72,72,72,72,72,72,39,56,85,72,72,72,72,72,86,59,76,81,36,72,72,72,39,82,79}
	},
	{
		// Entrance 15
		{-1,-1,8,72,72,72,11,-1,-1,-1,4,17,72,72,72,18,7,-1,9,29,73,72,72,72,74,30,10,20,73,72,72,72,72,72,74,23,12,72,83,72,72,72,83,72,15,56,85,95,72,72,72,95,86,59,76,41,85,72,72,72,86,42,79,-1,76,65,72,72,72,66,79,-1,-1,-1,77,49,84,50,78,-1,-1},
		{0,2,37,72,72,72,38,2,3,12,72,72,72,72,72,72,72,15,12,72,83,72,72,72,83,72,15,12,72,95,72,72,72,95,72,15,12,72,83,72,72,72,83,72,15,12,72,95,72,72,72,95,72,15,24,72,72,72,72,72,72,72,27,60,107,64,72,72,72,67,107,63,-1,-1,77,49,84,50,78,-1,-1},
		{-1,0,25,72,72,72,26,3,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,12,72,72,72,72,72,15,-1,-1,24,72,72,72,72,72,27,-1,-1,60,107,49,84,50,107,63,-1},
		{-1,-1,12,72,72,72,15,-1,-1,-1,-1,12,72,72,72,15,-1,-1,0,2,25,72,72,72,26,2,3,12,72,72,72,72,72,72,72,15,12,72,83,72,72,72,83,72,15,12,72,95,72,72,72,95,72,15,56,85,72,72,72,72,72,86,59,76,41,85,72,72,72,86,42,79,-1,76,81,49,84,50,82,79,-1}
	}
};

// Special rooms
int LevelSystem::_specialRooms[11][81] =
{
	// Boss vertical entrance  0
	{-1,-1,12,72,72,72,15,-1,-1,0,2,25,72,72,72,26,2,3,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,12,72,72,72,72,72,72,72,15,24,72,72,72,72,72,72,72,27,60,107,36,72,72,72,39,107,63,- 1,-1,12,72,72,72,15,-1,-1},

	// Boss horizontal entrance  1
	{},

	// Boss top left  2
	{-1,-1,-1,-1,-1,4,45,2,2,-1,-1,-1,-1,4,29,73,72,72,-1,-1,-1,4,29,73,72,72,72,-1,-1,4,29,73,72,72,72,72,-1,4,29,73,72,72,72,72,72,9,29,73,72,72,72,72,72,72,20,73,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72},

	// Boss bottom left  3
	{12,72,72,72,72,72,72,72,72,12,72,72,72,72,72,72,72,72,56,85,72,72,72,72,72,72,72,76,41,85,72,72,72,72,72,72,-1,76,41,85,72,72,72,72,72,-1,-1,76,41,85,72,72,72,72,-1,-1,-1,76,41,85,72,72,72,-1,-1,-1,-1,76,41,85,72,72,-1,-1,-1,-1,-1,76,81,107,107},

	// Boss top right  4
	{2,2,46,7,-1,-1,-1,-1,-1,72,72,74,30,7,-1,-1,-1,-1,72,72,72,74,30,7,-1,-1,-1,72,72,72,72,74,30,7,-1,-1,72,72,72,72,72,74,30,7,-1,72,72,72,72,72,72,74,30,10,72,72,72,72,72,72,72,74,23,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15},
	
	// Boss bottom right  5
	{72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,72,15,72,72,72,72,72,72,72,86,59,72,72,72,72,72,72,86,42,79,72,72,72,72,72,86,42,79,-1,72,72,72,72,86,42,79,-1,-1,72,72,72,86,42,79,-1,-1,-1,72,72,86,42,79,-1,-1,-1,-1,107,107,82,79,-1,-1,-1,-1,-1},

	// Boss top  6
	{2,1,2,2,13,2,2,1,2,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72},

	// Boss left  7
	{},

	// Boss right  8
	{},

	// Boss bottom  9
	{},

	// Boss middle  10
	{72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,118,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,107,107,36,72,72,72,39,107,107}
};

// Normal clusters
int LevelSystem::_clusters[15][4][9] =
{
	{
		// █ █
		// █ █ 0
		// ███
		{-1,11,8,-1,6,9,-1,-1,-1},
		{-1,11,3,1,13,-1,-1,0,-1},
		{-1,5,-1,1,14,8,-1,6,9},
		{-1,5,-1,-1,11,8,-1,0,0}
	},
	{
		// ███
		// █   1
		// ███
		{-1,7,8,-1,6,10,-1,-1,-1},
		{-1,-1,2,1,12,10,-1,0,-1},
		{7,8,-1,6,14,4,-1,0,-1},
		{1,8,-1,1,10,4,-1,-1,-1}
	},
	{
		// ███
		// █ █ 2
		// █ █
		{-1,-1,-1,7,8,-1,6,13,-1},
		{-1,2,-1,-1,11,3,1,13,-1},
		{7,8,-1,6,14,3,-1,5,-1},
		{2,2,-1,6,13,-1,-1,5,-1}
	},
	{
		// ███
		//   █ 3
		// ███
		{-1,-1,-1,12,8,-1,6,9,-1},
		{-1,2,-1,12,10,3,0,-1,-1},
		{-1,2,-1,4,14,8,-1,6,9},
		{-1,-1,-1,4,12,3,-1,6,3}
	},
	{
		// ███
		//     4
		// ███
		{-1,2,-1,4,14,4,-1,6,3},
		{7,4,8,13,-1,11,6,4,9},
		{-1,7,8,8,11,10,6,9,-1},
		{-1,2,2,12,10,10,0,-1,-1}
	},
	{
		// █ █
		// █ █ 5
		// █ █
		{-1,5,-1,1,13,-1,-1,5,-1},
		{7,13,-1,11,13,-1,6,13,-1},
		{-1,6,8,7,4,9,6,8,-1},
		{2,5,-1,6,14,8,-1,11,9}
	},
	{
		// █ █
		// █   6
		// ███
		{1,14,8,-1,5,6,-1,0,-1},
		{-1,11,8,-1,6,10,-1,-1,-1},
		{-1,5,-1,7,14,4,6,9,-1},
		{-1,5,-1,-1,6,12,-1,-1,0}
	},
	{
		// ███
		// █   7
		// █ █
		{2,-1,-1,11,12,4,6,13,-1},
		{-1,7,8,-1,11,14,-1,11,9},
		{7,8,-1,11,10,4,6,8,-1},
		{-1,-1,2,-1,-1,11,1,12,9}
	},
	{
		// ███
		//   █ 8
		// █ █
		{7,4,8,9,1,13,-1,7,9},
		{-1,2,-1,12,14,3,0,5,-1},
		{7,12,3,13,0,-1,6,8,-1},
		{-1,7,8,4,13,0,-1,5,-1}
	},
	{
		// █ █
		//   █ 9
		// ███
		{2,6,8,14,12,9,6,9,-1},
		{-1,11,3,4,10,3,-1,-1,-1},
		{-1,5,-1,8,11,3,6,9,-1},
		{7,10,8,13,-1,5,6,4,9}
	},
	{
		// █ █
		//     10
		// ███
		{-1,6,8,4,4,10,-1,-1,-1},
		{7,10,8,13,-1,11,0,-1,0},
		{-1,5,-1,4,14,12,-1,6,9},
		{-1,5,-1,12,9,7,6,4,9}
	},
	{
		// █ █
		// █   11
		// █ █
		{7,10,8,6,8,6,-1,5,-1},
		{1,13,-1,-1,11,4,1,13,-1},
		{-1,5,-1,-1,6,12,1,12,9},
		{-1,5,-1,1,14,4,-1,5,-1}
	},
	{
		// ███
		//     12
		// █ █
		{-1,1,8,4,12,14,-1,5,0},
		{7,8,-1,10,10,12,-1,7,9},
		{-1,7,8,8,5,6,6,13,-1},
		{2,2,-1,10,10,12,-1,7,9}
	},
	{
		// █ █
		//   █ 13
		// █ █
		{-1,6,8,4,12,13,-1,11,9},
		{7,13,-1,13,5,-1,6,13,-1},
		{-1,5,-1,12,10,8,6,8,0},
		{7,9,-1,10,12,8,-1,5,0}
	},
	{
		// █ █
		//     14
		// █ █
		{1,14,3,8,11,4,6,14,3},
		{-1,5,-1,4,14,4,-1,5,-1},
		{-1,11,3,12,13,7,6,14,9},
		{1,10,8,4,4,14,-1,7,9}
	}
};

// Special clusters
int LevelSystem::_specialClusters[2][9] =
{
	// Entrance
	// █ █
	// ███
	// ███
	{-1,15,-1,-1,-1,-1,-1,-1,-1},

	// Boss top
	// █▀█
	// ▌ ▐
	// █ █
	{2,6,4,3,10,5,-1,0,-1},
};

// Dungeon layouts
int LevelSystem::_dungeonLayouts[10][5][25] =
{
	// Level 1 variations
	{
		{-1,-1,-1,-1,-1,  -1,-1,-1,16,-1,  -1,-1, 7, 9,-1,  -1,-1, 5,-1,-1,  -1,-1,15,-1,-1},
		{-1,-1,-1,-1,-1,  -1,16,-1,-1,-1,  -1, 5,-1,-1,-1,  -1, 6, 8,-1,-1,  -1,-1,15,-1,-1},
		{-1,-1,16,-1,-1,  -1,-1, 5,-1,-1,  -1,-1, 5,-1,-1,  -1,-1, 5,-1,-1,  -1,-1,15,-1,-1},
		{-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,  -1,-1,-1,-1,16,  -1,-1, 7, 4, 9,  -1,-1,15,-1,-1},
		{-1,-1,-1,-1,-1,  -1,-1,-1,16,-1,  -1,-1,-1, 5,-1,  -1,-1, 7, 9,-1,  -1,-1,15,-1,-1}
	},
	// Level 2 variations
	{
		{-1,-1,-1,-1,-1,  -1,-1,-1,-1,16,  -1,-1,-1,-1, 5,  -1,-1, 7, 4, 9,  -1,-1,15,-1,-1},
		{-1,-1,-1,-1,-1,  -1,-1,16,-1,-1,  -1, 7, 9,-1,-1,  -1, 6, 8,-1,-1,  -1,-1,15,-1,-1},
		{-1,-1,-1,-1,-1,  -1,-1,-1,-1,16,  -1,-1,-1, 7, 9,  -1,-1, 7, 9,-1,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,  -1, 5,-1,-1,-1,  -1, 5,-1,-1,-1,  -1, 6, 8,-1,-1,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,  -1, 5,-1,-1,-1,  -1, 6, 8,-1,-1,  -1,-1, 5,-1,-1,  -1,-1,15,-1,-1}
	},
	// Level 3 variations
	{
		{-1,16,-1,-1,-1,  -1, 5, 2,-1,-1,  -1, 6,13,-1,-1,  -1,-1, 5,-1,-1,  -1,-1,15,-1,-1},
		{-1,-1,-1,16,-1,  -1,-1,-1, 5,-1,  -1,-1,-1,11, 3,  -1,-1, 7, 9,-1,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,  -1, 5,-1,-1,-1,  -1,11, 3,-1,-1,  -1, 6, 8,-1,-1,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,  -1, 5,-1,-1,-1,  -1, 6,12, 3,-1,  -1,-1, 5,-1,-1,  -1,-1,15,-1,-1},
		{-1,-1,-1,16,-1,  -1, 1,12, 9,-1,  -1,-1, 5,-1,-1,  -1,-1, 5,-1,-1,  -1,-1,15,-1,-1}
	},
	// Level 4 variations
	{
		{-1,-1,-1,16,-1,  -1,-1,-1, 5,-1,  -1,-1, 7,14, 3,  -1,-1,11, 9,-1,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,  -1, 5,-1,-1,-1,   7,13,-1,-1,-1,   6,10, 8,-1,-1,  -1,-1,15,-1,-1},
		{-1,-1,-1,16,-1,  -1,-1, 7,14, 3,  -1,-1,11, 9,-1,  -1,-1, 5,-1,-1,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,  -1,11, 3,-1,-1,   1,13,-1,-1,-1,  -1, 6, 8,-1,-1,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,  -1, 5, 2,-1,-1,  -1,11,13,-1,-1,  -1, 6,13,-1,-1,  -1,-1,15,-1,-1}
	},
	// Level 5 variations
	{
		{-1,-1,-1,16,-1,  -1,-1, 2, 5,-1,  -1, 7,14,13,-1,  -1, 6,14, 9,-1,  -1,-1,15,-1,-1},
		{-1,-1,-1,16,-1,  -1,-1, 1,14, 8,  -1,-1, 7,14, 9,  -1,-1,11, 9,-1,  -1,-1,15,-1,-1},
		{-1,-1, 2,16,-1,  -1, 1,14,13,-1,  -1,-1, 5, 5,-1,  -1,-1,11, 9,-1,  -1,-1,15,-1,-1},
		{-1,16, 2,-1,-1,   1,14,13,-1,-1,  -1, 6,13,-1,-1,  -1,-1,11, 3,-1,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,   1,14, 3,-1,-1,   7,13,-1,-1,-1,   6,10, 8,-1,-1,  -1,-1,15,-1,-1}
	},
	// Level 6 variations
	{
		{-1,-1,-1,16,-1,  -1, 6,12,13,-1,  -1, 5,11,10, 3,  -1,11, 9,-1,-1,  -1,15,-1,-1,-1},
		{-1,-1,-1,-1,-1,  16,-1,-1,-1,-1,   5, 1,12, 8,-1,   6,12,10,13,-1,  -1, 0,-1,15,-1},
		{-1,-1,16,-1,-1,  -1, 7,10, 8,-1,  -1,11,12,13,-1,  -1, 0,11, 9,-1,  -1,-1,15,-1,-1},
		{-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,   7, 8,-1, 2,16,  11,10,12,10, 9,  15,-1, 0,-1,-1},
		{-1,16, 2,-1,-1,  -1, 6,14, 3,-1,  -1,-1,11, 8,-1,  -1,-1, 6,14, 3,  -1,-1,-1,15,-1}
	},
	// Level 7 variations
	{
		{-1,-1,-1,-1,16,  -1,-1, 1,12,13,  -1, 7, 4,13, 5,  -1, 6,12,10, 9,  -1,-1,15,-1,-1},
		{-1,16,-1,-1,-1,   7,13,-1,-1,-1,   5,11,12, 8,-1,   6,14,10,13,-1,  -1,0,-1,15,-1},
		{-1,-1,-1,16,-1,   7, 8, 7,14, 3,   6,14,14, 9,-1,  -1,11, 9,-1,-1,  -1,15,-1,-1,-1},
		{-1,-1, 2,-1,16,  -1, 7,10,12,13,  -1, 6,12,10, 9,  -1, 1,13,-1,-1,  -1,-1,15,-1,-1},
		{-1,-1,16, 2,-1,  -1, 1,14,13,-1,  -1, 7,10,14, 3,  -1, 6,12, 9,-1,  -1,-1,15,-1,-1}
	},
	// Level 8 variations
	{
		{16, 2,-1,-1,-1,  11,14,12, 3,-1,   6,13,11, 8,-1,  -1, 6,14, 9,-1,  -1,-1,15,-1,-1},
		{-1, 7, 8,16,-1,   7,14,14,13,-1,   6,13,11, 9,-1,  -1,11, 9,-1,-1,  -1,15,-1,-1,-1},
		{16,-1,-1,-1,-1,   5, 7, 8, 2,-1,  11,10,14,13,-1,   6, 4,13,15,-1,  -1,-1, 0,-1,-1},
		{-1,-1,-1,-1,-1,  -1, 2,-1,-1,-1,   7,10,12, 3,-1,   6,12,14, 8,16,  -1,15, 6,10, 9},
		{-1,-1, 7, 8,16,  -1, 7,14,14, 9,  -1, 6,13, 5,-1,  -1,-1,11,10, 3,  -1,-1,15,-1,-1}
	},
	// Level 9 variations
	{
		{-1,-1,-1,-1,-1,   7, 4,12, 8,-1,   5,16,11,14, 3,   6,13, 5,15,-1,  -1, 6,10, 3,-1},
		{-1,-1,-1,16,-1,   7,12, 4,14, 8,   6,14, 8,11, 9,   7,10,10, 9,-1,  15,-1,-1,-1,-1},
		{-1, 2,-1,-1,16,   7,10,12,12,13,   6,12,13,11, 9,  -1,11,10, 9,-1,  -1,15,-1,-1,-1},
		{ 7,12, 3,-1,-1,  11,14,12, 8,-1,   0,15,11, 9,-1,  -1, 1,13,16,-1,  -1,-1, 6, 9,-1},
		{-1,-1,-1,-1,-1,   2,-1, 7, 8,-1,  11,12,14,10, 8,  15,11,13,16, 5,  -1, 0, 6,10, 9}
	},
	// Level 10 variations
	{
		{16, 7, 8,-1,-1,  11,13,11, 3,-1,   6,14,10,12, 8,  -1,11, 4,14, 9,  -1, 0,-1,15,-1},
		{-1, 2,-1,-1,16,   7,10,12, 8, 5,   6,12,13,11,13,  -1,11,10,14, 9,  -1,15,-1, 0,-1},
		{-1, 7, 8,-1,-1,  -1,11,10, 8,16,   7,14, 4,13, 5,   6,13,-1,11,13,  -1,15,-1, 6, 9},
		{-1,16,-1, 7, 8,  -1,11, 4,13, 5,   1,10, 4,14,13,  -1, 1,12,10,13,  -1,-1,15,-1, 0},
		{16,-1, 7, 8,-1,  11, 4,14, 9,-1,   6, 4,14,12, 8,  -1, 1,14,13,15,  -1,-1, 6, 9,-1}
	}
};

// Not enough layouts. Must make more...