#pragma once

#include "Player.h"
#include "NPC_Monkey.h"
#include "Assets.h"

class Level
{

public:

	Level(Assets& t_assets);
	~Level();

	void onUpdate(sf::Time t_deltaTime);

	Assets& m_assets;

	Player m_player01 {m_assets, sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f) };

	std::vector<NPC_Monkey> m_monkeys;
};

