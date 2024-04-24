#include "Level.h"

// INCLUDES FOR FORWARD DEPENDANCY
#include "Render.h"

void Level::actorUpdate(sf::Time t_deltaTime)
{
	m_player01.onUpdate(t_deltaTime);

	for (int i = 0; i < static_cast<int>(m_monkeys.size()); i++)
	{
		m_monkeys[i].onUpdate(t_deltaTime);
	}

	for (int i = 0; i < static_cast<int>(m_visitors.size()); i++)
	{
		m_visitors[i].onUpdate(t_deltaTime);
	}

	m_ammoBox.onUpdate(t_deltaTime);
}

void Level::doCollisions(Game& t_game)
{
	colPlayerMonkey(t_game);
	colPlayerVisitor();
	colPlayerAmmoBox();
	colMonkeyBanana();
	colMonkeyVisitor();
	colVisitorSafeZone();
}

void Level::colPlayerMonkey(Game& t_game)
{
	for (int i = 0; i < static_cast<int>(m_monkeys.size()); i++)
	{
		if (m_player01.m_rectShapeCol.getGlobalBounds().intersects(m_monkeys[i].m_rectShape.getGlobalBounds()))
		{
			m_monkeys[i].touchPlayer();
			m_player01.setLives(-1, m_render, t_game);
		}
	}
}

void Level::colPlayerVisitor()
{
	for (int i = 0; i < static_cast<int>(m_visitors.size()); i++)
	{
		if (m_visitors[i].myState != VisitorInactive && m_visitors[i].myState != VisitorRescue)
		{
			if (m_player01.m_rectShapeCol.getGlobalBounds().intersects(m_visitors[i].m_rectShape.getGlobalBounds()))
			{
				m_visitors[i].myState = VisitorFollow;
			}
		}
	}
}

void Level::colPlayerAmmoBox()
{
	if (m_player01.m_rectShapeCol.getGlobalBounds().intersects(m_ammoBox.m_rectShape.getGlobalBounds()))
	{
		std::cout << "Touching ammoBox! \n\n";
		m_ammoBox.goPreSpawn();
		m_player01.setBananas(3);
	}
}

void Level::colMonkeyBanana()
{
	for (int i = 0; i < static_cast<int>(m_monkeys.size()); i++)
	{
		if (m_monkeys[i].m_myState != MonkeyState::MonkeyCatch && m_monkeys[i].m_myState != MonkeyState::MonkeyEating)
		{
			for (int o = 0; o < static_cast<int>(m_player01.m_bananaBullets.size()); o++)
			{
				if (m_player01.m_bananaBullets[o].m_myState != BananaState::BananaInactive)
				{
					sf::Vector2f curDist = m_monkeys[i].m_rectShape.getPosition() - m_player01.m_bananaBullets[o].m_rectShape.getPosition();
					if (Hlp::v2fGetMagnitude(curDist) < m_player01.m_bananaBullets[o].M_BANANA_ATTRACT_RADIUS)
					{
						m_monkeys[i].seesBanana(m_player01.m_bananaBullets[o].m_rectShape.getPosition());
					}
				}
			}
		}
	}
}

void Level::colMonkeyVisitor()
{
	for (int i = 0; i < static_cast<int>(m_monkeys.size()); i++)
	{
		for (int o = 0; o < static_cast<int>(m_visitors.size()); o++)
		{
			if (m_visitors[o].m_rectShape.getGlobalBounds().intersects(m_monkeys[i].m_rectShape.getGlobalBounds()))
			{
				if (m_visitors[o].myState == VisitorFollow)
				{
					m_visitors[o].startFlee(m_monkeys[i].m_rectShape.getPosition());
				}
			}
		}
	}
}

void Level::colVisitorSafeZone()
{
	for (int i = 0; i < static_cast<int>(m_visitors.size()); i++)
	{
		sf::Vector2f distance = m_circShapeSafeZone.getPosition() - m_visitors[i].m_rectShape.getPosition();
		if (Hlp::v2fGetMagnitude(distance) < m_circShapeSafeZone.getRadius())
		{
			if (m_visitors[i].myState != VisitorRescue && m_visitors[i].myState != VisitorInactive)
			{
				m_visitors[i].rescue();
				m_curVisitors++;
				m_render.setHudVisitors(m_curVisitors);
			}
		}
	}
}

Level::Level(Assets& t_assets, Render& t_render) : m_assets{t_assets}, m_render{t_render}
{
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.25f), 500.0f, m_assets, m_player01 });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.25f), 500.0f, m_assets, m_player01 });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.85f), 500.0f, m_assets, m_player01 });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.85f), 500.0f, m_assets, m_player01 });

	m_visitors.push_back(NPC_Visitor{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.25f), m_assets, m_player01 });
	m_visitors.push_back(NPC_Visitor{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.25f), m_assets, m_player01 });
	m_visitors.push_back(NPC_Visitor{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.85f), m_assets, m_player01 });
	m_visitors.push_back(NPC_Visitor{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.85f), m_assets, m_player01 });

	m_rectShapeBGImage.setTexture(&m_assets.m_background01);
	m_rectShapeBGImage.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	m_rectShape8x8Grid.setTexture(&m_assets.m_8x8GreyGrid);
	m_rectShape8x8Grid.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_rectShape8x8Grid.setFillColor(sf::Color(255, 255, 255, 63));

	m_circShapeSafeZone.setRadius(80.0f);
	m_circShapeSafeZone.setOrigin(m_circShapeSafeZone.getRadius(), m_circShapeSafeZone.getRadius());
	m_circShapeSafeZone.setPosition(80.0f * SCREEN_SCALAR, 32.0f * SCREEN_SCALAR);
	m_circShapeSafeZone.setOutlineColor(sf::Color::Green);
	m_circShapeSafeZone.setOutlineThickness(1.0f);
	m_circShapeSafeZone.setFillColor(sf::Color::Transparent);
}

Level::~Level(){}

void Level::onUpdate(sf::Time t_deltaTime, Game& t_game)
{
	actorUpdate(t_deltaTime);

	doCollisions(t_game);
}

void Level::onReset()
{
	m_curVisitors = M_DEF_VISITORS;
}
