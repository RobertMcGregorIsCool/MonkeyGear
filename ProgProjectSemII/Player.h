// Player class declaration
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Global header file
#include "Assets.h"		// include Assets header file
#include "Banana.h"		// include 

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

	sf::Vector2f m_desiredDir;

	void moveDir(sf::Time t_deltaTime);

	Assets& m_assets;
	Render& m_render;

	const float M_INVUL_PERIOD = 0.8f;
	float m_invulTimer = M_INVUL_PERIOD;

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

	// Banana bananaBullet{ m_assets };
	std::vector<Banana> m_bananaBullets;

	sf::RectangleShape m_rectShapeVis;
	sf::RectangleShape m_rectShapeCol;
};