#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <iostream>
#include "LevelSystem.h"

using namespace std;
using namespace sf;

const int gameWidth = 1920;
const int gameHeight = 1080;

Texture roomSpriteSheet;

void load()
{

    if (!roomSpriteSheet.loadFromFile("res/img/dungeon_tiles.png"))
    {
        cerr << "Failed to load spritesheet!" << endl;
    }


    ls::generateDungeon(1);
}

void Render(RenderWindow& window)
{
    ls::Render(window);
}


int main() {
    RenderWindow window(sf::VideoMode({ gameWidth, gameHeight }), "Map Test");

    load();

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        Render(window);
        window.display();
    }
    return 0;
}