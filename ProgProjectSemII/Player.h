// Player class declaration
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Global header file

class Player
{
	// private data members
	const float M_SPEED_WALK = 128.0f;

	sf::Texture m_spriteSheet;

public:
	Player(sf::Vector2f t_posStart);
	~Player();

	void move(sf::Time t_deltaTime, sf::Vector2f t_desiredDir);

	sf::IntRect m_intRect {18, 15, 42, 60};
	sf::RectangleShape m_rectShape;
};