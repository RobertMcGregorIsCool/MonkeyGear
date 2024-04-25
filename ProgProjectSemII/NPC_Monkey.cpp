#include "NPC_Monkey.h"

#include "Player.h"

namespace {
	const float M_SPEED_WALK = 16.0f; // Walking speed for Monkey
	const float M_SPEED_RUN = 80.0f; // Running speed for Monkey
	const float M_BOUNDS_SCALAR = 0.95f;
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

	sf::Vector2f dist2Banana = VEC2F_ZERO;

	switch (m_myState)
	{
	case MonkeyGetBanana:
		m_speedCur = M_SPEED_RUN;
		chase(t_deltaTime, m_bananaPos);
		dist2Banana = m_bananaPos - m_rectShape.getPosition();
		if (Hlp::v2fGetMagnitude(dist2Banana) < 2.0f)
		{
			startEating(m_bananaPos);
		}
		break;
	case MonkeyEating:
		std::cout << "This monkey is eating! Animate it!\n\n";
		if (m_eating_timer > 0.0f)
		{
			m_eating_timer -= t_deltaTime.asSeconds();
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
		patrol(t_deltaTime);
		break;
	case MonkeyChase:
		detect(playerPos);
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

void NPC_Monkey::chase(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{// This needs to give move the players destination
	moveTo(t_deltaTime, t_playerPos);
}

void NPC_Monkey::touchPlayer()
{
	m_patrolDestination = m_posStart;
	m_myState = MonkeyPatrol;
}

void NPC_Monkey::seesBanana(sf::Vector2f t_bananaPos)
{
	std::cout << "Monkey see banana?\n\n";
	m_bananaPos = t_bananaPos;
	m_myState = MonkeyGetBanana;
}

void NPC_Monkey::startEating(sf::Vector2f t_bananaPos)
{
	m_myState = MonkeyState::MonkeyEating;
	m_eating_timer = M_EATING_PERIOD;
}

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

void NPC_Monkey::reset()
{
	m_rectShape.setPosition(m_posStart);
	m_myState = MonkeyState::MonkeyPatrol;
}
