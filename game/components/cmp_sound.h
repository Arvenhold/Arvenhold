#pragma once

#include <ecm.h>
#include <system_resources.h>

/// <summary>
/// Sound element
/// </summary>
class SoundComponent : public Component {
protected:

	sf::SoundBuffer _sB;
	sf::Sound _sound;

public:
	void update(double dt) override {};
	void render() override {};
	void play();
	explicit SoundComponent(Entity* p, std::string file);
	SoundComponent() = delete;
};