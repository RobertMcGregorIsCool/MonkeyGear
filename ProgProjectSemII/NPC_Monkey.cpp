#include "NPC_Monkey.h"

#include "Player.h"

namespace {
	const float M_SPEED_WALK = 16.0f; // Walking speed for Monkey
	const float M_SPEED_RUN = 80.0f; // Running speed for Monkey
}

NPC_Monkey::NPC_Monkey(sf::Vector2f t_posStart, float t_patrolRadius, Assets& t_assets, Player& t_player) : m_player{t_player}
{
	m_rectShape.setSize(sf::Vector2f(8.0f * SCREEN_SCALAR, 16.0f * SCREEN_SCALAR));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
	m_rectShape.setPosition(t_posStart);

	m_rectShape.setTexture(&t_assets.m_spriteSheet);
	m_rectShape.setTextureRect(m_intRect);

	m_posStart = t_posStart;
	m_patrolRadius = t_patrolRadius;

	m_speedCur = M_SPEED_WALK;
}

NPC_Monkey::~NPC_Monkey(){}

void NPC_Monkey::onUpdate(sf::Time t_deltaTime)
{
	sf::Vector2f playerPos = m_player.m_rectShapeVis.getPosition();

	detect(playerPos);

	switch (myState)
	{
	case MonkeyNone:
		std::cout << "This monkey is in an unhandled state! Handle it!\n\n";
		break;
	case MonkeyPatrol:
		m_speedCur = M_SPEED_WALK;
		patrol(t_deltaTime);
		break;
	case MonkeyChase:
		m_speedCur = M_SPEED_RUN;
		chase(t_deltaTime, playerPos);
		break;
	default:
		std::cout << "This monkey is in an unhandled state! Handle it!\n\n";
		break;
	}
}

void NPC_Monkey::detect(sf::Vector2f t_playerPos)
{
	float detectDistance = Hlp::v2fGetMagnitude(m_rectShape.getPosition() - t_playerPos);

	if (detectDistance <= m_detectRadiusCur && m_player.m_myState == PlayerState::PlayerVulnerable)
	{
		if (myState != MonkeyState::MonkeyChase)
		{
			myState = MonkeyState::MonkeyChase;
		}
	}
	else
	{
		if (myState == MonkeyState::MonkeyChase)
		{
			myState = MonkeyState::MonkeyPatrol;
		}
	}
}

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
	
	move(t_deltaTime, m_patrolDestination);
}

void NPC_Monkey::chase(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{// This needs to give move the players destination
	move(t_deltaTime, t_playerPos);
}

void NPC_Monkey::move(sf::Time t_deltaTime, sf::Vector2f t_destination)
{//Move towards destination.
	m_desiredDirection = t_destination - m_rectShape.getPosition();
	
	if (std::abs(m_desiredDirection.x) > 1.0f || std::abs(m_desiredDirection.y) > 1.0f)
	{
		animateSprite(t_deltaTime);

		m_desiredDirection = Hlp::v2fGetNormal(m_desiredDirection);

		sf::Vector2f newVelocity = m_desiredDirection * m_speedCur * t_deltaTime.asSeconds();

		sf::Vector2f testPos = m_rectShape.getPosition() + newVelocity;

		testPos.x = testPos.x > SCREEN_WIDTH ? SCREEN_WIDTH : testPos.x;
		testPos.x = testPos.x < 0 ? 0 : testPos.x;
		testPos.y = testPos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : testPos.y;
		testPos.y = testPos.y < 0 ? 0 : testPos.y;

		m_rectShape.setPosition(testPos);	
	}
}

void NPC_Monkey::animateSprite(sf::Time t_deltaTime)
{
	if (std::abs(m_desiredDirection.x) > std::abs(m_desiredDirection.y))
	{// We're facing horizontal
		if (m_desiredDirection.x > 0.0f)
		{// We're facing right
			m_intRect = { 0, 176, 8, 16 };
		}
		else
		{// We're facing left
			m_intRect = { 0, 160, 8, 16 };
		}
	}
	else
	{// We're facing vertical
		if (m_desiredDirection.y > 0.0f)
		{// We're facing down
			m_intRect = { 0, 128, 8, 16 };
		}
		else
		{// We're facing up
			m_intRect = { 0, 144, 8, 16 };
		}
	}
	m_rectShape.setTextureRect(m_intRect);
}
