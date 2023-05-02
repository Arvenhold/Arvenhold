#include "arvenhold.h"
#include <SFML/graphics.hpp>

class FileHandler {
public:
	static void save(int gameWidth, int gameHeight);
	static void load(int &gameWidth, int &gameHeight);
	static string ItoS(sf::Keyboard::Key k);
	static int CtoK(char c);
};