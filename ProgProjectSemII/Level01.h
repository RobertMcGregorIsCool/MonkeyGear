#pragma once

#include "Player.h"
#include "NPC_Monkey.h"

class Level01
{

public:

	void onUpdate(sf::Time t_deltaTime);

	Player m_player01{ sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f) };
	NPC_Monkey m_monkey01{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.25f), 150.0f };
};

