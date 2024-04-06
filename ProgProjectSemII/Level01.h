#pragma once

#include "Player.h"
#include "NPC_Monkey.h"

class Level01
{

public:

	Player m_player01{ sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f) };
	NPC_Monkey m_monkey01{ sf::Vector2f(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f), 100.0f };
};

