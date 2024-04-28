/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

// Player class declaration
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Assets.h" // Content loader / container
#include "Banana.h" // Ammo

class Render;	// FORWARD DEPENDANCY
class Game;		// FORWARD DEPENDANCY

enum PlayerState
{
	PlayerNone,
	PlayerVulnerable,
	PlayerInvulnerable
};

class Player
{
	// private data members
	const float M_SPEED_WALK = 128.0f;
	const float M_COLLIDE_SCALE = 0.6f;

	const int M_DEF_LIVES = 3;
	const int M_DEF_BANANAS = 3;

	int m_curLives = M_DEF_LIVES;
	int m_curBananas = 0; // = M_DEF_BANANAS;

	sf::Texture m_spriteSheet;
	sf::IntRect m_intRect{ 0, 0, 8, 16 };

	sf::Vector2f m_desiredDir = VEC2F_ZERO;
	sf::Vector2f m_desiredDirPrev = VEC2F_ZERO;

	void moveDir(sf::Time t_deltaTime);

	Assets& m_assets;
	Render& m_render;

	const float M_INVUL_PERIOD = 0.8f;
	float m_invulTimer = M_INVUL_PERIOD;

	int m_spriteFrame{ -1 };
	const int M_SPRITE_TOTAL_ANIM_FRAMES = 4;
	float m_spriteFrameCounter = 0.0f;
	float m_spriteFrameIncrement = 0.3f;

public:
	Player(Assets& t_assets, sf::Vector2f t_posStart, Render& t_render);
	~Player();

	void setDesiredDir(sf::Vector2f t_desiredDir);

	void onUpdate(sf::Time t_deltaTime);

	void Player::setLives(int t_addedValue, Render& t_render, Game& t_game);

	int getLives();
	
	void setBananas(int t_addedValue);
	void throwBanana(sf::Vector2f t_throwDirection);

	void reset();

	sf::Vector2f m_posStart;

	PlayerState m_myState = PlayerState::PlayerInvulnerable;

	std::vector<Banana> m_bananaBullets;

	sf::RectangleShape m_rectShapeVis;
	sf::RectangleShape m_rectShapeCol;
};