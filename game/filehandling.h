#include "arvenhold.h"
#include <SFML/graphics.hpp>

using namespace std;

class FileHandler {
public:
	static void save(int gameWidth, int gameHeight, int save);
	static void load(int &gameWidth, int &gameHeight, int &save);
	static string ItoS(int k);
	static int StoI(string c);
};