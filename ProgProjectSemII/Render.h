#pragma once

#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Level01.h"
class Render
{
	

public:
	bool m_exitGame = false;

	sf::RenderWindow m_window;

	sf::Font m_font;	// font for writing text
	sf::Text m_message; // text to write on the screen

	Level01& m_level01;	// Reference to Level container

	Render(Level01& t_level01);
	~Render();

	void onDraw();
};

