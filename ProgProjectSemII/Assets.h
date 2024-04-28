/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

/// <summary>
/// Loader for game assets
/// </summary>
class Assets
{
public:
	sf::Font m_font01;					// font for writing text
	sf::Font m_font02;					// bold version of first font

	sf::Texture m_spriteSheet;			// Playable elements
	sf::Texture m_8x8GreyGrid;			// Overlay used to place elements
	sf::Texture m_background01;			// Background for play
	sf::Texture m_titleScreen;			// Title screen art
	sf::Texture m_titleScreenTextStars;	// Title screen stars, for flickering
	sf::Texture m_howToPlay;			// 'How to play' screen.

	Assets();
	~Assets();
};

