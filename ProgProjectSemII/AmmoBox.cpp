/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#include "AmmoBox.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="t_assets">Ref to asset loader/container</param>
AmmoBox::AmmoBox(Assets& t_assets) : m_assets(t_assets)
{
	m_rectShape.setSize(sf::Vector2f(8.0f * SCREEN_SCALAR, 8.0f * SCREEN_SCALAR));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);

	m_rectShape.setTexture(&m_assets.m_spriteSheet);

	goPreSpawn();
}

AmmoBox::~AmmoBox(){} // Not used

/// <summary>
/// Called from Game Update, directs behavior based on state
/// </summary>
/// <param name="t_deltaTime">Deltatime</param>
void AmmoBox::onUpdate(sf::Time t_deltaTime)
{
	switch (m_myState)
	{
	case preSpawn:
		
		if (m_spawnTimer > 0)
		{
			m_spawnTimer -= t_deltaTime.asSeconds();
		}
		else
		{
			goGettable();
		}
		break;
	case gettable:
		if (m_gettable_timer > 0)
		{
			m_gettable_timer -= t_deltaTime.asSeconds();
			animate();
		}
		else
		{
			goExpiration();
		}
		break;
	case expiring:
		if (m_expiration_timer > 0)
		{
			m_expiration_timer -= t_deltaTime.asSeconds();
			animate();
		}
		else
		{
			goPreSpawn();
		}
	default:
		break;
	}
}

/// <summary>
/// Creates random range of time to wait before spawning, sets state to prespawn
/// </summary>
void AmmoBox::goPreSpawn()
{
	m_spawnTimer = Hlp::randomFloatRange(M_SPAWN_PERIOD_MIN, M_SPAWN_PERIOD_MAX);
	m_myState = AmmoBoxState::preSpawn;
}

/// <summary>
/// Sets state to 'gettable', starts in random position, gets random time for existing
/// </summary>
void AmmoBox::goGettable()
{
	// Spawn in random position!
	sf::Vector2f newPos { Hlp::randomFloatRange(0, SCREEN_WIDTH), Hlp::randomFloatRange(0, SCREEN_HEIGHT)};
	m_rectShape.setPosition(newPos);
	m_gettable_timer = Hlp::randomFloatRange(M_GETTABLE_PERIOD_MIN, M_GETTABLE_PERIOD_MIN);
	m_myState = AmmoBoxState::gettable;
}

/// <summary>
/// Sets state to expiring, resets timer
/// </summary>
void AmmoBox::goExpiration()
{
	m_expiration_timer = M_EXPIRATION_PERIOD;
	m_myState = AmmoBoxState::expiring;
}

/// <summary>
/// Animate gleam
/// </summary>
void AmmoBox::animate()
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

	m_intRect = { 80 + (m_currentFrame * M_FRAME_WIDTH), 64, 8, 8};
	m_rectShape.setTextureRect(m_intRect);
}
