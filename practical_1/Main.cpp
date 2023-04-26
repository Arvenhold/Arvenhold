#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <iostream>
#include "LevelSystem.h"
#include "player.h"
#include "arvenhold.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;

const int gameWidth = 1920;
const int gameHeight = 1080;

//unique_ptr<Player> player(new Player());

Texture roomSpriteSheet;
Texture wizardSprite;


std::vector<b2Body*> bodies;
std::vector<Sprite*> sprites;

// 1 sfml unit = 30 physics units
const float physics_scale = 30.0f;
// inverse of physics_scale, useful for calculations
const float physics_scale_inv = 1.0f / physics_scale;
// Magic numbers for accuracy of physics simulation
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

//Convert from b2Vec2 to a Vector2f
inline const Vector2f bv2_to_sv2(const b2Vec2& in) {
    return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}
//Convert from Vector2f to a b2Vec2
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
    return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}
//Convert from screenspace.y to physics.y (as they are the other way around)
inline const Vector2f invert_height(const Vector2f& in) {
    return Vector2f(in.x, gameHeight - in.y);
}

b2World* world;

void init() {

    const b2Vec2 gravity(0.0f, 0.0f);

    // Construct a world, which holds and simulates the physics bodies.
    world = new b2World(gravity);

    if (!roomSpriteSheet.loadFromFile("res/img/dungeon_tiles.png"))
    {
        cerr << "Failed to load spritesheet!" << endl;
    }
    if (!wizardSprite.loadFromFile("res/img/wizard.png"))
    {
        cerr << "Failed to load spritesheet!" << endl;
    }

    for (int i = 1; i < 11; i++)
    {
        auto s = new Sprite();
        s->setPosition(Vector2f(i*(gameWidth / 12.f), (gameHeight / 2.f)));
        //s->setSize(Vector2f(8.0f, 16.0f));
        s->setOrigin(Vector2f(16.0f, 16.0f));
        s->setTexture(wizardSprite);
        //s->setScale(Vector2f(0.5f,0.5f));
        //s->setFillColor(Color::White);
        sprites.push_back(s);


        b2BodyDef BodyDef;
        // Is Dynamic(moving), or static(Stationary)
        BodyDef.type = b2_dynamicBody;
        BodyDef.position = sv2_to_bv2(s->getPosition());

        auto body = world->CreateBody(&BodyDef);

        body->SetActive(true);
        {
            b2PolygonShape ps;

            b2Vec2 vertices[4];

            vertices[0].Set(-0.5f, 1.0f);
            vertices[1].Set(-0.5f, -1.0f);
            vertices[2].Set(0.0f, -1.0f);
            vertices[3].Set(0.0f, 1.0f);

            ps.Set(vertices, 4);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &ps;

            body->CreateFixture(&fixtureDef);
        }

        

        bodies.push_back(body);
    }
}







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

    world->Step(dt, velocityIterations, positionIterations);

    for (int i = 0; i < bodies.size(); ++i) {
        // Sync Sprites to physics position
        sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));
        // Sync Sprites to physics Rotation
        sprites[i]->setRotation(radians((180 / b2_pi) * bodies[i]->GetAngle()));
    }

    activeScene->update(dt);
}

void Render(RenderWindow& window)
{
    for (auto e : sprites)
    {
        Renderer::queue(e);
    }
    activeScene->render();
}


int main() {
    RenderWindow window(sf::VideoMode({ gameWidth, gameHeight }), "Map Test");

   // View view;
   // view.reset(FloatRect({ 100, 100 }, { 1920, 1080 }));
  //  window.setView(view);

    Renderer::initialise(window);

    init();
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
       // view.setCenter(player.get()->getPosition());
       // window.setView(view);
        Render(window);
        window.display();
    }
    return 0;
}