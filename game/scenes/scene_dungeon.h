#pragma once

#include "engine.h"

class DungeonScene : public Scene {
private:
	/*sf::Text text;
	sf::Clock scoreClock;
	void respawn();*/

public:
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void generateDungeonEntities(std::vector<int> t);
	void UnLoad() override;
};