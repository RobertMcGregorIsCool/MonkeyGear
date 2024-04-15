#pragma once

#include "Player.h"
#include "NPC_Monkey.h"
#include "NPC_Visitor.h"
#include "Assets.h"

	// WIP Player / Monkey	= LoseLife/Teleport
	// WIP Player / Visitor	= Follow
	// Player / AmmoBox	= More ammo
	// WIP Player / SafeZone= N/A
	// Visitor/ Monkey	= Cower
	// Visitor/ Banana	= N/A
	// Visitor/ SafeZone= N/A
	// Monkey / BananaAr= Eat
	// Monkey / BananaGd= Eat
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

	void playerMonkey(Game& t_game);
	void playerVisitor();
	void monkeyBanana();
	void visitorSafeZone();

	const int M_DEF_VISITORS = 4; // Possibly I could just do this from the vector.size()?

public:
	Level(Assets& t_assets, Render& t_render);
	~Level();

	void onUpdate(sf::Time t_deltaTime, Game& t_game);

	void onReset();

	Assets& m_assets;
	Render& m_render;

	sf::RectangleShape m_rectShapeBGImage;
	sf::RectangleShape m_rectShape8x8Grid;

	Player m_player01{ m_assets, sf::Vector2f(9.0f*7.5f*SCREEN_SCALAR, 2.0f*8.0f*SCREEN_SCALAR)};

	std::vector<NPC_Monkey> m_monkeys;

	int m_curVisitors = M_DEF_VISITORS;
};