/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#pragma once

#include "Player.h"
#include "NPC_Monkey.h"
#include "NPC_Visitor.h"
#include "AmmoBox.h"
#include "Assets.h"
#include "PropJeep.h"
#include "Dressing.h"

// Some collision stuff I'd still like to do:
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
	void colVisitorBanana();

	void rallyTimer(sf::Time t_deltaTime);

	const int M_DEF_VISITOR_SCORE = 0;
	const float M_INITIAL_RALLY_PERIOD = 35.0f;
	const float M_RALLY_EXTEND = 7.0f;

	Game& m_game;

public:
	Level(Assets& t_assets, Render& t_render, Game& t_game);
	~Level();

	void onUpdate(sf::Time t_deltaTime, Game& t_game);

	void rallyAddTime(float seconds);

	void onGameOver();

	void onReset();

	Assets& m_assets;
	Render& m_render;

	sf::RectangleShape	m_rectShapeBGImage;
	sf::RectangleShape	m_rectShape8x8Grid;	// Overlaid on play area, used by developer to place objects
	sf::CircleShape		m_circShapeSafeZone;// Debug visual to show safe zone radius

	Player m_player01{ m_assets, sf::Vector2f(9.0f*7.5f*SCREEN_SCALAR, 2.0f*8.0f*SCREEN_SCALAR), m_render};

	std::vector<NPC_Monkey> m_monkeys;

	NPC_Visitor m_visitor{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.25f), m_assets, m_player01 };
	
	AmmoBox m_ammoBox{ m_assets };

	// Remember to set position of Dressings in Level constructor, AND to animate!
	Dressing m_dresJeep{ m_assets, 0.1f, 1, 4, 32, 32, 128, 0, true, false };
	Dressing m_dresSmok{ m_assets, 0.1f, 2,2,8,8,112, 64, true, true };

	int m_visitorScore = M_DEF_VISITOR_SCORE;

	float m_rallyTimer = M_INITIAL_RALLY_PERIOD;
};