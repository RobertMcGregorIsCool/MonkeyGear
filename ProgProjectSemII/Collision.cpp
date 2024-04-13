#include "Collision.h"

void Collision::playerMonkey()
{
	std::cout << "Checking for monkeys.\n\n";
	for (int i = 0; i < m_level.m_monkeys.size(); i++)
	{
		if (m_level.m_player01.m_rectShapeCol.getGlobalBounds().intersects(m_level.m_monkeys[i].m_rectShape.getGlobalBounds()))
		{
			
		}
	}
}

void Collision::playerVisitor(){}
void Collision::monkeyBanana(){}
void Collision::visitorSafeZone(){}

Collision::Collision(Level& t_level) : m_level{ t_level }{}

Collision::~Collision(){}

void Collision::onUpdate()
{
	playerMonkey();
	playerVisitor();
	monkeyBanana();
	visitorSafeZone();
}
