#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Hlp.h"
#include "Globals.h"

class LevelTitle
{
	float m_endY = 0.0f;
	float m_speed = 2.0f;
	
	Assets &m_assets;

public:
	LevelTitle(Assets &t_assets, float t_endY);
	~LevelTitle();
	void onUpdate(sf::Time t_deltaTime);

	sf::RectangleShape m_rectShape;
	float m_introTimer = 1.0f;
};

