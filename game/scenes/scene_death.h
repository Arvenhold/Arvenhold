#pragma once

#include "engine.h"

/// <summary>
/// The beginning
/// </summary>
class DeathScene : public Scene
{
public:
	void Render() override;

	void Update(const double& dt) override;

	void Load() override;

	void UnLoad() override;
};