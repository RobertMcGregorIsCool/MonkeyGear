/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Global header file
#include "Hlp.h"
#include "Assets.h"

enum MonkeyState
{
	MonkeySeekBanana,
	MonkeyEating,
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

	sf::IntRect m_intRect{ 112, 0, 16, 16 };

	float m_detectRadiusCur = SCREEN_HEIGHT * 0.20f;

	float m_patrolRadius = 0.0f;
	const float M_PATROL_PERIOD_MIN = 3.0f;
	const float M_PATROL_PERIOD_MAX = 9.0f;
	float m_patrolTimer	=0.0f;

	sf::Vector2f m_patrolDestination = VEC2F_ZERO; // Place monkey patrols to.
	sf::Vector2f m_desiredDirection = VEC2F_ZERO;
	sf::Vector2f m_desiredDirPrev = VEC2F_ZERO;

	sf::Vector2f m_bananaPos = VEC2F_ZERO;
	const float M_EATING_PERIOD = 4.0f;
	float m_eating_timer = M_EATING_PERIOD;

	const float M_CATCH_PERIOD = 1.0f;
	float m_catch_timer = M_CATCH_PERIOD;

	const float M_SEEK_BANANA_PERIOD = 3.0f;
	float m_seek_banana_timer = M_SEEK_BANANA_PERIOD;

	int currentFrame = 0;
	const int M_FRAME_WIDTH = 16;
	const int M_FRAME_HEIGHT = 16;
	int m_spriteFrame{ -1 };
	const int M_SPRITE_TOTAL_ANIM_FRAMES = 4;
	float m_spriteFrameCounter = 0.0f;
	float m_spriteFrameIncrement = 0.1f;

public:
	bool m_isActive = true;

	MonkeyState m_myState{ MonkeyState::MonkeyPatrol};

	NPC_Monkey(sf::Vector2f t_posStart, float t_patrolRadius, Assets& t_assets, Player& t_player);
	~NPC_Monkey();

	void onUpdate(sf::Time t_deltaTime);

	void NPC_Monkey::detect(sf::Vector2f t_playerPos);

	void patrol(sf::Time t_deltaTime);

	void chase(sf::Time t_deltaTime, sf::Vector2f t_playerPos);

	void touchPlayer ();

	void seekBanana(sf::Vector2f t_bananaPos);

	void startEating(sf::Vector2f t_bananaPos);

	void moveTo(sf::Time t_deltaTime, sf::Vector2f t_destination);

	void animateSprite(sf::Time t_deltaTime);
	void animateMove();
	void animateEat();
	void animateCatch();

	void reset();

	sf::RectangleShape m_rectShape;

	sf::CircleShape m_circShape{ 4.0f };

	Player& m_player;
};

