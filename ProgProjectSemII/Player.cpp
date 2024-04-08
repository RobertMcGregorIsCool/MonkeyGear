

#include "Player.h"   // include Player header file

// Player function definitions here

Player::Player(sf::Vector2f t_posStart)
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

void Player::setDesiredDir(sf::Vector2f t_desiredDir)
{
	m_desiredDir = t_desiredDir;
}

void Player::onUpdate(sf::Time t_deltaTime)
{
	move(t_deltaTime);
}

void Player::move(sf::Time t_deltaTime) // sf::Vector2f t_desiredDir,
{
	sf::Vector2f newVelocity = m_desiredDir * M_SPEED_WALK * t_deltaTime.asSeconds();

	sf::Vector2f testPos = m_rectShape.getPosition() + newVelocity;

	// Screen bounds test
	testPos.x = testPos.x > SCREEN_WIDTH ? SCREEN_WIDTH : testPos.x;
	testPos.x = testPos.x < 0 ? 0 : testPos.x;
	testPos.y = testPos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : testPos.y;
	testPos.y = testPos.y < 0 ? 0 : testPos.y;

	m_rectShape.setPosition(testPos);

	// Orientation test from movement
	if (std::abs(m_desiredDir.x) > 0.01f || std::abs(m_desiredDir.y) > 0.01f)
	{// We have player input
		if (std::abs(m_desiredDir.x) > std::abs(m_desiredDir.y))
		{// We're facing horizontal
			if (m_desiredDir.x > 0.0f)
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
			if (m_desiredDir.y > 0.0f)
			{// We're facing down
				m_intRect = {18, 15, 42, 60};
				
			}
			else
			{// We're facing up
				m_intRect = { 18, 258, 42, 60 };
			}
		}
	}
	
	m_rectShape.setTextureRect(m_intRect);
}
