#include "cmp_sound.h"

using namespace sf;
using namespace std;


void SoundComponent::play()
{
	//if (_sound.getStatus() != 2)
	//{
		_sound.stop();
		_sound.play();
	//}
}

SoundComponent::SoundComponent(Entity* p, std::string file) : Component(p)
{

	_sB = *Resources::load<SoundBuffer>(file);

	_sound.setBuffer(_sB);
}
