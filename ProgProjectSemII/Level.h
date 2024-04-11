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

	Player m_player01{ sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f) };
	// NPC_Monkey m_monkey01{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.25f), 150.0f };

	// static constexpr int M_MAX_MONKEYS{ 4 };
	// NPC_Monkey m_monkeys[M_MAX_MONKEYS];

	//std::array<NPC_Monkey, 4> m_monkeys = 

	Assets& m_assets;

	std::vector<NPC_Monkey> m_monkeys;
};

