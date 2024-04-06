#include "NPC_Monkey.h"

NPC_Monkey::NPC_Monkey(sf::Vector2f t_posStart, float t_patrolBoxWidth)
{
	// m_rectShape.setFillColor(sf::Color::Red);
	m_rectShape.setSize(sf::Vector2f(32.0f, 32.0f));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
	m_rectShape.setPosition(t_posStart);

	if (!m_spriteSheet.loadFromFile("ASSETS/PROJECT_SPRITES/enemy1.png"))
	{
		std::cout << "enemy1.png failed to load."; // 42x60
	}

	m_rectShape.setTexture(&m_spriteSheet);
	m_rectShape.setTextureRect(m_intRect);

	m_patrolBoxWidth 
}

NPC_Monkey::~NPC_Monkey(){}

void NPC_Monkey::move(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{
	if (m_patrolTimer <= 0.0f)
	{
		m_patrolTimer = m_patrolPeriod;
		// Set random location
		m_patrolDestination.x = Hlp::randomRange(t_patrolBoxWidth)
	}
	else
	{
		m_patrolTimer -= t_deltaTime.asSeconds();
	}

	// Move towards destination.

	m_desiredDirection = m_rectShape.getPosition() - m_patrolDestination;

	//sf::Vector2f newVelocity = t_desiredDir * M_SPEED_WALK * t_deltaTime.asSeconds();

	//sf::Vector2f testPos = m_rectShape.getPosition() + newVelocity;

	//testPos.x = testPos.x > SCREEN_WIDTH ? SCREEN_WIDTH : testPos.x;
	//testPos.x = testPos.x < 0 ? 0 : testPos.x;
	//testPos.y = testPos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : testPos.y;
	//testPos.y = testPos.y < 0 ? 0 : testPos.y;

	//m_rectShape.setPosition(testPos);

	//if (std::abs(t_desiredDir.x) > 0.01f || std::abs(t_desiredDir.y) > 0.01f)
	//{// We have player input
	//	if (std::abs(t_desiredDir.x) > std::abs(t_desiredDir.y))
	//	{// We're facing horizontal
	//		if (t_desiredDir.x > 0.0f)
	//		{// We're facing right
	//			m_intRect = { 18, 178, 42, 60 };
	//		}
	//		else
	//		{// We're facing left
	//			m_intRect = { 18, 92, 42, 60 };
	//		}
	//	}
	//	else
	//	{// We're facing vertical
	//		if (t_desiredDir.y > 0.0f)
	//		{// We're facing down
	//			m_intRect = { 18, 15, 42, 60 };

	//		}
	//		else
	//		{// We're facing up
	//			m_intRect = { 18, 258, 42, 60 };
	//		}
	//	}
	//}

	//m_rectShape.setTextureRect(m_intRect);
}
