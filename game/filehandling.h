#include "arvenhold.h"

class FileHandler {
public:
	static void save(int gameWidth, int gameHeight);
	static void load(int &gameWidth, int &gameHeight);
};