#include "NPC_Visitor.h"

#include "Player.h" // FORWARD DEPENDENCY

namespace {
	const float M_SPEED_FOLLOW = 60.0f; // Follow speed for Visitor
	const float M_SPEED_FLEE = 95.0f; // Fleeing speed for Visitor
}

void NPC_Visitor::amRescued(sf::Time t_deltaTime)
{
	if (m_rescueTimer > 0)
	{
		m_rescueTimer -= t_deltaTime.asSeconds();
	}
	else
	{
		// std::cout << "Visitor now inactive.\n\n";
		m_myState = VisitorPreSpawn;
	}
}

NPC_Visitor::NPC_Visitor(sf::Vector2f t_posStart, Assets& t_assets, Player& t_player) : m_player{ t_player } //, NPC_Monkey& t_nearMonkey) : m_player{ t_player }, m_nearMonkey(t_nearMonkey)
{
	m_rectShape.setSize(sf::Vector2f(8.0f * SCREEN_SCALAR, 16.0f * SCREEN_SCALAR));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
	m_rectShape.setPosition(t_posStart);

	m_rectShape.setTexture(&t_assets.m_spriteSheet);
	m_rectShape.setTextureRect(m_intRect);

	m_posStart = t_posStart;

	m_speedCur = M_SPEED_FOLLOW;

	spawn();
}

NPC_Visitor::~NPC_Visitor(){}

void NPC_Visitor::onUpdate(sf::Time t_deltaTime)
{
	sf::Vector2f playerPos = m_player.m_rectShapeVis.getPosition();

	detect(playerPos);

	switch (m_myState)
	{
	case VisitorPreSpawn:
		// Rescue animation?
		//std::cout << "I'm in prespawn.\n\n";
		if (m_spawnTimer > 0)
		{
			m_spawnTimer -= t_deltaTime.asSeconds();
		}
		else
		{
			spawn();
		}
		break;
	case VisitorFresh:
		//std::cout << "I'm freshly spawned!\n\n";
		if (m_freshTimer > 0)
		{
			m_freshTimer -= t_deltaTime.asSeconds();
		}
		else
		{
			m_myState = VisitorCower;
		}
		cowering(t_deltaTime);
		break;
	case VisitorCower:
		cowering(t_deltaTime);
		break;
	case VisitorFollow:
		m_speedCur = M_SPEED_FOLLOW;
		// Follow code here
		follow(t_deltaTime, playerPos);
		break;
	case VisitorFlee:
		m_speedCur = M_SPEED_FLEE;
		flee(t_deltaTime);
		//std::cout << "I am fleeing!\n\n";
		if (m_fleeTimer > 0)
		{
			m_fleeTimer -= t_deltaTime.asSeconds();
		}
		else
		{
			m_myState = VisitorCower;
		}
		break;
	case VisitorRescue:
		amRescued(t_deltaTime);
		break;
	default:
		std::cout << "This visitor is in an unhandled state! Handle it!\n\n";
		break;
	}
}

void NPC_Visitor::detect(sf::Vector2f t_playerPos)
{
}

void NPC_Visitor::spawn()
{
	// Spawn in random position!
	sf::Vector2f newPos { Hlp::randomFloatRange(25, SCREEN_WIDTH-25), Hlp::randomFloatRange(SCREEN_HEIGHT * 0.20f, SCREEN_HEIGHT)};
	//sf::Vector2f newPos = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT) * 0.5f;
	m_rectShape.setPosition(newPos);
	m_freshTimer = M_FRESH_PERIOD;
	m_myState = VisitorState::VisitorFresh;
	m_speedCur = M_SPEED_FOLLOW;
}

void NPC_Visitor::follow(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{
	if (m_player.m_myState == PlayerVulnerable)
	{
		moveTo(t_deltaTime, t_playerPos);
	}
	else
	{
		m_myState = VisitorCower;
	}
}

void NPC_Visitor::startFlee(sf::Vector2f t_monkeyPos)
{
	m_fleeTimer = M_FLEE_PERIOD;
	m_fleeDestination = m_rectShape.getPosition() - t_monkeyPos;
	m_myState = VisitorFlee;
}

void NPC_Visitor::cowering(sf::Time t_deltaTime)
{

}

void NPC_Visitor::flee(sf::Time t_deltaTime)
{
	moveTo(t_deltaTime, m_fleeDestination);
}

void NPC_Visitor::rescue()
{
	m_rescueTimer = M_RESCUED_PERIOD;
	m_myState = VisitorRescue;
}



void NPC_Visitor::moveTo(sf::Time t_deltaTime, sf::Vector2f t_destination)
{	//Move towards destination.
	m_desiredDirection = t_destination - m_rectShape.getPosition();

	if (std::abs(m_desiredDirection.x) > m_movementThreshold || std::abs(m_desiredDirection.y) > m_movementThreshold)
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

void NPC_Visitor::animateSprite(sf::Time t_deltaTime)
{
	if (std::abs(m_desiredDirection.x) > std::abs(m_desiredDirection.y))
	{// We're facing horizontal
		if (m_desiredDirection.x > 0.0f)
		{// We're facing right
			m_intRect = { 0, 112, 8, 16 };
		}
		else
		{// We're facing left
			m_intRect = { 0, 96, 8, 16 };
		}
	}
	else
	{// We're facing vertical
		if (m_desiredDirection.y > 0.0f)
		{// We're facing down
			m_intRect = { 0, 64, 8, 16 };
		}
		else
		{// We're facing up
			m_intRect = { 0, 80, 8, 16 };
		}
	}
	m_rectShape.setTextureRect(m_intRect);
}

void NPC_Visitor::reset()
{
	m_speedCur = M_SPEED_FOLLOW;
	spawn();
}
