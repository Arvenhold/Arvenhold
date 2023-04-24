#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <iostream>
#include "LevelSystem.h"
#include "player.h"

using namespace std;
using namespace sf;

const int gameWidth = 1920;
const int gameHeight = 1080;

unique_ptr<Player> player(new Player());

Texture roomSpriteSheet;

void load()
{

    if (!roomSpriteSheet.loadFromFile("res/img/dungeon_tiles.png"))
    {
        cerr << "Failed to load spritesheet!" << endl;
    }


    ls::generateDungeon(1);
}

void Update(RenderWindow& window)
{
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // check and consume events
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
            return;
        }
    }

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
    }

    player->Update(dt);
}

void Render(RenderWindow& window)
{
    ls::Render(window);


    player->Render(window);
}


int main() {
    RenderWindow window(sf::VideoMode({ gameWidth, gameHeight }), "Map Test");

    View view;
    view.reset(FloatRect({ 100, 100 }, { 1920, 1080 }));
    window.setView(view);

    load();

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        Update(window);
        view.setCenter(player.get()->getPosition());
        window.setView(view);
        Render(window);
        window.display();
    }
    return 0;
}