#include "AmmoBox.h"

AmmoBox::AmmoBox(Assets& t_assets) : m_assets(t_assets)
{
}

AmmoBox::~AmmoBox(){}

void AmmoBox::onUpdate(sf::Time t_deltaTime)
{
	switch (m_myState)
	{
	case preSpawn:
		if (m_spawn_timer > 0)
		{
			m_spawn_timer -= t_deltaTime.asSeconds();
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
		}
		else
		{
			goPreSpawn();
		}
	default:
		break;
	}
}

void AmmoBox::goPreSpawn()
{
	m_spawn_timer = Hlp::randomFloatRange(M_SPAWN_PERIOD_MIN, M_SPAWN_PERIOD_MAX);
	m_myState = AmmoBoxState::preSpawn;
}

void AmmoBox::goGettable()
{
	// Spawn in random position!
	sf::Vector2f newPos { Hlp::randomFloatRange(0, SCREEN_WIDTH), Hlp::randomFloatRange(0, SCREEN_HEIGHT)};
	m_rectShape.setPosition(newPos);
	m_gettable_timer = Hlp::randomFloatRange(M_GETTABLE_PERIOD_MIN, M_GETTABLE_PERIOD_MIN);
	m_myState = AmmoBoxState::gettable;
}

void AmmoBox::goExpiration()
{
	m_expiration_timer = M_EXPIRATION_PERIOD;
	m_myState = AmmoBoxState::expiring;
}
