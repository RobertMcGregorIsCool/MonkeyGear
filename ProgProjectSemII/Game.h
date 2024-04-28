/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

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

enum GameState
{
	GSTitleScreen,
	GSMainMenu,
	GSHowToPlay,
	GSGameplay,
	GSGameOver,
};

class Game
{
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.
	
	Assets m_assets;	// Assets loader / container
	Level m_level01{m_assets,	m_render,	*this}; // Level objects container, collision, timer
	Render m_render{m_level01,	*this, m_assets }; // Code for rendering the game, depending on gamestate
	Input m_input{	m_level01,	m_render,	*this };// Player input to game depending on gamestate

	const float M_TITLE_SCREEN_PERIOD = 5.0f;
	float m_titleScreenTimer = 0.0f;

	GameState m_myState = GameState::GSTitleScreen;	


public:	  // declaration of member functions	
	Game(); // default constructor
	void	run();
	void	update(sf::Time t_deltaTime);
	void	processEvents(); // Process game input from SFML

	GameState getGameState() { return m_myState; } // Handles events on state change, performs state change.
	void	setGameState(GameState t_newState);

	void	quitGame();

	sf::RectangleShape m_rectShapeTitleScreen;
	sf::RectangleShape m_rectShapeTitleScreenTextStars;
	sf::RectangleShape m_rectShapeHowToPlay;

	
};
