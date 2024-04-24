#pragma once

#include "Player.h"
#include "NPC_Monkey.h"
#include "NPC_Visitor.h"
#include "AmmoBox.h"
#include "Assets.h"

	// WIP Player / Monkey	= LoseLife/Teleport
	// WIP Player / Visitor	= Follow
	// WIP Player / AmmoBox	= More ammo
	// WIP Player / SafeZone= N/A
	// WIP Visitor/ Monkey	= Cower
	// Visitor/ Banana	= N/A
	// WIP Visitor/ SafeZone= N/A
	// WIP Monkey / BananaAr= Eat
	// WIP Monkey / BananaGd= Eat
	// Visitor/ Solid	= Impassible
	// Player / Solid	= Impassible
	// Monkey / Solid	= Impassible
	// Bananna/ Solid	= Impassible

class Render;	// FORWARD DEPENDANCY
class Game;		// FORWARD DEPENDANCY

class Level
{
	void actorUpdate(sf::Time t_deltaTime);

	void doCollisions(Game& t_game);

	void colPlayerMonkey(Game& t_game);
	void colPlayerVisitor();
	void colPlayerAmmoBox();
	void colMonkeyBanana();
	void colMonkeyVisitor();
	void colVisitorSafeZone();

	void rallyTimer(sf::Time t_deltaTime);

	const int M_DEF_VISITORS = 0; // Possibly I could just do this from the vector.size()?

public:
	Level(Assets& t_assets, Render& t_render);
	~Level();

	void onUpdate(sf::Time t_deltaTime, Game& t_game);

	void onReset();

	Assets& m_assets;
	Render& m_render;

	sf::RectangleShape	m_rectShapeBGImage;
	sf::RectangleShape	m_rectShape8x8Grid;
	sf::CircleShape		m_circShapeSafeZone;

	Player m_player01{ m_assets, sf::Vector2f(9.0f*7.5f*SCREEN_SCALAR, 2.0f*8.0f*SCREEN_SCALAR), m_render};

	std::vector<NPC_Monkey> m_monkeys;
	std::vector<NPC_Visitor> m_visitors;
	AmmoBox m_ammoBox{ m_assets };

	int m_curVisitors = M_DEF_VISITORS;

	const float M_INITIAL_PLAY_PERIOD = 30.0f;
	float m_playTimer = M_INITIAL_PLAY_PERIOD;
};