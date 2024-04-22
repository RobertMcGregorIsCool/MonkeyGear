#include "Banana.h"

Banana::Banana(Assets& t_assets) : m_assets(t_assets)
{
	m_rectShape.setSize(sf::Vector2f(8.0f * SCREEN_SCALAR, 8.0f * SCREEN_SCALAR));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
	
	m_circShapeAttractZone.setRadius(M_BANANA_ATTRACT_RADIUS);
	m_circShapeAttractZone.setOrigin(m_circShapeAttractZone.getRadius(), m_circShapeAttractZone.getRadius());
	m_circShapeAttractZone.setPosition(m_rectShape.getPosition());
	m_circShapeAttractZone.setFillColor(sf::Color::Transparent);
	m_circShapeAttractZone.setOutlineColor(sf::Color::Blue);
	m_circShapeAttractZone.setOutlineThickness(2.0f);
}

Banana::~Banana(){}

void Banana::Update(sf::Time t_deltaTime)
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
			MoveDir(t_deltaTime);
		}
		else
		{
			m_thrownTimer = M_THROWN_PERIOD;
			m_rectShape.setFillColor(sf::Color::Blue);
			m_myState = BananaAtRest;
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

void Banana::ThrowAtDir(sf::Vector2f t_posStart, sf::Vector2f t_throwDirection)
{
	m_thrownTimer = M_THROWN_PERIOD;
	m_rectShape.setPosition(t_posStart);
	m_throwDirection = t_throwDirection;
	m_rectShape.setFillColor(sf::Color::Yellow);
	m_myState = BananaThrown;
}

void Banana::MoveDir(sf::Time t_deltaTime)
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
