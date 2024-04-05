

#include "Player.h"   // include Player header file

// Player function definitions here

Player::Player()
{
	// m_rectShape.setFillColor(sf::Color::Red);
	m_rectShape.setSize(sf::Vector2f(32.0f, 32.0f));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
	m_rectShape.setPosition(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	if (!m_spriteSheet.loadFromFile("ASSETS/PROJECT_SPRITES/player.png"))
	{
		std::cout << "player.png failed to load."; // 42x60
	}

	m_rectShape.setTexture(&m_spriteSheet);
	m_rectShape.setTextureRect(m_intRect);
}

Player::~Player()
{
}

void Player::move(sf::Time t_deltaTime, sf::Vector2f t_desiredDir)
{
	sf::Vector2f newVelocity = t_desiredDir * m_speedWalk * t_deltaTime.asSeconds();

	sf::Vector2f testPos = m_rectShape.getPosition() + newVelocity;

	testPos.x = testPos.x > SCREEN_WIDTH ? SCREEN_WIDTH : testPos.x;
	testPos.x = testPos.x < 0 ? 0 : testPos.x;
	testPos.y = testPos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : testPos.y;
	testPos.y = testPos.y < 0 ? 0 : testPos.y;

	m_rectShape.setPosition(testPos);

	if (std::abs(t_desiredDir.x) > 0.01f || std::abs(t_desiredDir.y) > 0.01f)
	{// We have player input
		if (std::abs(t_desiredDir.x) > std::abs(t_desiredDir.y))
		{// We're facing horizontal
			if (t_desiredDir.x > 0.0f)
			{// We're facing right
				std::cout << "Right\n\n";
				m_intRect = { 18, 178, 42, 60 };
			}
			else
			{// We're facing left
				std::cout << "Left\n\n";
				m_intRect = { 18, 92, 42, 60 };
			}
		}
		else
		{// We're facing vertical
			if (t_desiredDir.y > 0.0f)
			{// We're facing down
				std::cout << "Down\n\n";
				m_intRect = {18, 15, 42, 60};
				
			}
			else
			{// We're facing up
				std::cout << "Up\n\n";
				m_intRect = { 18, 258, 42, 60 };
			}
		}
	}
	
	m_rectShape.setTextureRect(m_intRect);
}
