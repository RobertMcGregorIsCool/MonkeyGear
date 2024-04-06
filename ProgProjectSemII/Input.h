#pragma once
#include "Level01.h"
#include "Render.h"
class Input
{

	sf::Vector2f m_desiredDir; // Player's desired direction set by input events

public:

	Level01& m_level01;
	Render& m_render;

	Input(Level01& t_level01, Render& m_render);
	~Input();

	void onUpdate(sf::Time t_deltaTime);

	void onProcessEvents(sf::Event event);

	void onKeyReleased(sf::Event event);
};

