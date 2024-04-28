/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#include "Banana.h"

Banana::Banana(Assets& t_assets) : m_assets(t_assets)
{
	m_rectShape.setSize(sf::Vector2f(8.0f * SCREEN_SCALAR, 8.0f * SCREEN_SCALAR));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
	m_rectShape.setTexture(&m_assets.m_spriteSheet);
	m_rectShape.setTextureRect(m_intRect);
}

Banana::~Banana(){}

/// <summary>
/// Called from Level, branches behavior based on state
/// </summary>
/// <param name="t_deltaTime"></param>
void Banana::update(sf::Time t_deltaTime)
{
	switch (m_myState)
	{
	case BananaInactive:
		// Do nowt.
		break;
	case BananaThrown:
		if (m_thrownTimer > 0.0f)
		{
			m_thrownTimer -= t_deltaTime.asSeconds();
			moveDir(t_deltaTime);
			animate(t_deltaTime);
		}
		else
		{
			m_thrownTimer = M_THROWN_PERIOD;
			m_myState = BananaAtRest;
			m_intRect = { 64, 72, 8, 8 };
			m_rectShape.setTextureRect(m_intRect);
		}
		break;
	case BananaAtRest:
		if (m_atRestTimer > 0.0f)
		{
			m_atRestTimer -= t_deltaTime.asSeconds();
		}
		else
		{
			m_atRestTimer = M_AT_REST_PERIOD;
			m_myState = BananaInactive;
		}
		break;
	default:
		break;
	}
}

/// <summary>
/// Player throws banana in spec'd direction
/// </summary>
/// <param name="t_posStart">Start point for Banana</param>
/// <param name="t_throwDirection">Direction of throw</param>
void Banana::throwAtDir(sf::Vector2f t_posStart, sf::Vector2f t_throwDirection)
{
	m_thrownTimer = M_THROWN_PERIOD;
	m_rectShape.setPosition(t_posStart);
	m_throwDirection = t_throwDirection;
	m_myState = BananaThrown;
}

/// <summary>
/// Move in spec'd direction, called from Update with BananaThrown state
/// </summary>
/// <param name="t_deltaTime">Deltatime</param>
void Banana::moveDir(sf::Time t_deltaTime)
{
	sf::Vector2f newVelocity = m_throwDirection * M_THROWN_SPEED * t_deltaTime.asSeconds();

	sf::Vector2f testPos = m_rectShape.getPosition() + newVelocity;

	// Screen bounds test - rewrite to stop banana on bounds.
	testPos.x = testPos.x > SCREEN_WIDTH ? SCREEN_WIDTH : testPos.x;
	testPos.x = testPos.x < 0 ? 0 : testPos.x;
	testPos.y = testPos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : testPos.y;
	testPos.y = testPos.y < 0 ? 0 : testPos.y;

	m_rectShape.setPosition(testPos);
	m_circShapeAttractZone.setPosition(m_rectShape.getPosition());
}

/// <summary>
/// Called from update, plays appropriate animation depending on state
/// </summary>
/// <param name="t_deltaTime">Deltatime - possibly get rid of this? </param>
void Banana::animate(sf::Time t_deltaTime)
{
	m_spriteFrameCounter += m_spriteFrameIncrement; // Increase spriteFrame

	m_currentFrame = static_cast<int>(m_spriteFrameCounter); // Truncate to int
	if (m_currentFrame >= M_SPRITE_TOTAL_ANIM_FRAMES)
	{// If more than max frames in cycle,
		m_currentFrame = 0;	// ...reset to 0.
		m_spriteFrameCounter = 0.0f;
	}
	if (m_currentFrame != m_spriteFrame)
	{// If incremented truncated frame is not the same as current frame,
		m_spriteFrame = m_currentFrame; // make current frame incremented frame.
	}

	switch (m_myState)
	{
	case BananaInactive:
		break;
	case BananaThrown:
		m_intRect = { 80 + (m_currentFrame * M_FRAME_WIDTH), 72, 8, 8 };
		break;
	case BananaAtRest:
		m_intRect = { 64, 72, 8, 8 };
		break;
	default:
		break;
	}
	m_rectShape.setTextureRect(m_intRect);
}

void Banana::reset()
{
	m_myState == BananaInactive;
}
