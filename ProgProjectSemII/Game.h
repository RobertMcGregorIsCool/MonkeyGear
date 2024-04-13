// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

#include "Player.h" // include Player header file
#include "Render.h"	// Include class that does our rendering tasks
#include "Input.h"	// Include header for input
#include "Level.h"// Include header for level container
#include "Assets.h" // Include header for ASSETS jesus christ
#include "Collision.h" // Include collision header.

class Game
{
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.
	
	Assets m_assets;
	Level m_level01{ m_assets };
	Collision m_collision{ m_level01 };
	Render m_render{ m_level01 };
	Input m_input{ m_level01, m_render };

	const int M_DEF_LIVES = 3;
	const int M_DEF_VISITORS = 4;
	const int M_DEF_FRUIT = 3;
	const float M_DEF_TIME = 5.0f;

public:	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent();
	void	run();
	void	update(sf::Time t_deltaTime);
	void	processEvents();
	void	reset();

	int m_curLives = 3;
	int m_curVisitors = 4;
	int m_curFruit;
	float m_curTime;
};
