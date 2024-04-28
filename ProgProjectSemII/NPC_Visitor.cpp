/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#include "NPC_Visitor.h"

#include "Player.h" // FORWARD DEPENDENCY

namespace {
	const float M_SPEED_FOLLOW = 60.0f; // Follow speed for Visitor
	const float M_SPEED_FLEE = 95.0f; // Fleeing speed for Visitor
	const float M_SPEED_BASH = 140.0f;
}

/// <summary>
/// If rescued, animate celebration and then disappear
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
void NPC_Visitor::amRescued(sf::Time t_deltaTime)
{
	animateSprite(t_deltaTime);
	if (m_rescueTimer > 0)
	{
		m_rescueTimer -= t_deltaTime.asSeconds();
	}
	else
	{
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

/// <summary>
/// Called from Level::OnUpdate, powers visitor
/// </summary>
/// <param name="t_deltaTime">Delta Time</param>
void NPC_Visitor::onUpdate(sf::Time t_deltaTime)
{
	sf::Vector2f playerPos = m_player.m_rectShapeVis.getPosition();

	switch (m_myState)
	{
	case VisitorPreSpawn:
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
		follow(t_deltaTime, playerPos);
		break;
	case VisitorFlee:
		m_speedCur = M_SPEED_FLEE;
		flee(t_deltaTime);
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

/// <summary>
/// Spawn in random position!
/// </summary>
void NPC_Visitor::spawn()
{
	sf::Vector2f newPos { Hlp::randomFloatRange(25, SCREEN_WIDTH-25), Hlp::randomFloatRange(SCREEN_HEIGHT * 0.40f, SCREEN_HEIGHT)};
	m_rectShape.setPosition(newPos);
	m_spriteFrameIncrement = 0.3f;
	m_freshTimer = M_FRESH_PERIOD;
	m_myState = VisitorState::VisitorFresh;
	m_speedCur = M_SPEED_FOLLOW;
}

/// <summary>
/// Begin following player, change state and speed
/// </summary>
void NPC_Visitor::startFollow()
{
	m_speedCur = M_SPEED_FOLLOW;
	m_myState = VisitorFollow;
}

/// <summary>
/// Follow player
/// </summary>
/// <param name="t_deltaTime">Delta Time</param>
/// <param name="t_playerPos">Current player position</param>
void NPC_Visitor::follow(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{
	m_spriteFrameIncrement = 0.3f;
	if (m_player.m_myState == PlayerVulnerable)
	{
		moveTo(t_deltaTime, t_playerPos);
	}
	else
	{
		m_myState = VisitorCower;
	}
}

/// <summary>
/// Begin running away!
/// </summary>
/// <param name="t_monkeyPos">Current position of monkey</param>
void NPC_Visitor::startFlee(sf::Vector2f t_monkeyPos)
{
	m_spriteFrameIncrement = 0.5f;
	m_fleeTimer = M_FLEE_PERIOD;
	m_fleeDestination = m_rectShape.getPosition() - t_monkeyPos;
	m_myState = VisitorFlee;
}

/// <summary>
/// Start worrying!
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
void NPC_Visitor::cowering(sf::Time t_deltaTime)
{
	m_spriteFrameIncrement = 0.05f;
	animateSprite(t_deltaTime);
}

/// <summary>
/// Run away, called from state stwitch
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
void NPC_Visitor::flee(sf::Time t_deltaTime)
{
	moveTo(t_deltaTime, m_fleeDestination);
}

/// <summary>
/// If in rescue zone, reset rescue timer, change sprite speed, change state to rescued!
/// </summary>
void NPC_Visitor::rescue()
{
	m_rescueTimer = M_RESCUED_PERIOD;
	m_spriteFrameIncrement = 0.1f;
	m_myState = VisitorRescue;
}

/// <summary>
/// If hit by a thrown banana...
/// </summary>
void NPC_Visitor::bananaBash()
{
	m_speedCur = M_SPEED_BASH;
	m_spriteFrameIncrement = 0.9f;
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

/// <summary>
/// Power sprite animation, branch based on state
/// </summary>
/// <param name="t_deltaTime">Deltatime</param>
void NPC_Visitor::animateSprite(sf::Time t_deltaTime)
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
	case VisitorPreSpawn:
		break;
	case VisitorFresh:
		animateMove();
		break;
	case VisitorCower:
		animateCower();
		break;
	case VisitorFollow:
		animateMove();
		break;
	case VisitorFlee:
		animateMove();
		break;
	case VisitorRescue:
		animateRescue();
		break;
	default:
		break;
	}
	m_rectShape.setTextureRect(m_intRect);
}

/// <summary>
/// Play correct sprite animation based on orientation and movement
/// </summary>
void NPC_Visitor::animateMove()
{
	if (std::abs(m_desiredDirection.x) > 0.01f || std::abs(m_desiredDirection.y) > 0.01f)
	{
		if (std::abs(m_desiredDirection.x) > std::abs(m_desiredDirection.y))
		{// We're facing horizontal
			if (m_desiredDirection.x > 0.0f)
			{// We're facing right
				m_intRect = { 48 + (m_currentFrame * M_FRAME_WIDTH), 48, 8, 16 };
			}
			else
			{// We're facing left
				m_intRect = { 48 + (m_currentFrame * M_FRAME_WIDTH), 32, 8, 16 };
			}
		}
		else
		{// We're facing vertical
			if (m_desiredDirection.y > 0.0f)
			{// We're facing down
				m_intRect = { 48 + (m_currentFrame * M_FRAME_WIDTH), 0, 8, 16 };
			}
			else
			{// We're facing up
				m_intRect = { 48 + (m_currentFrame * M_FRAME_WIDTH), 16, 8, 16 };
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
				m_intRect = { 40, 32, 8, 16 };
			}
			else
			{// We're facing left
				m_intRect = { 40, 48, 8, 16 };
			}
		}
		else
		{// We're facing vertical
			if (m_desiredDirPrev.y > 0.0f)
			{// We're facing down
				m_intRect = { 40, 0, 8, 16 };
			}
			else
			{// We're facing up
				m_intRect = { 40, 16, 8, 16 };
			}
		}
	}
}

/// <summary>
/// Animate clown cowering!
/// </summary>
void NPC_Visitor::animateCower()
{
	m_intRect = { 80 + (m_currentFrame * M_FRAME_WIDTH), 32, 8, 16 };
}

/// <summary>
/// Animate clown celebration!
/// </summary>
void NPC_Visitor::animateRescue()
{
	m_intRect = { 80 + (m_currentFrame * M_FRAME_WIDTH), 16, 8, 16 };
}

/// <summary>
/// Reset clown to default values
/// </summary>
void NPC_Visitor::reset()
{
	m_speedCur = M_SPEED_FOLLOW;
	spawn();
}
