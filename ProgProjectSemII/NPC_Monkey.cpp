/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#include "NPC_Monkey.h"

#include "Player.h"

namespace { // These values are here as I need to initialise the creatures through a vector pushback
	const float M_SPEED_WALK = 16.0f; // Walking speed for Monkey
	const float M_SPEED_RUN = 80.0f; // Running speed for Monkey
	const float M_BOUNDS_SCALAR = 0.95f;
}

NPC_Monkey::NPC_Monkey(sf::Vector2f t_posStart, float t_patrolRadius, Assets& t_assets, Player& t_player) : m_player{t_player}
{
	m_rectShape.setSize(sf::Vector2f(16.0f * SCREEN_SCALAR, 16.0f * SCREEN_SCALAR));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
	m_rectShape.setPosition(t_posStart);

	m_rectShape.setTexture(&t_assets.m_spriteSheet);
	m_rectShape.setTextureRect(m_intRect);

	m_posStart = t_posStart;
	m_patrolRadius = t_patrolRadius;

	m_speedCur = M_SPEED_WALK;
}

NPC_Monkey::~NPC_Monkey(){}

/// <summary>
/// Called from Level::Update, powers monkey
/// </summary>
/// <param name="t_deltaTime">Delta Time</param>
void NPC_Monkey::onUpdate(sf::Time t_deltaTime)
{
	sf::Vector2f playerPos = m_player.m_rectShapeVis.getPosition();

	sf::Vector2f dist2Banana = VEC2F_ZERO;

	switch (m_myState)
	{
	case MonkeySeekBanana:
		if (m_seek_banana_timer > 0.0f)
		{
			m_seek_banana_timer -= t_deltaTime.asSeconds();
			animateSprite(t_deltaTime);
			chase(t_deltaTime, m_bananaPos);
			dist2Banana = m_bananaPos - m_rectShape.getPosition();
			if (Hlp::v2fGetMagnitude(dist2Banana) < 2.0f)
			{
				startEating(m_bananaPos);
			}
		}
		else
		{
			m_seek_banana_timer = M_SEEK_BANANA_PERIOD;
			m_myState = MonkeyState::MonkeyPatrol;
		}
		break;
	case MonkeyEating:
		if (m_eating_timer > 0.0f)
		{
			m_eating_timer -= t_deltaTime.asSeconds();
			animateSprite(t_deltaTime);
		}
		else
		{
			m_eating_timer = M_EATING_PERIOD;
			m_myState = MonkeyState::MonkeyPatrol;
		}
		break;
	case MonkeyPatrol:
		detect(playerPos);
		m_speedCur = M_SPEED_WALK;
		m_spriteFrameIncrement = 0.1f;
		patrol(t_deltaTime);
		break;
	case MonkeyChase:
		detect(playerPos);
		m_speedCur = M_SPEED_RUN;
		m_spriteFrameIncrement = 0.3f;
		chase(t_deltaTime, playerPos);
		break;
	case MonkeyCatch:
		if (m_catch_timer > 0.0f)
		{
			m_catch_timer -= t_deltaTime.asSeconds();
			animateSprite(t_deltaTime);
		}
		else
		{
			m_catch_timer = M_CATCH_PERIOD;
			m_myState = MonkeyState::MonkeyPatrol;
		}
		break;
	default:
		std::cout << "This monkey is in an unhandled state! Handle it!\n\n";
		break;
	}
}

/// <summary>
/// Check radius for nearby player, called from patrol state
/// </summary>
/// <param name="t_playerPos">Player current position</param>
void NPC_Monkey::detect(sf::Vector2f t_playerPos)
{
	float detectDistance = Hlp::v2fGetMagnitude(m_rectShape.getPosition() - t_playerPos);

	if (detectDistance <= m_detectRadiusCur && m_player.m_myState == PlayerState::PlayerVulnerable)
	{
		if (m_myState != MonkeyState::MonkeyChase)
		{
			m_myState = MonkeyState::MonkeyChase;
		}
	}
	else
	{
		if (m_myState == MonkeyState::MonkeyChase)
		{
			m_myState = MonkeyState::MonkeyPatrol;
		}
	}
}

/// <summary>
/// Make monkey patrol environment
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
void NPC_Monkey::patrol(sf::Time t_deltaTime)
{// This needs to time the patrol and give move it's destination
	if (m_patrolTimer <= 0.0f)
	{
		m_patrolTimer = Hlp::randomFloatRange(M_PATROL_PERIOD_MIN, M_PATROL_PERIOD_MAX);
		// Set random coord.
		m_patrolDestination.x = Hlp::randomFloatRange(-m_patrolRadius, m_patrolRadius);
		m_patrolDestination.y = Hlp::randomFloatRange(-m_patrolRadius, m_patrolRadius);
		// Turn coord into a normalised dir
		m_patrolDestination = Hlp::v2fGetNormal(m_patrolDestination);
		// Move in that random direction a random amount within radius range
		m_patrolDestination *= Hlp::randomFloatRange(-m_patrolRadius, m_patrolRadius);

		m_patrolDestination += m_posStart; // Destination now relative to start pos
	}
	else
	{
		m_patrolTimer -= t_deltaTime.asSeconds();
	}
	m_circShape.setPosition(m_patrolDestination);
	
	moveTo(t_deltaTime, m_patrolDestination);
}

/// <summary>
/// Not totally sure why I don't just use moveTo here, tbh.
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
/// <param name="t_playerPos">Player's current position</param>
void NPC_Monkey::chase(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{// This needs to give move the players destination
	moveTo(t_deltaTime, t_playerPos);
}

/// <summary>
/// On touching the player, start fight and set destination to home.
/// </summary>
void NPC_Monkey::touchPlayer()
{
	m_patrolDestination = m_posStart;
	m_myState = MonkeyCatch;
}

/// <summary>
/// On detecting a banana, set state to seekingBanana, 
/// change move speed and animate speed to run
/// </summary>
/// <param name="t_bananaPos">current position of relelvant banana</param>
void NPC_Monkey::seekBanana(sf::Vector2f t_bananaPos)
{
	m_bananaPos = t_bananaPos;
	m_myState = MonkeySeekBanana;

	m_speedCur = M_SPEED_RUN;
	m_spriteFrameIncrement = 0.1f;
}

/// <summary>
/// If the monkey is close enough to a banana, start eating it.
/// </summary>
/// <param name="t_bananaPos">Banana current position - THIS INFORMATION ISN'T USED!!!</param>
void NPC_Monkey::startEating(sf::Vector2f t_bananaPos)
{
	m_myState = MonkeyState::MonkeyEating;
	m_eating_timer = M_EATING_PERIOD;
}

/// <summary>
/// Move monkey to specific destination
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
/// <param name="t_destination">Current destination</param>
void NPC_Monkey::moveTo(sf::Time t_deltaTime, sf::Vector2f t_destination)
{//Move towards destination.
	m_desiredDirection = t_destination - m_rectShape.getPosition();
	
	if (std::abs(m_desiredDirection.x) > 1.0f || std::abs(m_desiredDirection.y) > 1.0f)
	{
		animateSprite(t_deltaTime);

		m_desiredDirection = Hlp::v2fGetNormal(m_desiredDirection);

		sf::Vector2f newVelocity = m_desiredDirection * m_speedCur * t_deltaTime.asSeconds();

		sf::Vector2f testPos = m_rectShape.getPosition() + newVelocity;

		testPos.x = testPos.x > SCREEN_WIDTH * M_BOUNDS_SCALAR ? SCREEN_WIDTH * M_BOUNDS_SCALAR : testPos.x;
		testPos.x = testPos.x < 1? 1 + M_BOUNDS_SCALAR: testPos.x;
		testPos.y = testPos.y > SCREEN_HEIGHT * M_BOUNDS_SCALAR ? SCREEN_HEIGHT * M_BOUNDS_SCALAR : testPos.y;
		testPos.y = testPos.y < 1? 1 + M_BOUNDS_SCALAR: testPos.y;

		m_rectShape.setPosition(testPos);	
	}
}

/// <summary>
/// Play appropriate animation for state
/// </summary>
/// <param name="t_deltaTime">DeltaTime</param>
void NPC_Monkey::animateSprite(sf::Time t_deltaTime)
{
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

	switch (m_myState)
	{
	case MonkeySeekBanana:
		animateMove();
		break;
	case MonkeyEating:
		animateEat();
		break;
	case MonkeyPatrol:
		animateMove();
		break;
	case MonkeyChase:
		animateMove();
		break;
	case MonkeyCatch:
		animateCatch();
		break;
	default:
		break;
	}

	m_rectShape.setTextureRect(m_intRect);
}

/// <summary>
/// Play animation for moving in specific direction
/// </summary>
void NPC_Monkey::animateMove()
{
	if (std::abs(m_desiredDirection.x) > 3.00f || std::abs(m_desiredDirection.y) > 3.00f)
	{
		if (std::abs(m_desiredDirection.x) > std::abs(m_desiredDirection.y))
		{// We're facing horizontal
			if (m_desiredDirection.x > 0.0f)
			{// We're facing right
				m_intRect = { 64 + (currentFrame * M_FRAME_WIDTH), 112, 16, 16 };
			}
			else
			{// We're facing left
				m_intRect = { 64 + (currentFrame * M_FRAME_WIDTH), 96, 16, 16 };
			}
		}
		else
		{// We're facing vertical
			if (m_desiredDirection.y > 0.0f)
			{// We're facing down
				m_intRect = { 0 + (currentFrame * M_FRAME_WIDTH), 96, 16, 16 };
			}
			else
			{// We're facing up
				m_intRect = { 0 + (currentFrame * M_FRAME_WIDTH), 112, 16, 16 };
			}
		}
		m_desiredDirPrev = m_desiredDirection;
	}
	else
	{
		if (std::abs(m_desiredDirPrev.x) > std::abs(m_desiredDirPrev.y))
		{// We're facing horizontal
			if (m_desiredDirPrev.x > 0.0f)
			{// We're facing right
				m_intRect = { 112, 32, 16, 16 };
			}
			else
			{// We're facing left
				m_intRect = { 112, 48, 16, 16 };
			}
		}
		else
		{// We're facing vertical
			if (m_desiredDirPrev.y > 0.0f)
			{// We're facing down
				m_intRect = { 112, 0, 16, 16 };
			}
			else
			{// We're facing up
				m_intRect = { 112, 16, 16, 16 };
			}
		}
	}
}

/// <summary>
/// Play animation for eating
/// </summary>
void NPC_Monkey::animateEat()
{
	m_intRect = { 64 + (currentFrame * M_FRAME_WIDTH), 80, 16, 16 };
}

/// <summary>
/// Play animation for catch/fight
/// </summary>
void NPC_Monkey::animateCatch()
{
	m_intRect = { 0 + (currentFrame * M_FRAME_WIDTH), 80, 16, 16 };
}

/// <summary>
/// Reset Monkey to initial values
/// </summary>
void NPC_Monkey::reset()
{
	m_rectShape.setPosition(m_posStart);
	m_myState = MonkeyState::MonkeyPatrol;
}
