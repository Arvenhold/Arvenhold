#pragma once

#include "engine.h"

class MenuScene : public Scene {
private:
	//sf::Text text;

public:
	/*MenuScene() = default;

	~MenuScene() override = default;*/

	void Render() override;

	void Update(const double& dt) override;

	void Load() override;

	void UnLoad() override;
};