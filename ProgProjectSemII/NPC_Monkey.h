#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Global header file
#include "Hlp.h"

class NPC_Monkey
{
	// private data members
	const float M_SPEED_WALK = 16.0f; // Walking speed for Monkey
	const float M_SPEED_RUN = 256.0f; // Running speed for Monkey
	sf::Vector2f m_posStart = VEC2F_ZERO;
	sf::Texture m_spriteSheet;
	sf::IntRect m_intRect{ 18, 15, 42, 60 };

	float m_patrolRadius = 0.0f;	
	float m_patrolPeriod = 0.25f;	// Time to patrol before changing destination
	float m_patrolTimer	=0.0f;

	sf::Vector2f m_patrolDestination = VEC2F_ZERO; // Place monkey patrols to.
	sf::Vector2f m_desiredDirection = VEC2F_ZERO; // 

public:
	NPC_Monkey(sf::Vector2f t_posStart, float t_patrolRadius);
	~NPC_Monkey();

	void onUpdate(sf::Time t_deltaTime, sf::Vector2f t_playerPos);

	void move(sf::Time t_deltaTime, sf::Vector2f t_playerPos);

	sf::RectangleShape m_rectShape;

	sf::CircleShape m_circShape{ 4.0f };
};

