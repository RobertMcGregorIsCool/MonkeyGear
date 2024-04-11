#pragma once
#include "Level.h"
#include "Render.h"
class Input
{

	sf::Vector2f m_desiredDir; // Player's desired direction set by input events

public:

	Level& m_level01;
	Render& m_render;

	Input(Level& t_level01, Render& m_render);
	~Input();

	void onUpdate();

	//void onProcessEvents(sf::Event event);
	void onProcessEvents();
	void onKeyPressed(sf::Event event);
	void onKeyReleased(sf::Event event);
};

