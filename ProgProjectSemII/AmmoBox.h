/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Hlp.h"
#include "Globals.h"

enum AmmoBoxState
{
	preSpawn,
	gettable,
	expiring
};

/// <summary>
/// Acquriable that refills player ammo
/// </summary>
class AmmoBox
{
	const float M_SPAWN_PERIOD_MAX = 07.5f;
	const float M_SPAWN_PERIOD_MIN = 05.0f;
	float m_spawnTimer = 0.0f;

	const float M_GETTABLE_PERIOD_MAX = 7.0f;
	const float M_GETTABLE_PERIOD_MIN = 2.0f;
	float m_gettable_timer = 0.0f;

	const float M_EXPIRATION_PERIOD = 3.0f;
	float m_expiration_timer = 0.0f;

	sf::IntRect m_intRect{ 80, 72, 8, 8 };

	int m_currentFrame = 0;
	const int M_FRAME_WIDTH = 8;
	const int M_FRAME_HEIGHT = 8;
	int m_spriteFrame{ -1 };
	const int M_SPRITE_TOTAL_ANIM_FRAMES = 4;
	float m_spriteFrameCounter = 0.0f;
	float m_spriteFrameIncrement = 0.05f;

public:
	AmmoBox(Assets& t_assets);
	~AmmoBox();

	void onUpdate(sf::Time t_deltaTime);
	void goPreSpawn();
	void goGettable();
	void goExpiration();

	void animate();

	Assets& m_assets;

	AmmoBoxState m_myState = AmmoBoxState::preSpawn;

	sf::RectangleShape m_rectShape;
	sf::Texture m_texAmmoBox;
};

