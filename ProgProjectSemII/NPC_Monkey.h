#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Global header file
#include "Hlp.h"
#include "Assets.h"

enum MonkeyState
{
	MonkeyNone,
	MonkeyPatrol,
	MonkeyChase,
	MonkeyCatch
};

class Player; // FORWARD DEPENDANCY

class NPC_Monkey
{
	// private data members
	float m_speedCur = 0.0f;
	sf::Vector2f m_posStart = VEC2F_ZERO;

	sf::IntRect m_intRect{ 0, 128, 8, 9 };

	float m_detectRadiusCur = SCREEN_HEIGHT * 0.20f;

	float m_patrolRadius = 0.0f;
	const float M_PATROL_PERIOD_MIN = 3.0f;
	const float M_PATROL_PERIOD_MAX = 9.0f;
	// float m_patrolPeriod = 5.0f;	// Time to patrol before changing destination
	float m_patrolTimer	=0.0f;

	sf::Vector2f m_patrolDestination = VEC2F_ZERO; // Place monkey patrols to.
	sf::Vector2f m_desiredDirection = VEC2F_ZERO; // 

public:
	bool isActive = true;

	MonkeyState myState{ MonkeyState::MonkeyPatrol};

	NPC_Monkey(sf::Vector2f t_posStart, float t_patrolRadius, Assets& t_assets, Player& t_player);
	~NPC_Monkey();

	void onUpdate(sf::Time t_deltaTime);

	void NPC_Monkey::detect(sf::Vector2f t_playerPos);

	void patrol(sf::Time t_deltaTime);

	void chase(sf::Time t_deltaTime, sf::Vector2f t_playerPos);

	void touchPlayer ();

	void move(sf::Time t_deltaTime, sf::Vector2f t_destination);

	void animateSprite(sf::Time t_deltaTime);

	sf::RectangleShape m_rectShape;

	sf::CircleShape m_circShape{ 4.0f };

	Player& m_player;
};

