// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

#include "Globals.h"   // include Global header file
#include "Player.h"   // include Player header file


class Game
{
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.
	bool m_exitGame = false;

	sf::RenderWindow m_window;

	Player player;

public:
	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen
	sf::Vector2f m_desiredDir; // Vector 2 for players desired direction set by input events

public:	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent();
	void	run();
	void	update(sf::Time t_deltaTime);
	void	processEvents(sf::Event event);
	void	draw();
};
