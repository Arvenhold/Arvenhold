#include "arvenhold.h"
#include <SFML/graphics.hpp>

class FileHandler {
public:
	static void save(int gameWidth, int gameHeight);
	static void load(int &gameWidth, int &gameHeight);
	static char KtoC(sf::Keyboard::Key k);
	static sf::Keyboard::Key CtoK(char c);
};