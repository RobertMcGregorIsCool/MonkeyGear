/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

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

/// <summary>
/// Ammo player throws at monkeys (and clowns!)
/// </summary>
class Banana
{
	const float M_ROTATION_SPEED = 50.0f;
	const float M_THROWN_SPEED = 512.0f;

	const float M_THROWN_PERIOD = 0.25f;
	float m_thrownTimer = M_THROWN_PERIOD;

	const float M_AT_REST_PERIOD = 1.5f;
	float m_atRestTimer = M_AT_REST_PERIOD;

	Assets& m_assets;
	
	sf::IntRect m_intRect{ 80, 72, 8, 8 };

	int m_currentFrame = 0;
	const int M_FRAME_WIDTH = 8;
	const int M_FRAME_HEIGHT = 8;
	int m_spriteFrame{ -1 };
	const int M_SPRITE_TOTAL_ANIM_FRAMES = 4;
	float m_spriteFrameCounter = 0.0f;
	float m_spriteFrameIncrement = 0.1f;

public:
	Banana(Assets& t_assets);
	~Banana();

	void update(sf::Time t_deltaTime);

	void throwAtDir(sf::Vector2f t_posStart, sf::Vector2f t_throwDirection);

	void moveDir(sf::Time t_deltaTime);

	void animate(sf::Time t_deltaTime);

	void reset();

	sf::RectangleShape m_rectShape;

	BananaState m_myState = BananaInactive;
	sf::Vector2f m_throwDirection = sf::Vector2f(0.0f, 1.0f);

	const float M_BANANA_ATTRACT_RADIUS = 80.0f;
	sf::CircleShape m_circShapeAttractZone;	// Visualiser for area that banana will attract monkeys.
};

