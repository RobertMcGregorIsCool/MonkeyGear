

#include "Player.h"   // include Player header file

// Player function definitions here
Player::Player(Assets& t_assets, sf::Vector2f t_posStart) : m_assets{t_assets}
{
	m_rectShapeVis.setSize(sf::Vector2f(8.0f * SCREEN_SCALAR, 16.0f * SCREEN_SCALAR));
	m_rectShapeVis.setOrigin(m_rectShapeVis.getSize() * 0.5f);
	m_rectShapeVis.setPosition(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	m_rectShapeCol.setSize(m_rectShapeVis.getSize() * M_COLLIDE_SCALE);
	m_rectShapeCol.setOrigin(m_rectShapeCol.getSize() * 0.5f);
	m_rectShapeCol.setPosition(m_rectShapeVis.getPosition());

	m_rectShapeVis.setTexture(&t_assets.m_spriteSheet);
	m_rectShapeVis.setTextureRect(m_intRect);

	m_rectShapeCol.setOutlineColor(sf::Color::Red);
	m_rectShapeCol.setFillColor(sf::Color::Transparent);
	m_rectShapeCol.setOutlineThickness(1.0f);
}

Player::~Player(){}

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

	sf::Vector2f testPos = m_rectShapeVis.getPosition() + newVelocity;

	// Screen bounds test
	testPos.x = testPos.x > SCREEN_WIDTH ? SCREEN_WIDTH : testPos.x;
	testPos.x = testPos.x < 0 ? 0 : testPos.x;
	testPos.y = testPos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : testPos.y;
	testPos.y = testPos.y < 0 ? 0 : testPos.y;

	m_rectShapeVis.setPosition(testPos);
	m_rectShapeCol.setPosition(m_rectShapeVis.getPosition());

	// Orientation test from movement
	if (std::abs(m_desiredDir.x) > 0.01f || std::abs(m_desiredDir.y) > 0.01f)
	{// We have player input
		if (std::abs(m_desiredDir.x) > std::abs(m_desiredDir.y))
		{// We're facing horizontal
			if (m_desiredDir.x > 0.0f)
			{// We're facing right
				m_intRect = { 0, 32, 8, 16 };
			}
			else
			{// We're facing left
				m_intRect = { 0, 48, 8, 16 };
			}
		}
		else
		{// We're facing vertical
			if (m_desiredDir.y > 0.0f)
			{// We're facing down
				m_intRect = { 0, 0, 8, 16 };
				
			}
			else
			{// We're facing up
				m_intRect = { 0, 16, 8, 16 };
			}
		}
	}
	
	m_rectShapeVis.setTextureRect(m_intRect);
}
