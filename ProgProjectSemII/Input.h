#pragma once
#include "Level.h"
#include "Render.h"
#include "Hlp.h"

class Game; // FORWARD DEPENDENCY

class Input
{
	sf::Vector2f m_desiredDir; // Player's desired direction set by input events
	sf::Vector2f m_desiredDirPrev = sf::Vector2f(0.0f, -1.0f); // Previous desired direction

	bool m_pressedSpace = false;
	bool m_releasedSpaceIgnoreFirst = true;

public:

	Level& m_level01;
	Render& m_render;
	Game& m_game;

	Input(Level& t_level01, Render& t_render, Game& t_game);
	~Input();

	void onUpdate();

	void onProcessEvents();
	void onKeyPressed(sf::Event event);
	void onKeyReleased(sf::Event event);
};

