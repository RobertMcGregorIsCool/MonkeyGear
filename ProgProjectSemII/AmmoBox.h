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

class AmmoBox
{
	const float M_SPAWN_PERIOD_MAX = 07.5f;
	const float M_SPAWN_PERIOD_MIN = 05.0f;
	float m_spawn_timer = 0.0f;

	const float M_GETTABLE_PERIOD_MAX = 7.0f;
	const float M_GETTABLE_PERIOD_MIN = 2.0f;
	float m_gettable_timer = 0.0f;

	const float M_EXPIRATION_PERIOD = 3.0f;
	float m_expiration_timer = 0.0f;

public:
	AmmoBox(Assets& t_assets);
	~AmmoBox();

	void onUpdate(sf::Time t_deltaTime);
	void goPreSpawn();
	void goGettable();
	void goExpiration();

	Assets& m_assets;

	AmmoBoxState m_myState = AmmoBoxState::preSpawn;

	sf::RectangleShape m_rectShape;
	sf::Texture m_texAmmoBox;
};

