#include "DressingParent.h"

//DressingParent::DressingParent(Assets& t_assets, float t_spriteFrameIncrement, int t_frameTotal, int t_frameWidth, int t_frameHeight, int t_frameXPos, int t_frameYPos) :
//	m_assets{ t_assets }, M_SPRITE_FRAME_INCREMENT{ t_spriteFrameIncrement }, M_FRAME_TOTAL{ t_frameTotal }, M_FRAME_WIDTH{ t_frameWidth }, M_FRAME_HEIGHT{ t_frameHeight },
//	M_FRAME_XPOS{ t_frameXPos }, M_FRAME_YPOS{ t_frameYPos }, bool t_animate = false, bool t_animateAlongX = false
//{
//}

DressingParent::~DressingParent(){}

void DressingParent::onAnimate()
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

	m_intRect = { M_FRAME_WIDTH, (m_currentFrame * M_FRAME_HEIGHT), M_FRAME_WIDTH, M_FRAME_HEIGHT };

	m_rectShape.setTextureRect(m_intRect);
}
