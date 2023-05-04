#pragma once

#include "engine.h"

/// <summary>
/// Spooky scary skeletons
/// </summary>
class DungeonScene : public Scene 
{
private:

	// Array of dungeon collision shapes
	static b2Vec2 DungeonScene::_polygons[120][6];

public:
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void generateDungeonEntities(std::vector<int> t);
	void UnLoad() override;
	void DungeonScene::generateEnemies();
	std::vector<std::shared_ptr<Entity>> enemies;
};