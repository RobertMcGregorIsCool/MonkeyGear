#include "Dressing.h"

Dressing::Dressing(Assets& t_assets, float t_spriteFrameIncrement, int t_frameXTot, int t_frameYTot, int t_frameWidth, int t_frameHeight, int t_frameXPos, int t_frameYPos, bool t_animate, bool t_animateAlongX) : 
	m_assets{ t_assets }, M_SPRITE_FRAME_INCREMENT{ t_spriteFrameIncrement }, M_FRAME_XTOT{ t_frameXTot }, M_FRAME_YTOT{ t_frameYTot }, M_FRAME_WIDTH {	t_frameWidth }, M_FRAME_HEIGHT{ t_frameHeight }, M_FRAME_XPOS{ t_frameXPos }, M_FRAME_YPOS{ t_frameYPos }, m_animate{ t_animate }, m_animateAlongX{ t_animateAlongX }
{
	m_rectShape.setTexture(&m_assets.m_spriteSheet);
	m_rectShape.setSize(sf::Vector2f(M_FRAME_WIDTH * SCREEN_SCALAR, M_FRAME_HEIGHT * SCREEN_SCALAR));
	m_rectShape.setOrigin(m_rectShape.getSize() * 0.5f);
}

Dressing::~Dressing(){}

void Dressing::onAnimate()
{
	m_spriteFrameCounter += M_SPRITE_FRAME_INCREMENT;

	m_currentXFrame = static_cast<int>(m_spriteFrameCounter);

	if (m_currentXFrame >= M_FRAME_XTOT)
	{
		m_currentXFrame = 0;
		m_spriteFrameCounter = 0.0f;
		m_currentYFrame++;
		if (m_currentYFrame >= M_FRAME_YTOT)
		{
			m_currentYFrame = 0;
		}
	}
	
	m_intRect = {	M_FRAME_XPOS + (m_currentXFrame * M_FRAME_WIDTH), 
					M_FRAME_YPOS + (m_currentYFrame * M_FRAME_HEIGHT), 
					M_FRAME_WIDTH, M_FRAME_HEIGHT};
	
	m_rectShape.setTextureRect(m_intRect);
}
