/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#include "Player.h"   // include Player header file

#include "Render.h"	// FORWARD DEPENDANCY - need to use functions
#include "Game.h"	// FORWARD DEPENDENCY - need to use functions

// Player function definitions here
Player::Player(Assets& t_assets, sf::Vector2f t_posStart, Render& t_render) : m_assets{t_assets}, m_render{t_render}
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

	for (int i = 0; i < M_DEF_BANANAS; i++)
	{
		m_bananaBullets.push_back(Banana{ m_assets });
		setBananas(1);
	}
}

Player::~Player(){}

/// <summary>
/// Input sets desired direction
/// </summary>
/// <param name="t_desiredDir">Which way we want to go</param>
void Player::setDesiredDir(sf::Vector2f t_desiredDir)
{
	m_desiredDir = t_desiredDir;
}

/// <summary>
/// Powers player, called from Level::OnUpdate
/// </summary>
/// <param name="t_deltaTime">Delta Time</param>
void Player::onUpdate(sf::Time t_deltaTime)
{
	switch (m_myState)
	{
	case PlayerNone: // Not sure I need this?
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

	moveDir(t_deltaTime);

	for (int i = 0; i < static_cast<int>(m_bananaBullets.size()); i++)
	{
		if (m_bananaBullets[i].m_myState != BananaState::BananaInactive)
		{
			m_bananaBullets[i].update(t_deltaTime);
		}
	}
}

/// <summary>
/// Sets player lives, based on collision with Monkeys (in Levels)
/// </summary>
/// <param name="t_addedValue">Adding or subtracting this amount from m_curLives</param>
/// <param name="t_render">Ref to render for updating hud</param>
/// <param name="t_game">Ref to Game - not sure we need this? </param>
void Player::setLives(int t_addedValue, Render& t_render, Game& t_game)
{
	m_curLives += t_addedValue;

	if (m_curLives >= M_DEF_LIVES) m_curLives = M_DEF_LIVES;

	if (m_curLives <= 0) 
	{
		m_curLives = 0;
	}
	else if (t_addedValue < 0)
	{
		m_myState = PlayerState::PlayerInvulnerable;
		m_rectShapeVis.setPosition(m_posStart);
	}

	t_render.setHudLives(m_curLives);
}

/// <summary>
/// Getter for current lives
/// </summary>
/// <returns>Current lives</returns>
int Player::getLives()
{
	return m_curLives;
}

/// <summary>
/// Setter for player ammo
/// </summary>
/// <param name="t_addedValue">Added/subtracted value for ammo</param>
void Player::setBananas(int t_addedValue)
{
	m_curBananas += t_addedValue;

	if (m_curBananas >= M_DEF_BANANAS) m_curBananas = M_DEF_BANANAS;

	if (m_curBananas <= 0)
	{
		m_curBananas = 0;
	}

	m_render.setHudBananas(m_curBananas);
}

/// <summary>
/// Throw the bananana!
/// </summary>
/// <param name="t_throwDirection">Direction of throw</param>
void Player::throwBanana(sf::Vector2f t_throwDirection)
{
	if (m_curBananas > 0)
	{
		for (int i = 0; i < static_cast<int>(m_bananaBullets.size()); i++)
		{
			if (m_bananaBullets[i].m_myState == BananaState::BananaInactive)
			{
				m_bananaBullets[i].throwAtDir(m_rectShapeVis.getPosition(), t_throwDirection);
				setBananas(-1);
				break;
			}
		}
	}	
}

/// <summary>
/// Return player to default value
/// </summary>
void Player::reset()
{
	m_curLives = M_DEF_LIVES;
	m_curBananas = M_DEF_BANANAS;
	m_myState = PlayerState::PlayerInvulnerable;
	m_rectShapeVis.setPosition(m_posStart);
}

/// <summary>
/// Called from onUpdate, moves player in direction
/// </summary>
/// <param name="t_deltaTime">Delta Time</param>
void Player::moveDir(sf::Time t_deltaTime)
{
	int currentFrame = 0;
	const int FRAME_WIDTH = 8;
	const int FRAME_HEIGHT = 16;

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
		m_spriteFrameCounter += m_spriteFrameIncrement; // Increase spriteFrame

		currentFrame = static_cast<int>(m_spriteFrameCounter); // Truncate to int
		if (currentFrame >= M_SPRITE_TOTAL_ANIM_FRAMES)
		{// If more than max frames in cycle,
			currentFrame = 0;	// ...reset to 0.
			m_spriteFrameCounter = 0.0f;
		}
		if (currentFrame != m_spriteFrame)
		{// If incremented truncated frame is not the same as current frame,
			m_spriteFrame = currentFrame; // make current frame incremented frame.
		}

		if (std::abs(m_desiredDir.x) > std::abs(m_desiredDir.y))
		{// We're facing horizontal
			if (m_desiredDir.x > 0.0f)
			{// We're facing right
				m_intRect = { 8 + (currentFrame * FRAME_WIDTH), 32, 8, 16 };
			}
			else
			{// We're facing left
				m_intRect = { 8 + (currentFrame * FRAME_WIDTH), 48, 8, 16 };
			}
		}
		else
		{// We're facing vertical
			if (m_desiredDir.y > 0.0f)
			{// We're facing down
				m_intRect = { 8 + (currentFrame * FRAME_WIDTH), 0, 8, 16 };
			}
			else
			{// We're facing up
				m_intRect = { 8 + (currentFrame * FRAME_WIDTH), 16, 8, 16 };
			}
		}
		m_desiredDirPrev = m_desiredDir;
	}
	else
	{
		if (std::abs(m_desiredDirPrev.x) > std::abs(m_desiredDirPrev.y))
		{// We're facing horizontal
			if (m_desiredDirPrev.x > 0.0f)
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
			if (m_desiredDirPrev.y > 0.0f)
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
