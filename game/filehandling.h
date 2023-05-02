#include "arvenhold.h"
#include <SFML/graphics.hpp>

using namespace std;

class FileHandler {
public:
	static void save(int gameWidth, int gameHeight);
	static void load(int &gameWidth, int &gameHeight);
	static string ItoS(int k);
	static int StoI(string c);
};