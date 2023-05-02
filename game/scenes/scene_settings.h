#pragma once

#include "engine.h"

/// <summary>
/// Settings
/// </summary>
class SettingsScene : public Scene
{
public:
	void Render() override;

	void Update(const double& dt) override;

	void Load() override;

	void UnLoad() override;
};
