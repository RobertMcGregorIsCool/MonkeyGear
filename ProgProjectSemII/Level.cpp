/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#include "Level.h"

// INCLUDES FOR FORWARD DEPENDANCY
#include "Render.h"
#include "Game.h"

/// <summary>
/// Called from Update in Game, powers actors
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
void Level::actorUpdate(sf::Time t_deltaTime)
{
	m_player01.onUpdate(t_deltaTime);

	for (int i = 0; i < static_cast<int>(m_monkeys.size()); i++)
	{
		m_monkeys[i].onUpdate(t_deltaTime);
	}

	m_visitor.onUpdate(t_deltaTime);

	m_ammoBox.onUpdate(t_deltaTime);
}

/// <summary>
/// Does collisions
/// </summary>
/// <param name="t_game">Reference to game for player interaction</param>
void Level::doCollisions(Game& t_game)
{
	colPlayerMonkey(t_game);
	colPlayerVisitor();
	colPlayerAmmoBox();
	colMonkeyBanana();
	colMonkeyVisitor();
	colVisitorSafeZone();
	colVisitorBanana();
}

/// <summary>
/// Collision between Player and Monkey
/// </summary>
/// <param name="t_game">Reference to game for when player loses lives</param>
void Level::colPlayerMonkey(Game& t_game)
{
	for (int i = 0; i < static_cast<int>(m_monkeys.size()); i++)
	{
		if (m_player01.m_rectShapeCol.getGlobalBounds().intersects(m_monkeys[i].m_rectShape.getGlobalBounds()))
		{
			m_monkeys[i].touchPlayer();
			m_player01.setLives(-1, m_render, t_game);

			if (m_player01.getLives() <= 0)
			{
				onGameOver();
			}
		}
	}
}

/// <summary>
/// Collision between Player and Visitor
/// </summary>
void Level::colPlayerVisitor()
{
	if (m_visitor.m_myState != VisitorPreSpawn && m_visitor.m_myState != VisitorRescue)
	{
		if (m_player01.m_rectShapeCol.getGlobalBounds().intersects(m_visitor.m_rectShape.getGlobalBounds()))
		{
			m_visitor.startFollow();
		}
	}
}

/// <summary>
/// Collision between Player and AmmoBox
/// </summary>
void Level::colPlayerAmmoBox()
{
	if (m_player01.m_rectShapeCol.getGlobalBounds().intersects(m_ammoBox.m_rectShape.getGlobalBounds()))
	{
		// std::cout << "Touching ammoBox! \n\n";
		m_ammoBox.goPreSpawn();
		m_player01.setBananas(3);
	}
}

/// <summary>
/// Collision between Monkey and Banana
/// </summary>
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
						m_monkeys[i].seekBanana(m_player01.m_bananaBullets[o].m_rectShape.getPosition());
					}
				}
			}
		}
	}
}

/// <summary>
/// Collision between Monkey and Visitor
/// </summary>
void Level::colMonkeyVisitor()
{
	for (int i = 0; i < static_cast<int>(m_monkeys.size()); i++)
	{
		if (m_visitor.m_rectShape.getGlobalBounds().intersects(m_monkeys[i].m_rectShape.getGlobalBounds()))
		{
			if (m_visitor.m_myState == VisitorFollow)
			{
				m_visitor.startFlee(m_monkeys[i].m_rectShape.getPosition());
			}
		}
	}
}

/// <summary>
/// Collision between Visitor and Safe Zone
/// </summary>
void Level::colVisitorSafeZone()
{
	sf::Vector2f distance = m_circShapeSafeZone.getPosition() - m_visitor.m_rectShape.getPosition();
	if (Hlp::v2fGetMagnitude(distance) < m_circShapeSafeZone.getRadius())
	{
		if (m_visitor.m_myState != VisitorRescue && m_visitor.m_myState != VisitorPreSpawn)
		{
			m_visitor.rescue();
			m_visitorScore++;
			m_render.setHudVisitors(m_visitorScore);
			rallyAddTime(M_RALLY_EXTEND);
		}
	}
}

/// <summary>
/// Collision between Visitor and thrown Banana
/// </summary>
void Level::colVisitorBanana()
{
	for (int o = 0; o < static_cast<int>(m_player01.m_bananaBullets.size()); o++)
	{
		if (m_player01.m_bananaBullets[o].m_rectShape.getGlobalBounds().intersects(m_visitor.m_rectShape.getGlobalBounds()))
		{
			if (m_visitor.m_myState == VisitorFollow && m_player01.m_bananaBullets[o].m_myState == BananaThrown)
			{
				m_visitor.bananaBash();
			}
		}
	}
}

/// <summary>
/// Timer which can have extra time added if player rescues a visitor.
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
void Level::rallyTimer(sf::Time t_deltaTime)
{
	if (m_rallyTimer > 0)
	{
		m_rallyTimer -= t_deltaTime.asSeconds();
		std::string minutes = std::to_string(static_cast<int>(m_rallyTimer / 60.0f));
		std::string seconds = std::to_string(static_cast<int>(m_rallyTimer) % 60);
		m_render.setHudTime(minutes + ":" + seconds);
	}
	else
	{
		onGameOver();
	}
}

/// <summary>
/// When visitor is rescued, this adds extra time for player
/// </summary>
/// <param name="seconds"></param>
void Level::rallyAddTime(float seconds)
{
	m_rallyTimer += seconds;
}

/// <summary>
/// Called when all player lives lost or time has run out
/// </summary>
void Level::onGameOver()
{
	m_game.setGameState(GameState::GSGameOver);
}

/// <summary>
/// Constructor
/// </summary>
/// <param name="t_assets">Reference to asset loader / container</param>
/// <param name="t_render">Reference to rendering code</param>
/// <param name="t_game">Reference to main game loop</param>
Level::Level(Assets& t_assets, Render& t_render, Game& t_game) : m_assets{ t_assets }, m_render{ t_render }, m_game{ t_game }
{
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.25f), 500.0f, m_assets, m_player01 });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.25f), 500.0f, m_assets, m_player01 });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.85f), 500.0f, m_assets, m_player01 });
	m_monkeys.push_back(NPC_Monkey{ sf::Vector2f(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.85f), 500.0f, m_assets, m_player01 });

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

	m_rallyTimer = M_INITIAL_RALLY_PERIOD;

	m_dresJeep.m_rectShape.setPosition(SCREEN_WIDTH * 0.5f, (13.0f * SCREEN_SCALAR) + m_dresJeep.m_rectShape.getSize().y * 0.5f);
	m_dresSmok.m_rectShape.setPosition(SCREEN_WIDTH * 0.5f + (20 * SCREEN_SCALAR), 28 * SCREEN_SCALAR);
}

Level::~Level(){}

/// <summary>
/// Called from Game::Update, powers level functions
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
/// <param name="t_game">Reference to main game loop</param>
void Level::onUpdate(sf::Time t_deltaTime, Game& t_game)
{
	actorUpdate(t_deltaTime);

	doCollisions(t_game);

	rallyTimer(t_deltaTime);

	m_dresJeep.onAnimate();
	m_dresSmok.onAnimate();
}

/// <summary>
/// Resets level to initial state
/// </summary>
void Level::onReset()
{
	m_visitorScore = M_DEF_VISITOR_SCORE;
	m_rallyTimer = M_INITIAL_RALLY_PERIOD;
	m_player01.reset();
	m_visitor.reset();
	for (int i = 0; i < static_cast<int>(m_monkeys.size()); i++)
	{
		m_monkeys[i].reset();
	}
	for (int o = 0; o < static_cast<int>(m_player01.m_bananaBullets.size()); o++)
	{
		m_player01.m_bananaBullets[o].reset();
	}
}
