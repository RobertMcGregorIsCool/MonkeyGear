
#include "PropJeep.h"

PropJeep::PropJeep(Assets& t_assets) : m_assets {t_assets}
{
	m_rectShapeJeep.setTexture(&m_assets.m_spriteSheet);
	m_rectShapeJeep.setSize(sf::Vector2f(32 * SCREEN_SCALAR, 32 * SCREEN_SCALAR));
	m_rectShapeJeep.setTextureRect(m_intRectJeep);
	m_rectShapeJeep.setOrigin(m_rectShapeJeep.getSize() * 0.5f);
	m_rectShapeJeep.setPosition(SCREEN_WIDTH * 0.5f, (13.0f * SCREEN_SCALAR) + m_rectShapeJeep.getSize().y * 0.5f);
	m_rectShapeJeep.setFillColor(sf::Color(255, 255, 255, 255));
}

PropJeep::~PropJeep(){}

void PropJeep::onUpdate(sf::Time t_deltaTime)
{
	m_spriteFrameCounter += M_SPRITE_FRAME_INCREMENT;

	m_currentFrame = static_cast<int>(m_spriteFrameCounter);

	if (m_currentFrame >= M_FRAME_TOTAL)
	{
		m_currentFrame = 0;
		m_spriteFrameCounter = 0.0f;
	}

	if (m_currentFrame != m_spriteFrame)
	{
		m_spriteFrame = m_currentFrame;
	}

	m_intRectJeep = { 128, (m_currentFrame * M_FRAME_HEIGHT), M_FRAME_WIDTH, M_FRAME_HEIGHT };

	m_rectShapeJeep.setTextureRect(m_intRectJeep);

	
}
