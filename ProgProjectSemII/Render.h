#pragma once

#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Level.h"

class Game; // FORWARD DEPENDENCY

class Render
{
	Game& m_game;

	const float M_FLASH_PERIOD = 0.5f;
	float m_flashTimer = 0.0f;

	bool m_flashShow = true;

public:
	bool m_exitGame = false;

	sf::RenderWindow m_window;

	bool m_renderFlicker = true;

	sf::Font m_font01;		// font for writing text
	sf::Font m_font02;		
	sf::Text m_hudLives;	// Number of player lives remaining
	sf::Text m_hudVisitors; // Number of visitors to rescue
	sf::Text m_hudFruit;	// Amount of fruit player has
	sf::Text m_hudTimer;	// Time remaining before losing a life

	sf::RectangleShape m_dimmer;
	sf::Text m_hudGameOver;
	sf::Text m_hudScore;

	sf::Text m_pressStartToPlay;

	Level& m_level;	// Reference to Level container

	Render(Level& t_level, Game& t_game);
	~Render();

	void onDraw();

	void drawTitleScreen();
	void drawMainMenu();
	void drawGameplay();
	void drawGameOver();

	void onUpdate(sf::Time t_deltaTime);

	void setHudLives(int lives);
	void setHudBananas(int bananas);
	void setHudVisitors(int visitors);
	void setHudTime(std::string time); //  float time);
};

