#pragma once

#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Level.h"
class Render
{
	

public:
	bool m_exitGame = false;

	sf::RenderWindow m_window;

	sf::Font m_font;	// font for writing text
	sf::Text m_message; // text to write on the screen

	Level& m_level;	// Reference to Level container

	Render(Level& t_level);
	~Render();

	void onDraw();
};

