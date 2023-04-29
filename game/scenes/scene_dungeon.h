#pragma once

#include "engine.h"

class DungeonScene : public Scene {
private:
	static b2Vec2 DungeonScene::_polygons[120][6];

public:
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void generateDungeonEntities(std::vector<int> t);
	void UnLoad() override;
	void DungeonScene::generateEnemies();
};