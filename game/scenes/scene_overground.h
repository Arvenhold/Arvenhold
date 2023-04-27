#pragma once

#include "engine.h"

class OverGroundScene : public Scene {
private:
	/*sf::Text text;
	sf::Clock scoreClock;
	void respawn();*/

public:
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
};