#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <iostream>
#include "LevelSystem.h"
#include "player.h"
#include "arvenhold.h"
#include "system_resources.h"

using namespace std;
using namespace sf;

const int gameWidth = 1920;
const int gameHeight = 1080;

//unique_ptr<Player> player(new Player());

void load()
{
    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->load();
    menuScene->load();

    activeScene = gameScene;
}

void Update(RenderWindow& window)
{
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
    }

    activeScene->update(dt);
}

void Render(RenderWindow& window)
{
    activeScene->render();
}


int main() {
    RenderWindow window(sf::VideoMode({ gameWidth, gameHeight }), "Map Test");

    View view;
    view.reset(FloatRect({ 100, 100 }, { 1920, 1080 }));
    window.setView(view);

    Renderer::initialise(window);

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