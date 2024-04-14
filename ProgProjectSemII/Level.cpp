#include "Level.h"

void Level::playerUpdate(sf::Time t_deltaTime)
{
	m_player01.onUpdate(t_deltaTime);

	for (int i = 0; i < m_monkeys.size(); i++)
	{
		if (m_monkeys[i].isActive)
		{
			m_monkeys[i].onUpdate(t_deltaTime, m_player01.m_rectShapeVis.getPosition());
		}
	}
}

void Level::doCollisions()
{
	playerMonkey();
	playerVisitor();
	monkeyBanana();
	visitorSafeZone();
}

void Level::playerMonkey()
{
	for (int i = 0; i < m_monkeys.size(); i++)
	{
		if (m_player01.m_rectShapeCol.getGlobalBounds().intersects(m_monkeys[i].m_rectShape.getGlobalBounds()))
		{
			std::cout << "Monkey touched me.\n\n";
		}
	}
}

void Level::playerVisitor()
{
}

void Level::monkeyBanana()
{
}

void Level::visitorSafeZone()
{
}

Level::Level(Assets& t_assets): m_assets{t_assets}
{
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.25f), 150.0f, m_assets });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.25f), 150.0f, m_assets });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.85f), 150.0f, m_assets });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.85f), 150.0f, m_assets });

	m_rectShapeBGImage.setTexture(&m_assets.m_background01);
	m_rectShapeBGImage.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	m_rectShape8x8Grid.setTexture(&m_assets.m_8x8GreyGrid);
	m_rectShape8x8Grid.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_rectShape8x8Grid.setFillColor(sf::Color(255, 255, 255, 63));
}

Level::~Level(){}

void Level::onUpdate(sf::Time t_deltaTime)
{
	playerUpdate(t_deltaTime);

	doCollisions();
}

void Level::onReset()
{
	m_curVisitors = M_DEF_VISITORS;
}
