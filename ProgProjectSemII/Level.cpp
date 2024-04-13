#include "Level.h"

Level::Level(Assets& t_assets): m_assets{t_assets}
{
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.25f), 150.0f, m_assets });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.25f), 150.0f, m_assets });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.85f), 150.0f, m_assets });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.85f), 150.0f, m_assets });


}

Level::~Level(){}

void Level::onUpdate(sf::Time t_deltaTime)
{
	m_player01.onUpdate(t_deltaTime);

	for (int i = 0; i < m_monkeys.size(); i++)
	{
		if (m_monkeys[i].isActive)
		{
			m_monkeys[i].onUpdate(t_deltaTime, m_player01.m_rectShapeVis.getPosition());
		}
	}
}
