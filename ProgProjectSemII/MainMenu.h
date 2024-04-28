/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#pragma once
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Assets.h"

const int M_MENU_OPTIONS = 3;

class Game; // FORWARD DEPENDENCY

class MainMenu
{
	sf::IntRect m_intRect;
	sf::Text m_textButtons[M_MENU_OPTIONS];
	sf::Vector2f m_buttonLocations[M_MENU_OPTIONS];

	Assets& m_assets;	// Reference to asset loader / container
	Game& m_game;

	sf::RectangleShape m_rectShapeButton;

public:
	MainMenu(Assets& t_assets, Game& t_game);
	~MainMenu();

	// void onUpdate(sf::Time t_deltaTime);
	void onRender(sf::RenderWindow& t_window);

	const float M_BUTTON_WDH = 64.0f;
	const float M_BUTTON_HGT = 16.0f;
	const float M_BUTTON_X_START = (SCREEN_WIDTH - M_BUTTON_WDH) * 0.5f;
	const float M_BUTTON_Y_START = 32.0f * SCREEN_SCALAR;
	const float M_BUTTON_GAP = 32.0f * SCREEN_SCALAR;	
};

