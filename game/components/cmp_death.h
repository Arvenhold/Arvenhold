#pragma once
#include "ecm.h"
#include <sfml/Graphics.hpp>


class DeathComponent : public Component {
protected:
	bool _isPlayer;
public:
	DeathComponent() = delete;
	explicit DeathComponent(Entity* p);
	void update(double dt);
	void render();
	void kill();

	bool getType();
	void setType(bool type);

};