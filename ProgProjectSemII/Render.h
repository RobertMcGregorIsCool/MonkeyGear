/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#pragma once

#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Level.h"
#include "MainMenu.h"
#include "LevelTitle.h"

class Game; // FORWARD DEPENDENCY

class Render
{
	Game& m_game;

	const float M_FLASH_PERIOD = 0.5f;
	float m_flashTimer = 0.0f;

	// Used for flashing and flickering effects
	bool m_flashShow = true;
	bool m_renderFlicker = true;

	sf::RectangleShape m_dimmer; // Used to dim title screen when main menu is displayed.

	sf::Text m_hudLives;	// Number of player lives remaining
	sf::Text m_hudVisitors; // Number of visitors to rescue
	sf::Text m_hudFruit;	// Amount of fruit player has
	sf::Text m_hudTimer;	// Time remaining before losing a life

	sf::Text m_hudGameOver;
	sf::Text m_hudScore;	// Currently number of clowns saved overall.

	sf::Text m_pressStartToPlay;

	Level& m_level;	// Reference to Level container
	Assets& m_assets;

	LevelTitle m_levelTitle{ m_assets, -256.0f };

public:

	MainMenu m_mainMenu{ m_assets, m_game }; // Reference to mainMenu object
	sf::RenderWindow m_window;

	bool m_exitGame = false;

	Render(Level& t_level, Game& t_game, Assets& t_assets);
	~Render();

	void onDraw();

	void drawTitleScreen();
	void drawMainMenu();
	void drawHowToPlay();
	void drawGameplay();
	void drawGameOver();

	void onUpdate(sf::Time t_deltaTime);

	void setHudLives(int lives);
	void setHudBananas(int bananas);
	void setHudVisitors(int visitors);
	void setHudTime(std::string time); //  float time);
};

