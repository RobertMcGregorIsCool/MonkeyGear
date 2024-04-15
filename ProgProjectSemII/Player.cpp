#include "Player.h"   // include Player header file

#include "Render.h"	// FORWARD DEPENDANCY - need to use functions
#include "Game.h"	// FORWARD DEPENDENCY - need to use functions

// Player function definitions here
Player::Player(Assets& t_assets, sf::Vector2f t_posStart) : m_assets{t_assets}
{
	m_posStart = t_posStart;

	m_rectShapeVis.setSize(sf::Vector2f(8.0f * SCREEN_SCALAR, 16.0f * SCREEN_SCALAR));
	m_rectShapeVis.setOrigin(m_rectShapeVis.getSize() * 0.5f);
	m_rectShapeVis.setPosition(m_posStart);

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
	switch (m_myState)
	{
	case MonkeyNone:
		std::cout<< "Player is in an unhandled state!Handle it!\n\n";
		break;
	case PlayerVulnerable:
		break;
	case PlayerInvulnerable:
		if (m_invulTimer > 0)
		{
			m_invulTimer -= t_deltaTime.asSeconds();
		}
		else
		{
			m_invulTimer = M_INVUL_PERIOD;
			m_myState = PlayerState::PlayerVulnerable;
		}
		break;
	default:
		std::cout << "Player is in an unhandled state!Handle it!\n\n";
		break;
	}

	move(t_deltaTime);
}

void Player::setLives(int t_addedValue, Render& t_render, Game& t_game)
{
	m_curLives += t_addedValue;

	if (m_curLives >= M_DEF_LIVES) m_curLives = M_DEF_LIVES;

	if (m_curLives <= 0) 
	{
		m_curLives = 0;
		
		t_game.reset();
		// Player is dead.
	}
	else if (t_addedValue < 0)
	{
		m_myState = PlayerState::PlayerInvulnerable;
		m_rectShapeVis.setPosition(m_posStart);
	}

	t_render.setHudLives(m_curLives);
}

void Player::setFruit(int t_addedValue)
{
	m_curFruit += t_addedValue;
}

void Player::reset()
{
	m_curLives = M_DEF_LIVES;
	m_curFruit = M_DEF_FRUIT;
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
	m_rectShapeCol.setPosition(m_rectShapeVis.getPosition()); // Set collision to same place as visible body

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
