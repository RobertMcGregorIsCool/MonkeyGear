#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Global header file
#include "Hlp.h"
#include "Assets.h"

enum VisitorState
{
	VisitorInactive,
	VisitorCower,
	VisitorFollow,
	VisitorFlee,
	VisitorRescue
};

class Player; // FORWARD DEPENDANCY
class NPC_Monkey; // FORWARD DEPENDANCY

class NPC_Visitor
{
	// private data members
	float m_speedCur = 0.0f;
	sf::Vector2f m_posStart = VEC2F_ZERO;

	sf::IntRect m_intRect { 0, 64, 8, 16 };

	float m_detectRadiusCur = SCREEN_HEIGHT * 0.25f;

	sf::Vector2f m_fleeDestination = VEC2F_ZERO;

	sf::Vector2f m_desiredDirection = VEC2F_ZERO; // 
	float m_movementThreshold = 30.0f;

	sf::Vector2f m_monkeyPos;

	const float M_FLEE_PERIOD = 0.50f;
	float m_fleeTimer = 0.0f;

	const float M_RESCUED_PERIOD = 0.5f;
	float m_rescueTimer = 0.0f;

	void amRescued(sf::Time t_deltaTime);

public:
	VisitorState myState{ VisitorState::VisitorCower };

	NPC_Visitor(sf::Vector2f t_posStart, Assets& t_assets, Player& t_player);
	~NPC_Visitor();

	void onUpdate(sf::Time t_deltaTime);

	void detect(sf::Vector2f t_playerPos);

	void follow(sf::Time t_deltaTime, sf::Vector2f t_playerPos);

	void startFlee(sf::Vector2f t_monkeyPos);

	void flee(sf::Time t_deltaTime);

	void rescue();

	void move(sf::Time t_deltaTime, sf::Vector2f t_destination);

	void animateSprite(sf::Time t_deltaTime);

	sf::RectangleShape m_rectShape;

	sf::CircleShape m_circShape{ 4.0f };

	Player& m_player;
};