#pragma once

#include "Player.h"
#include "NPC_Monkey.h"
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

class Level
{
	void playerUpdate(sf::Time t_deltaTime);

	void doCollisions();

	void playerMonkey();
	void playerVisitor();
	void monkeyBanana();
	void visitorSafeZone();

	const int M_DEF_VISITORS = 4; // Possibly I could just do this from the vector.size()?

public:
	Level(Assets& t_assets);
	~Level();

	void onUpdate(sf::Time t_deltaTime);

	void onReset();

	Assets& m_assets;

	sf::RectangleShape m_rectShapeBGImage;
	sf::RectangleShape m_rectShape8x8Grid;

	Player m_player01 {m_assets, sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f) };

	std::vector<NPC_Monkey> m_monkeys;

	int m_curVisitors = M_DEF_VISITORS;
};