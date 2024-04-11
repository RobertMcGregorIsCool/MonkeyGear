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

class Game
{
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.
	
	Assets m_assets;
	Level m_level01{ m_assets };
	
	Render m_render{ m_level01 };
	Input m_input{ m_level01, m_render };
	

public:
	
	

public:	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent();
	void	run();
	void	update(sf::Time t_deltaTime);
	void	processEvents();
};
