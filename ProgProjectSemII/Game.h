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
	TitleScreen,
	MainMenu,
	HowToPlay,
	Gameplay,
	GameOver,
};

class Game
{
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.
	
	Assets m_assets;
	Level m_level01{m_assets,	m_render,	*this};
	Render m_render{m_level01,	*this };
	Input m_input{	m_level01,	m_render,	*this };

	const float M_DEF_TIME = 5.0f;

	const float M_TITLE_SCREEN_PERIOD = 5.0f;
	float m_titleScreenTimer = 0.0f;

	GameState m_myState = GameState::TitleScreen;


public:	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent();
	void	run();
	void	update(sf::Time t_deltaTime);
	void	processEvents();

	GameState getGameState() { return m_myState; }
	void	setGameState(GameState t_newState);

	void	reset();
	
	float m_curTime = M_DEF_TIME;

	sf::RectangleShape m_rectShapeTitleScreen;
	sf::RectangleShape m_rectShapeTitleScreenTextStars;
	sf::RectangleShape m_rectShapeHowToPlay;

	sf::RectangleShape m_rectShapeButton;
	sf::IntRect m_intRect;
};
