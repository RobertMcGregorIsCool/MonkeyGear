// Player class declaration
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Global header file
#include "Assets.h"		// include Assets header file

class Player
{
	// private data members
	const float M_SPEED_WALK = 128.0f;

	sf::Texture m_spriteSheet;
	sf::IntRect m_intRect{ 0, 0, 8, 16 };

	sf::Vector2f m_desiredDir;

	void move(sf::Time t_deltaTime);

	Assets& m_assets;

public:
	Player(Assets& t_assets, sf::Vector2f t_posStart);
	~Player();

	void setDesiredDir(sf::Vector2f t_desiredDir);

	void onUpdate(sf::Time t_deltaTime);

	sf::RectangleShape m_rectShape;
};