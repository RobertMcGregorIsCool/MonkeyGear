#pragma once

#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Level.h"
class Render
{
public:
	bool m_exitGame = false;

	sf::RenderWindow m_window;

	bool renderPlayer = true;

	sf::Font m_font01;		// font for writing text
	sf::Font m_font02;		
	sf::Text m_hudLives;	// Number of player lives remaining
	sf::Text m_hudVisitors; // Number of visitors to rescue
	sf::Text m_hudFruit;	// Amount of fruit player has
	sf::Text m_time;		// Time remaining before losing a life

	Level& m_level;	// Reference to Level container

	Render(Level& t_level);
	~Render();

	void onDraw();

	void onUpdate();

	void setHudLives(int lives);
	void setHudVisitors(int visitors);
	void setHudFruit(int fruit);
	void setHudTime(float time);
};

