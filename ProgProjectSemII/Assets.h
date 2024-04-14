#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Assets
{

public:

	sf::Texture m_spriteSheet;
	sf::Texture m_8x8GreyGrid;
	sf::Texture m_background01;

	Assets();
	~Assets();
};

