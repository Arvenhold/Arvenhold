#pragma once

#include "engine.h"

/// <summary>
/// The real world
/// </summary>
class OverGroundScene : public Scene 
{
public:
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
};