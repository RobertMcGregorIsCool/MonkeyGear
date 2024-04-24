#include "AmmoBox.h"

AmmoBox::AmmoBox(Assets& t_assets) : m_assets(t_assets)
{
	m_rectShape.setSize(sf::Vector2f(8.0f * SCREEN_SCALAR, 8.0f * SCREEN_SCALAR));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);

	goPreSpawn();
}

AmmoBox::~AmmoBox(){}

void AmmoBox::onUpdate(sf::Time t_deltaTime)
{
	switch (m_myState)
	{
	case preSpawn:
		std::cout << "I'm in prespawn.\n\n";
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
		std::cout << "I'm in gettable.\n\n";
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
		std::cout << "I'm in expiring.\n\n";
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
	m_rectShape.setFillColor(sf::Color::Red);
}

void AmmoBox::goGettable()
{
	// Spawn in random position!
	sf::Vector2f newPos { Hlp::randomFloatRange(0, SCREEN_WIDTH), Hlp::randomFloatRange(0, SCREEN_HEIGHT)};
	//sf::Vector2f newPos = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT) * 0.5f;
	m_rectShape.setPosition(newPos);
	m_rectShape.setFillColor(sf::Color::Green);
	m_gettable_timer = Hlp::randomFloatRange(M_GETTABLE_PERIOD_MIN, M_GETTABLE_PERIOD_MIN);
	m_myState = AmmoBoxState::gettable;
}

void AmmoBox::goExpiration()
{
	m_rectShape.setFillColor(sf::Color::Magenta);
	m_expiration_timer = M_EXPIRATION_PERIOD;
	m_myState = AmmoBoxState::expiring;
}
