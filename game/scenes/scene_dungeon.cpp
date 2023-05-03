#include "scene_dungeon.h"
#include <LevelSystem.h>
#include "../arvenhold.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_death.h"
#include <system_resources.h>
#include "../components/cmp_state_machine.h"
#include "../steering_states.h"
#include "../steering_decisions.h"
#include "../components/cmp_spell.h"
#include "../components/cmp_entity_tracker.h"
#include "../components/cmp_health_bar.h"
#include "../components/cmp_ui_element.h"
#include "../components/cmp_health.h"
#include "../components/cmp_enemyfire.h"
#include "../components/cmp_potion.h"
#include "../components/cmp_sound.h"
#include "../filehandling.h"

using namespace std;
using namespace sf;

// Useful entities
static shared_ptr<Entity> player;
static shared_ptr<Entity> boss;
static shared_ptr<Entity> ui;
static shared_ptr<Entity> door;

// Healthbars
vector<shared_ptr<Entity>> hpBars;

// Dungeon view
View view;

// Some interesting positions
Vector2f startPos;
Vector2f bossPos;
vector<Vector2f> floors;
vector<Vector2f> pillarPos;

// Current dungeon level
int level;

// Is boss dead
bool bossDead;
bool doorOpened;

/// <summary>
/// Update dungeon
/// </summary>
/// <param name="dt">delta time</param>
void DungeonScene::Update(const double& dt) 
{
	// If pressed tab go to main menu
	if (Keyboard::isKeyPressed(Keyboard::Key(60)))
	{
		Engine::ChangeScene(&menuScene);
	}
	else if (player->is_fordeletion())
	{
		// decrement dungeon level
		if (level > 1)
		{
			level--;
		}

		// Save game
		FileHandler::save(Engine::getWindowSize().y, Engine::getWindowSize().x, level);

		Engine::ChangeScene(&dScene);
	}
	else
	{
		auto pPos = player->getPosition();

		// If player goes to dungeon entrance
		if (pPos.x < startPos.x + 48 && pPos.x > startPos.x - 48 && pPos.y > startPos.y + 144 && pPos.y < startPos.y + 160)
		{
			// decrement dungeon level
			if (level > 1)
			{
				level--;
			}

			// Save game
			FileHandler::save(Engine::getWindowSize().y, Engine::getWindowSize().x, level);

			// Go touch grass
			Engine::ChangeScene(&ogScene);
		}
		else if (pPos.x < bossPos.x + 48 && pPos.x > bossPos.x - 48 && pPos.y > bossPos.y - 1300 && pPos.y < bossPos.y - 1250 && bossDead && doorOpened && level < 10)
		{
			// Go to next level
			Engine::ChangeScene(&dungeonScene);
		}
		else
		{
			// FPS
			//cout << 1.0 / dt << endl;

			// Set alive status for entities
			for (auto e : ents.list)
			{
				// If not alive or deleting but nearby
				if (length(e->getPosition() - player->getPosition()) < 2000 && !e->isAlive() && !e->is_fordeletion())
				{
					// Set alive
					e->setAlive(true);
				}
				// If not nearby but alive
				else if (length(e->getPosition() - player->getPosition()) > 2000 && e->isAlive())
				{
					// Set not alive
					e->setAlive(false);
				}
			}

			// Set hp bars alive for alive enemies
			for (auto e : hpBars)
			{
				if (e->get_components<HealthBarComponent>()[0]->isTargetAlive())
				{
					e->setAlive(true);
				}
			}

			// Make sure ui is alive
			ui->setAlive(true);


			// Update entities
			player->update(dt);

			if (boss->is_fordeletion())
			{
				bossDead = true;


				// Increment dungeon level
				if (level < 10)
				{
					level++;
				}

				// Save game
				FileHandler::save(Engine::getWindowSize().y, Engine::getWindowSize().x, level);

			}

			if (player->is_fordeletion())
			{
				// decrement dungeon level
				if (level > 1)
				{
					level--;
				}

				// Save game
				FileHandler::save(Engine::getWindowSize().y, Engine::getWindowSize().x, level);

				Engine::ChangeScene(&dScene);
			}
			else
			{

				if (bossDead && !doorOpened && level < 10)
				{
					door->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(sf::IntRect(Vector2(128, 64), Vector2(64, 64)));
					doorOpened = true;
				}

				Scene::Update(dt);

				// Set visibility status for near entities
				for (auto e : ents.list)
				{
					// If not visible or deleting but nearby
					if (!e->isVisible() && length(e->getPosition() - player->getPosition()) < 1280 && !e->is_fordeletion())
					{
						// Set visible
						e->setVisible(true);
					}
					// If not nearby but visible
					else if ((e->isVisible() && length(e->getPosition() - player->getPosition()) > 1280))
					{
						// Set not visible
						e->setVisible(false);
					}
				}

				// Reset view on player position
				view.setCenter(player.get()->getPosition());
				Engine::GetWindow().setView(view);
			}
		}
	}
}

/// <summary>
/// Load necessary entities and other fun stuff
/// </summary>
void DungeonScene::Load()
{
	// Yes, this is the dungeon scene
	cout << " Scene Dungeon Load" << endl;

	// Make sure vectors are clear
	pillarPos.clear();
	floors.clear();
	enemies.clear();
	hpBars.clear();

	// Bools
	bossDead = false;
	doorOpened = false;

	// Generate layout
	auto t = ls::generateDungeon(level);

	// Generate terrain entities
	generateDungeonEntities(t);

	// Make player entity
	player = makeEntity();
	player->setPosition(startPos);

	// Tag as player
	player->addTag("player");

	// Generate enemy entites
	generateEnemies();

	// Give player a nice sprite
	auto s = player->addComponent<SpriteComponent>();
	s->setTexure(Resources::get<Texture>("wizard.png"));
	s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
	s->getSprite().setScale({ 2, 2 });

	// Give the player some health
	player->addComponent<HealthComponent>(200);

	// Set standard physics body
	b2PolygonShape Shape;
	b2Vec2 vertices[4];
	vertices[0].Set(-1.0f, -1.0f);
	vertices[1].Set(0.0f, -1.0f);
	vertices[2].Set(1.0f, -1.0f);
	vertices[3].Set(0.0f, 0.0f);
	Shape.Set(vertices, 4);

	// Use body for player component
	player->addComponent<PlayerPhysicsComponent>(Shape);

	// Texture for pillar tops
	auto pillarSprite = Resources::get<Texture>("pillar.png");

	// Generate pillar tops
	for (int i = 0; i < pillarPos.size(); i++)
	{
		auto pillar = makeEntity();

		pillar->setPosition(pillarPos[i]);

		auto s = pillar->addComponent<SpriteComponent>();
		s->setTexure(pillarSprite);
		s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
		s->getSprite().setScale({ 2, 2 });
	}

	// Create healthbars for enemies that appear on top of sprites
	for (auto e : enemies)
	{
		auto enemyUI = makeEntity();
		enemyUI->addComponent<HealthBarComponent>(player.get(), e.get());
		hpBars.push_back(enemyUI);

	}

	// Set view to player position

	view.reset(FloatRect({ 0, 0 }, { 1920, 1080 }));
	view.setCenter(player.get()->getPosition());

	// Set all entities to not visible or alive
	for (auto e : ents.list)
	{
		e->setVisible(false);
		e->setAlive(false);
	}

	// Make UI
	ui = makeEntity();
	// Player Healthbar
	ui->addComponent<HealthBarComponent>(player.get(), player.get());

	auto fireball = ui->addComponent<UIComponent>(Vector2f(-100, 420));
	fireball->setTexure(Resources::get<Texture>("ui_fire.png"));
	fireball->getSprite().setOrigin({ 32, 32 });
	fireball->getSprite().setScale({ 1.5, 1.5 });

	auto lightning = ui->addComponent<UIComponent>(Vector2f(0, 420));
	lightning->setTexure(Resources::get<Texture>("ui_lightning.png"));
	lightning->getSprite().setOrigin({ 32, 32 });
	lightning->getSprite().setScale({ 1.5, 1.5 });

	auto frost = ui->addComponent<UIComponent>(Vector2f(100, 420));
	frost->setTexure(Resources::get<Texture>("ui_frost.png"));
	frost->getSprite().setOrigin({ 32, 32 });
	frost->getSprite().setScale({ 1.5, 1.5 });

	auto potion = ui->addComponent<UIComponent>(Vector2f(230, 420));
	potion->setTexure(Resources::get<Texture>("ui_potion.png"));
	potion->getSprite().setOrigin({ 32, 32 });
	potion->getSprite().setScale({ 1.5, 1.5 });

	auto potionNum = ui->addComponent<UITextComponent>("5", Vector2f(300, 385));
	potionNum->getText()->setFillColor(Color::White);
	potionNum->getText()->setCharacterSize(72);
	auto width = potionNum->getText()->getLocalBounds().width / 2.f;
	auto height = potionNum->getText()->getLocalBounds().height / 2.f;
	potionNum->getText()->setOrigin({ width, height });

	// Give player some spells
	player->addComponent<SpellComponent>(15.0f, &(fireball->getSprite()), &(lightning->getSprite()), &(frost->getSprite()));

	// Give the player some health potions
	player->addComponent<PotionComponent>(&(potion->getSprite()), potionNum->getText());

	auto Sounds = makeEntity();
	{
		Sounds->addComponent<SoundComponent>("Hurt.wav");
		Sounds->addComponent<SoundComponent>("Player_cast.wav");
		Sounds->addComponent<SoundComponent>("lightning_2.wav");
		Sounds->addComponent<SoundComponent>("Enemy_cast.wav");
		Sounds->addComponent<SoundComponent>("Enemy_death.wav");
		Sounds->addComponent<SoundComponent>("Projectile_Explosion.wav");
		//Sounds->addComponent<SoundComponent>("Player_cast.wav");
	}
	Sounds->addTag("sound");

	// Set window view
	Engine::GetWindow().setView(view);

	// Everything is loaded
	setLoaded(true);
}

/// <summary>
/// Generate terrain entities for the dungeon from the blueprint provided
/// </summary>
/// <param name="t">Dungeon layout blueprint</param>
void DungeonScene::generateDungeonEntities(vector<int> t)
{
	// Load in terrain texture
	auto text = Resources::get<Texture>("dungeon_tiles.png");

	// Go down the rows of this "2d" vector
	for (int i = 0; i < 135; i++)
	{
		// Go across the columns of this "2d" vector
		for (int j = 0; j < 135; j++)
		{
			// If it is not an empty square
			if (t[i * 135 + j] != -1)
			{
				// Make tile entity
				auto tile = makeEntity();

				// Set its proper position
				tile->setPosition(Vector2f(j * 128, i * 128));

				// If it is the dungeon entrance
				if (t[i * 135 + j] == 84)
				{
					// Set start position to be just above it
					startPos = Vector2f(j * 128, (i-1) * 128);
				}

				// If it is a pillar base
				if (t[i * 135 + j] == 95)
				{
					// Keep an eye on it
					pillarPos.push_back(Vector2f(j * 128, (i - 1) * 128));
				}

				// Give the tile a texture
				auto s = tile->addComponent<SpriteComponent>();
				s->setTexure(text);
				s->getSprite().setOrigin(Vector2f(32.0f, 32.0f));

				//Give the tile its proper sprite from the texture
				auto xpos = t[i * 135 + j] % 12;
				auto ypos = t[i * 135 + j] / 12;
				s->getSprite().setTextureRect(sf::IntRect(Vector2(xpos * 64, ypos * 64), Vector2(64, 64)));
				s->getSprite().setScale({ 2, 2 });

				// If the tile is not a floor tile
				if (t[i * 135 + j] != 72 && t[i * 135 + j] != 73 && t[i * 135 + j] != 74 && t[i * 135 + j] != 84 && t[i * 135 + j] != 85 && t[i * 135 + j] != 86 && t[i * 135 + j] != 118 && t[i * 135 + j] != 119)
				{
					// Give the tile a collision shape
					b2PolygonShape Shape;
					Shape.Set(_polygons[t[i * 135 + j]], 6);
					tile->addComponent<PhysicsComponent>(false, Shape);

					// Tag it as either a wall or a pillar
					if (t[i * 135 + j] != 83 && t[i * 135 + j] != 95)
					{
						tile->addTag("wall");
					}
					else
					{
						tile->addTag("pillar");
					}

					if (t[i * 135 + j] == 13)
					{
						door = tile;
					}
				}
				// If it is but a floor
				else
				{
					// Tag it as a floor and keep track of its position
					tile->addTag("floor");
					floors.push_back(Vector2f(j * 128, (i - 1) * 128));
				}

				// The location of the boss is of much interest to the enemy generator
				if (t[i * 135 + j] == 118)
				{
					bossPos = Vector2f(j * 128, (i - 1) * 128);
				}
			}
		}
	}
}

/// <summary>
/// Generate enemy entities for the dungeon
/// </summary>
void DungeonScene::generateEnemies()
{
	// Random number fun time
	srand(time(NULL));

	// Load in the enemy textures
	auto skellington = Resources::get<Texture>("skelly.png");
	auto skellWarrior = Resources::get<Texture>("skelly-warrior.png");
	auto skellRanger = Resources::get<Texture>("skelly-ranger.png");
	auto skellWizard = Resources::get<Texture>("skelly-wizard.png");

	// For each floor tile
	for (int i = 0; i < floors.size(); i++)
	{
		// If it is not too close to the entrance
		if (length(floors[i] - startPos) > 1280.0)
		{
			// Spin the wheel to spawn an enemy
			int spawnChance = (rand() % 100) + 1;

			// If the wheel says "YES"
			if (spawnChance <= (10 + 3 * level))
			{
				// Make and enemy and tag it as such
				auto enemy = makeEntity();
				enemy->addTag("enemy");

				// Place it on the floor tile
				enemy->setPosition({ floors[i].x , floors[i].y + 64 });

				// Give the enemy a shape
				b2PolygonShape Shape;
				b2Vec2 vertices[4];
				vertices[0].Set(-0.5f, -0.5f);
				vertices[1].Set(0.0f, -1.0f);
				vertices[2].Set(0.5f, 0.5f);
				vertices[3].Set(0.0f, 1.0f);
				Shape.Set(vertices, 4);

				// Spin the super wheel for determining the enemy type
				int enemyType = (rand() % 100) + 1;
				{
					// Give the enemy a new look
					auto s = enemy->addComponent<SpriteComponent>();
					s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));

					// If it is a normal skeleton enemy
					if (enemyType < (100 - level * 5))
					{
						// Set correct texture
						s->setTexure(skellington);

						enemy->addComponent<HealthComponent>(75);

						enemy->addComponent<EnemyHitComponent>(player.get(), 5);

						// Set physics component and speed 
						enemy->addComponent<PhysicsComponent>(true, Shape, 175.0f);

						// Give the enemy some states of being
						auto sm = enemy->addComponent<StateMachineComponent>();
						sm->addState("stationary", make_shared<StationaryState>());
						sm->addState("hit", make_shared<HitState>(enemy, player));
						sm->addState("seek", make_shared<SeekState>(enemy, player));

						// Decision tree for the enemy AI
						auto decision = make_shared<DistanceDecision>(
							player,
							64.0f,
							make_shared<HitDecision>(),
							make_shared<DistanceDecision>(
								player,
								1000.0f,
								make_shared<SeekDecision>(),
								make_shared<StationaryDecision>()));

						// Give the enemy some decisions to make
						enemy->addComponent<DecisionTreeComponent>(decision);

						// Set the enemy size
						s->getSprite().setScale({ 2, 2 });
					}
					// If it is a skeleton warrior
					else if (enemyType < (100 - level * 3))
					{
						// Set correct texture
						s->setTexure(skellWarrior);

						enemy->addComponent<HealthComponent>(150);

						enemy->addComponent<EnemyHitComponent>(player.get(), 15);

						// Set physics component and speed 
						enemy->addComponent<PhysicsComponent>(true, Shape, 150.0f);

						// Give the enemy some states of being
						auto sm = enemy->addComponent<StateMachineComponent>();
						sm->addState("stationary", make_shared<StationaryState>());
						sm->addState("hit", make_shared<HitState>(enemy, player));
						sm->addState("seek", make_shared<SeekState>(enemy, player));

						// Decision tree for the enemy AI
						auto decision = make_shared<DistanceDecision>(
							player,
							72.0f,
							make_shared<HitDecision>(),
							make_shared<DistanceDecision>(
								player,
								1000.0f,
								make_shared<SeekDecision>(),
								make_shared<StationaryDecision>()));

						// Give the enemy some decisions to make
						enemy->addComponent<DecisionTreeComponent>(decision);

						// Set the enemy size
						s->getSprite().setScale({ 2.4, 2.4 });
					}
					// If it is a skeleton ranger
					else if (enemyType < (100 - level * 1.5f))
					{
						// Set correct texture
						s->setTexure(skellRanger);

						enemy->addComponent<HealthComponent>(120);

						// Set physics component and speed 
						enemy->addComponent<PhysicsComponent>(true, Shape, 200.0f);

						enemy->addComponent<EnemyFireComponent>(25.0f,1);

						// Give the enemy some states of being
						auto sm = enemy->addComponent<StateMachineComponent>();
						sm->addState("stationary", make_shared<StationaryState>());
						sm->addState("seek", make_shared<SeekState>(enemy, player));
						sm->addState("flee", make_shared<FleeState>(enemy, player));
						sm->addState("cast", make_shared<CastState>(enemy, player));

						// Decision tree for the enemy AI
						auto decision = make_shared<DistanceDecision>(
							player,
							200.0f,
							make_shared<FleeDecision>(),
							make_shared<DistanceDecision>(
								player,
								700.0f,
								make_shared<CastDecision>(),
								make_shared<DistanceDecision>(
									player,
									1000.0f,
									make_shared<SeekDecision>(),
									make_shared<StationaryDecision>())));

						// Give the enemy some decisions to make
						enemy->addComponent<DecisionTreeComponent>(decision);

						// Set the enemy size
						s->getSprite().setScale({ 2.2, 2.2 });
					}
					// If it is a skeleton wizard
					else
					{
						// Set correct texture
						s->setTexure(skellWizard);

						enemy->addComponent<HealthComponent>(90);

						// Set physics component and speed 
						enemy->addComponent<PhysicsComponent>(true, Shape, 125.0f);

						enemy->addComponent<EnemyFireComponent>(40.0f,0);

						// Give the enemy some states of being
						auto sm = enemy->addComponent<StateMachineComponent>();
						sm->addState("stationary", make_shared<StationaryState>());
						sm->addState("seek", make_shared<SeekState>(enemy, player));
						sm->addState("flee", make_shared<FleeState>(enemy, player));
						sm->addState("cast", make_shared<CastState>(enemy, player));

						// Decision tree for the enemy AI
						auto decision = make_shared<DistanceDecision>(
							player,
							200.0f,
							make_shared<FleeDecision>(),
							make_shared<DistanceDecision>(
								player,
								600.0f,
								make_shared<CastDecision>(),
								make_shared<DistanceDecision>(
									player,
									1000.0f,
									make_shared<SeekDecision>(),
									make_shared<StationaryDecision>())));

						// Give the enemy some decisions to make
						enemy->addComponent<DecisionTreeComponent>(decision);

						// Set the enemy size
						s->getSprite().setScale({ 2, 2 });
					}
				}
				// Add the enemy to the list
				enemies.push_back(enemy);
			}
		}
	}

	// Make the boss
	boss = makeEntity();

	// Give them somewhere to stay
	boss->setPosition(bossPos);

	boss->addTag("enemy");

	boss->addComponent<HealthComponent>(1000 + 500*(level-1));

	boss->addComponent<EnemyHitComponent>(player.get(), 60);

	boss->addComponent<EnemyFireComponent>(60.0f, 2);

	// Give them a shape
	b2PolygonShape Shape;
	b2Vec2 vertices[4];
	vertices[0].Set(-2.0f, -2.0f);
	vertices[1].Set(0.0f, -4.0f);
	vertices[2].Set(2.0f, -2.0f);
	vertices[3].Set(0.0f, 0.0f);
	Shape.Set(vertices, 4);

	// And some physics too
	boss->addComponent<PhysicsComponent>(true, Shape, 100.0f);

	// Give the boss something to wear
	auto s = boss->addComponent<SpriteComponent>();
	s->setTexure(skellWarrior);
	s->getSprite().setOrigin(Vector2f(16.0f, 16.0f));
	s->getSprite().setScale({ 4, 4 });

	// The boss needs some states to be in
	auto sm = boss->addComponent<StateMachineComponent>();
	sm->addState("stationary", make_shared<StationaryState>());
	sm->addState("seek", make_shared<SeekState>(boss, player));
	sm->addState("hit", make_shared<HitState>(boss, player));
	sm->addState("cast", make_shared<CastState>(boss, player));

	// Decisions for the boss
	auto decision = make_shared<DistanceDecision>(
		player,
		144.0f,
		make_shared<HitDecision>(),
		make_shared<DistanceDecision>(
			player,
			720.0f,
			make_shared<RandomDecision>(
				make_shared<CastDecision>(),
				make_shared<SeekDecision>()),
			make_shared<DistanceDecision>(
				player,
				1280.0f,
				make_shared<SeekDecision>(),
				make_shared<StationaryDecision>())));

	// The boss is the one to make the decisions
	boss->addComponent<DecisionTreeComponent>(decision);

	// Add the enemy to the list
	enemies.push_back(boss);
}

/// <summary>
/// Unload everything
/// </summary>
void DungeonScene::UnLoad()
{
	// Empty vectors
	enemies.clear();
	floors.clear();
	pillarPos.clear();
	hpBars.clear();

	// Just to be tidy
	player.reset();
	ui.reset();
	boss.reset();
	door.reset();

	// Unload EVERYTHING
	Scene::UnLoad();
}

/// <summary>
/// Render Dungeon scene
/// </summary>
void DungeonScene::Render() 
{
	// Render the scene
	Scene::Render();

	// Queue healthbars
	for (auto e : hpBars)
	{
		e->render();
	}

	// Queue UI
	ui->render();

	// Render UI elements again
	Renderer::render();
}

/// <summary>
/// Dungeon terrain collision bodies
/// </summary>
b2Vec2 DungeonScene::_polygons[120][6] =
{
	// Row 1
	{{ 0.5f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{ 0.0f,-0.5f},{ 0.0f,-2.1f}}, // 0
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 1
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 2
	{{-2.1f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f,-0.5f},{-0.5f, 0.0f},{-2.1f, 0.0f}}, // 3
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 4
	{{ 0.5f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{ 0.0f,-0.5f},{ 0.0f,-2.1f}}, // 5
	{{-2.1f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f,-0.5f},{-0.5f, 0.0f},{-2.1f, 0.0f}}, // 6
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 7
	{{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 2.1f}}, // 8
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 9
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 10
	{{-0.5f, 2.1f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 11
	// Row 2
	{{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 2.1f}}, // 12
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 13
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 14
	{{-0.5f, 2.1f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 15
	{{-2.1f,-0.5f},{-0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 16
	{{-2.1f,-2.1f},{ 0.5f, 0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 0.5f},{-2.1f, 0.0f}}, // 17
	{{-0.5f, 2.1f},{-0.5f, 0.5f},{ 2.1f,-2.1f},{ 2.1f, 0.0f},{ 0.5f, 0.5f},{ 0.5f, 2.1f}}, // 18
	{{-0.5f, 2.1f},{-0.5f, 0.5f},{ 0.5f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 2.1f}}, // 19
	{{ 2.1f, 2.1f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f}}, // 20
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 21
	{{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 22
	{{-2.1f, 2.1f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f},{-0.5f, 2.1f}}, // 23
	// Row 3
	{{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 2.1f}}, // 24
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 25
	{{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 26
	{{-0.5f, 2.1f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 27
	{{-2.1f,-0.5f},{-0.5f,-0.5f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 0.5f},{-2.1f, 0.0f}}, // 28
	{{-2.1f,-2.1f},{ 0.0f, 0.0f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 0.5f},{-2.1f, 0.0f}}, // 29
	{{-2.1f, 2.1f},{ 0.0f, 0.0f},{ 2.1f,-2.1f},{ 2.1f, 0.0f},{ 0.5f, 0.5f},{ 0.5f, 2.1f}}, // 30
	{{-2.1f, 2.1f},{ 0.5f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.5f, 0.5f},{ 0.5f, 2.1f}}, // 31
	{{-2.1f,-2.1f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f},{-2.1f,-0.5f}}, // 32
	{{-2.1f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f},{-2.1f,-0.5f}}, // 33
	{{-2.1f, 2.1f},{-0.5f,-0.5f},{ 2.1f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 2.1f}}, // 34
	{{-0.5f, 2.1f},{-0.5f,-0.5f},{ 2.1f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 2.1f}}, // 35
	// Row 4
	{{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f}}, // 36
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 37
	{{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-0.5f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 38
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 39
	{{ 2.1f,-2.1f},{-0.5f, 0.5f},{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f}}, // 40
	{{ 2.1f,-2.1f},{ 0.0f, 0.0f},{-2.1f, 2.1f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f}}, // 41
	{{ 2.1f, 2.1f},{ 0.0f, 0.0f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 0.0f}}, // 42
	{{ 2.1f, 0.5f},{ 0.5f, 0.5f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 0.0f}}, // 43
	{{-2.1f, 2.1f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f}}, // 44
	{{-2.1f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f},{-2.1f,-0.5f}}, // 45
	{{-2.1f,-0.5f},{ 2.1f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 46
	{{ 2.1f, 2.1f},{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 47
	// Row 5
	{{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f}}, // 48
	{{ 2.1f,-2.1f},{ 0.5f, 2.1f},{-0.5f, 2.1f},{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f,-2.1f}}, // 49
	{{ 2.1f, 0.5f},{ 0.5f, 2.1f},{-0.5f, 2.1f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 50
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 51
	{{ 0.5f,-2.1f},{ 0.5f,-0.5f},{-0.5f, 0.5f},{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f,-2.1f}}, // 52
	{{ 0.5f,-2.1f},{ 0.5f,-0.5f},{-2.1f, 2.1f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f}}, // 53
	{{ 2.1f, 2.1f},{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 0.0f}}, // 54
	{{ 2.1f, 0.5f},{ 0.5f, 0.5f},{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 55
	{{ 2.1f,-2.1f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f}}, // 56
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 57
	{{ 2.1f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 58
	{{-0.5f, 2.1f},{-2.1f,-2.1f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 59
	// Row 6
	{{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.5f, 0.0f},{ 2.1f, 0.0f},{ 2.1f, 0.5f}}, // 60
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 61
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 62
	{{-0.5f, 2.1f},{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f, 0.0f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 63
	{{ 0.5f,-2.1f},{ 0.5f,-0.5f},{-0.5f, 0.5f},{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f,-2.1f}}, // 64
	{{ 0.5f,-2.1f},{ 0.5f,-0.5f},{-2.1f, 2.1f},{-2.1f, 0.0f},{-0.5f,-0.5f},{ 0.0f,-2.1f}}, // 65
	{{ 2.1f, 2.1f},{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-0.5f},{ 2.1f, 0.0f}}, // 66
	{{ 2.1f, 0.5f},{ 0.5f, 0.5f},{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 67
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 2.1f,-2.1f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f}}, // 68
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 2.1f,-2.1f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 69
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 70
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-2.1f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 71
	// Row 7
	{{},{},{},{},{},{}}, // 72 - Unused
	{{},{},{},{},{},{}}, // 73 - Unused
	{{},{},{},{},{},{}}, // 74 - Unused
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 75
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 76
	{{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.5f, 0.0f},{ 2.1f, 0.0f},{ 2.1f, 0.5f}}, // 77
	{{-0.5f, 2.1f},{-2.1f, 0.5f},{-2.1f, 0.0f},{-0.5f, 0.0f},{ 0.0f, 0.0f},{ 0.0f, 2.1f}}, // 78
	{{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f}}, // 79
	{{-2.1f, 2.1f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f, 0.0f},{ 0.0f, 2.1f},{-0.5f, 2.1f}}, // 80
	{{-2.1f, 2.1f},{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f, 0.0f},{ 2.1f, 0.0f},{ 2.1f, 0.5f}}, // 81
	{{-2.1f, 0.5f},{-2.1f, 0.0f},{ 0.0f, 0.0f},{ 2.1f, 0.0f},{ 2.1f, 0.5f},{ 2.1f, 2.1f}}, // 82
	{{-0.5f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f,-0.5f},{ 0.0f,-0.5f}}, // 83
	// Row 8
	{{},{},{},{},{},{}}, // 84 - Unused
	{{},{},{},{},{},{}}, // 85 - Unused
	{{},{},{},{},{},{}}, // 86 - Unused
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 87
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 88
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 89
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 90
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 91
	{{ 2.1f, 2.1f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{ 0.0f, 0.0f},{ 0.0f,-2.1f},{ 0.5f,-2.1f}}, // 92
	{{-2.1f, 0.0f},{ 0.0f,-2.1f},{ 2.1f,-2.1f},{ 0.5f, 0.5f},{-2.1f, 2.1f},{-2.1f, 0.5f}}, // 93
	{{ 2.1f, 2.1f},{-0.5f, 0.5f},{-2.1f,-2.1f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 2.1f, 0.0f}}, // 94
	{{-0.5f, 2.1f},{-0.5f, 0.5f},{ 0.0f, 0.5f},{ 0.5f, 0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f}}, // 95
	// Row 9
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 96
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 1.0f},{-2.1f, 0.5f}}, // 97
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f}}, // 98
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f}}, // 99
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 100
	{{ 2.1f, 0.5f},{ 0.0f, 1.0f},{-0.5f, 0.5f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 101
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 102
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-0.5f, 0.5f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 103
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 104
	{{-2.1f,-0.5f},{-0.5f,-2.1f},{ 0.0f,-2.1f},{ 0.0f,-0.5f},{-0.5f, 0.0f},{-2.1f, 0.0f}}, // 105
	{{ 0.5f,-2.1f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{ 0.0f,-0.5f},{ 0.0f,-2.1f}}, // 106
	{{ 2.1f, 0.5f},{ 0.0f, 0.5f},{-2.1f, 0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 107
	// Row 10
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f},{ 2.1f, 0.0f},{ 0.0f, 0.0f},{-2.1f, 0.0f}}, // 108
	{{-0.5f, 2.1f},{-0.5f, 0.0f},{-0.5f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 0.0f},{ 0.5f, 2.1f}}, // 109
	{{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 0.5f}}, // 110
	{{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 0.5f}}, // 111
	{{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 0.5f}}, // 112
	{{-0.5f, 0.5f},{-0.5f, 0.0f},{-0.5f,-2.1f},{ 0.5f,-2.1f},{ 0.5f, 0.0f},{ 0.5f, 0.5f}}, // 113
	{{ 2.1f, 0.0f},{ 0.0f, 2.1f},{-0.5f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-0.5f},{ 2.1f,-0.5f}}, // 114
	{{-2.1f,-0.5f},{ 0.0f,-0.5f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 115
	{{-2.1f,-0.5f},{ 0.0f,-1.0f},{ 0.5f,-0.5f},{ 0.5f, 2.1f},{ 0.0f, 2.1f},{-2.1f, 0.0f}}, // 116
	{{ 2.1f, 0.0f},{ 0.0f, 2.1f},{-0.5f, 2.1f},{-0.5f,-0.5f},{ 0.0f,-1.0f},{ 2.1f,-0.5f}}, // 117
	{{},{},{},{},{},{}}, // 118 - Unused
	{{},{},{},{},{},{}}  // 119 - Unused
};
