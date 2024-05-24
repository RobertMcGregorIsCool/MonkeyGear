#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Globals.h"

class PropJeep
{
	sf::IntRect m_intRectJeep {128, 0, 32, 32};

	Assets& m_assets;

	int m_currentFrame = 0;
	int m_spriteFrame = -1;
	float m_spriteFrameCounter = 0.0f;
	const float M_SPRITE_FRAME_INCREMENT = 0.1f;
	const int M_FRAME_TOTAL = 4;
	const int M_FRAME_WIDTH = 32;
	const int M_FRAME_HEIGHT = 32;
	
public:
	PropJeep(Assets& t_assets);
	~PropJeep();

	void onUpdate(sf::Time t_deltaTime);

	sf::RectangleShape m_rectShapeJeep;
};

