#include "NPC_Monkey.h"

NPC_Monkey::NPC_Monkey(sf::Vector2f t_posStart, float t_patrolRadius)
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

	m_patrolRadius = t_patrolRadius;
}

NPC_Monkey::~NPC_Monkey(){}

void NPC_Monkey::onUpdate(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{
	move(t_deltaTime, t_playerPos);
}

void NPC_Monkey::move(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{
	if (m_patrolTimer <= 0.0f)
	{
		m_patrolTimer = m_patrolPeriod;
		// Set random coord.
		// std::cout << "Patrol Radius is: " << std::to_string(m_patrolRadius);
		m_patrolDestination.x = Hlp::randomRange(-m_patrolRadius, m_patrolRadius);
		m_patrolDestination.y = Hlp::randomRange(-m_patrolRadius, m_patrolRadius);
		std::cout << "New destination is: " << std::to_string(m_patrolDestination.x) << ":" << std::to_string(m_patrolDestination.y) << ".\n\n";
		// Turn coord into a normalised dir
		m_patrolDestination = Hlp::v2fGetNormal(m_patrolDestination);
		// Move in that random direction a random amount within radius range
		m_patrolDestination *= Hlp::randomRange(-m_patrolRadius, m_patrolRadius);
		m_patrolDestination += m_posStart; // Destination now relative to start pos
		
		m_circShape.setPosition(m_patrolDestination);
	}
	else
	{
		m_patrolTimer -= t_deltaTime.asSeconds();
	}

	 //Move towards destination.

	m_desiredDirection = m_patrolDestination - m_rectShape.getPosition();
	
	if (std::abs(m_desiredDirection.x) > 0.01f || std::abs(m_desiredDirection.y) > 0.01f)
	{
		m_desiredDirection = Hlp::v2fGetNormal(m_desiredDirection);

		sf::Vector2f newVelocity = m_desiredDirection * M_SPEED_WALK * t_deltaTime.asSeconds();

		sf::Vector2f testPos = m_rectShape.getPosition() + newVelocity;

		testPos.x = testPos.x > SCREEN_WIDTH ? SCREEN_WIDTH : testPos.x;
		testPos.x = testPos.x < 0 ? 0 : testPos.x;
		testPos.y = testPos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : testPos.y;
		testPos.y = testPos.y < 0 ? 0 : testPos.y;

		m_rectShape.setPosition(testPos);

		if (std::abs(m_desiredDirection.x) > 0.01f || std::abs(m_desiredDirection.y) > 0.01f) // Repeated here, change this!
		{// We have player input
			if (std::abs(m_desiredDirection.x) > std::abs(m_desiredDirection.y))
			{// We're facing horizontal
				if (m_desiredDirection.x > 0.0f)
				{// We're facing right
					m_intRect = { 18, 178, 42, 60 };
				}
				else
				{// We're facing left
					m_intRect = { 18, 92, 42, 60 };
				}
			}
			else
			{// We're facing vertical
				if (m_desiredDirection.y > 0.0f)
				{// We're facing down
					m_intRect = { 18, 15, 42, 60 };
				}
				else
				{// We're facing up
					m_intRect = { 18, 258, 42, 60 };
				}
			}
		}
		m_rectShape.setTextureRect(m_intRect);
	}
}
