#include "Level01.h"

void Level01::onUpdate(sf::Time t_deltaTime)
{
	m_player01.onUpdate(t_deltaTime);
	m_monkey01.onUpdate(t_deltaTime, m_player01.m_rectShape.getPosition());
}
