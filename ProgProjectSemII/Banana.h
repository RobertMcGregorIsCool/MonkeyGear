#pragma once

#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Hlp.h"
#include "Assets.h"

enum BananaState
{
	BananaInactive,
	BananaThrown,
	BananaAtRest
};

class Banana
{
	const float M_ROTATION_SPEED = 50.0f;
	const float M_THROWN_SPEED = 512.0f;

	const float M_THROWN_PERIOD = 0.25f;
	float m_thrownTimer = M_THROWN_PERIOD;

	const float M_AT_REST_PERIOD = 1.5f;
	float m_atRestTimer = M_AT_REST_PERIOD;

	Assets& m_assets;
	

public:
	Banana(Assets& t_assets);
	~Banana();

	void Update(sf::Time t_deltaTime);

	void ThrowAtDir(sf::Vector2f t_posStart, sf::Vector2f t_throwDirection);

	void MoveDir(sf::Time t_deltaTime);

	sf::RectangleShape m_rectShape;

	BananaState m_myState = BananaInactive;
	sf::Vector2f m_throwDirection = sf::Vector2f(0.0f, 1.0f);

	const float M_BANANA_ATTRACT_RADIUS = 80.0f;
	sf::CircleShape m_circShapeAttractZone;
};

