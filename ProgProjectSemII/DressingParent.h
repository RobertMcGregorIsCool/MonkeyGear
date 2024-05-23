#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Globals.h"

class DressingParent
{
	sf::IntRect m_intRect {0, 0, 0, 0};

	int m_currentFrame = 0;
	int m_spriteFrame = -1;
	float m_spriteFrameCounter = 0.0f;

	const float M_SPRITE_FRAME_INCREMENT;
	const int M_FRAME_TOTAL;
	const int M_FRAME_WIDTH;
	const int M_FRAME_HEIGHT;
	const int M_FRAME_XPOS;
	const int M_FRAME_YPOS;

public:

	DressingParent(Assets& t_assets, float t_spriteFrameIncrement, int t_frameTotal, int t_frameWidth, int t_frameHeight, int t_frameXPos, int t_frameYPos, bool t_animate = false, bool t_animateAlongX = false);

	~DressingParent();

	void onAnimate();

	Assets& m_assets;
	sf::RectangleShape m_rectShape;
};
