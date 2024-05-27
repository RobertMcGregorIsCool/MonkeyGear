#include "LevelTitle.h"

LevelTitle::LevelTitle(Assets& t_assets, float t_endY):
	m_assets{ t_assets }
{
	m_endY = t_endY;

	m_rectShape.setTexture(&m_assets.m_spriteSheet);
	m_rectShape.setTextureRect(sf::IntRect(192, 0, 64, 32));
	m_rectShape.setSize(sf::Vector2f(256.0f, 128.0f));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
	m_rectShape.setPosition(SCREEN_SIZE * 0.5f);
}

LevelTitle::~LevelTitle(){}

void LevelTitle::onUpdate(sf::Time t_deltaTime)
{
	if (m_introTimer > 0)
	{
		m_introTimer -= t_deltaTime.asSeconds();
	}
	else
	{
		float y = Hlp::floatLerp(m_rectShape.getPosition().y, m_endY, m_speed * t_deltaTime.asSeconds());
		m_rectShape.setPosition(sf::Vector2f(m_rectShape.getPosition().x, y));
	}
}
