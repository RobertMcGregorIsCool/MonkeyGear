#pragma once
#include "Level.h"
#include "Render.h"
class Input
{
	sf::Vector2f m_desiredDir; // Player's desired direction set by input events
	sf::Vector2f m_desiredDirPrev = sf::Vector2f(0.0f, -1.0f); // Previous desired direction

public:

	Level& m_level01;
	Render& m_render;

	Input(Level& t_level01, Render& m_render);
	~Input();

	void onUpdate();

	void onProcessEvents();
	void onKeyPressed(sf::Event event);
	void onKeyReleased(sf::Event event);
};

