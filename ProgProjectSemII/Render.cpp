#include "Render.h"
#include <iostream>

// FORWARD DEPENDENCY
#include "Game.h"

Render::Render(Level& t_level, Game& t_game) : m_window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH),
    static_cast<int>(SCREEN_HEIGHT)),
    "Monkey Gear", sf::Style::Default), m_level(t_level), m_game(t_game)
{
    if (!m_font01.loadFromFile("ASSETS/FONTS/Silkscreen/slkscr.ttf")) {
        std::cout << "Error loading slkscr.ttf";
    }
    if (!m_font02.loadFromFile("ASSETS/FONTS/Silkscreen/slkscreb.ttf")) {
        std::cout << "Error loading slkscreb.ttf";
    }

    // set up the message string
    m_hudLives.setFont(m_font01);                                                   // set the font for the text
    m_hudLives.setCharacterSize(24);                                                // set the text size
    m_hudLives.setFillColor(sf::Color(255,248,220,255));                            // set the text colour
    m_hudLives.setPosition(SCREEN_WIDTH * 0.01f, SCREEN_HEIGHT * 0.0001f);            // its position on the screen

    m_hudVisitors.setFont(m_font01);
    m_hudVisitors.setCharacterSize(24);
    m_hudVisitors.setFillColor(sf::Color(255, 248, 220, 255));
    m_hudVisitors.setPosition(SCREEN_WIDTH * 0.33f, SCREEN_HEIGHT * 0.0001f);

    m_hudFruit.setFont(m_font01);
    m_hudFruit.setCharacterSize(24);
    m_hudFruit.setFillColor(sf::Color(255, 248, 220, 255));
    m_hudFruit.setPosition(SCREEN_WIDTH * 0.73f, SCREEN_HEIGHT * 0.0001f);

    m_hudTimer.setFont(m_font02);
    m_hudTimer.setCharacterSize(40);
    m_hudTimer.setFillColor(sf::Color(255, 248, 220, 255));
    m_hudTimer.setPosition(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.88f);

    m_hudGameOver.setFont(m_font01);
    m_hudGameOver.setCharacterSize(48);
    m_hudGameOver.setFillColor(sf::Color(255, 248, 220, 255));
    m_hudGameOver.setString("GAME OVER");
    m_hudGameOver.setPosition(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.30f);

    m_hudScore.setFont(m_font01);
    m_hudScore.setCharacterSize(30);
    m_hudScore.setFillColor(sf::Color(255, 248, 220, 255));
    m_hudScore.setString("You Rescued X Clowns!");
    m_hudScore.setPosition(SCREEN_WIDTH * 0.20f, SCREEN_HEIGHT * .65f);

    m_dimmer.setFillColor(sf::Color(0, 0, 0, 150));
    m_dimmer.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    m_pressStartToPlay.setFont(m_font01);
    m_pressStartToPlay.setCharacterSize(48);
    m_pressStartToPlay.setFillColor(sf::Color(255, 248, 220, 255));
    m_pressStartToPlay.setString("PRESS SPACE TO PLAY");
    m_pressStartToPlay.setPosition(SCREEN_WIDTH * 0.02f, SCREEN_HEIGHT * 0.90f);

    setHudLives(3);
    setHudVisitors(0);
    setHudBananas(3);
    setHudTime("0 : 30");
}

Render::~Render(){}

void Render::onDraw()
// This function draws the game world
{
    // DRAW CHARACTERS
    if (m_renderFlicker)
    {
        m_renderFlicker = false;
    }
    else
    {
        m_renderFlicker = true;
    }

    switch (m_game.getGameState())
    {
    case TitleScreen:
        drawTitleScreen();
        break;
    case MainMenu:
        drawMainMenu();
        break;
    case Gameplay:
        drawGameplay();
        break;
    case GameOver:
        drawGameplay();
        break;
    default:
        break;
    }    

    m_window.display();
}

void Render::drawTitleScreen()
{
    m_window.clear();

    m_window.draw(m_game.m_rectShapeTitleScreen);

    if (m_renderFlicker)
    {
        m_window.draw(m_game.m_rectShapeTitleScreenTextStars);
    }

    if (m_flashShow && m_game.getGameState() == GameState::TitleScreen)
    {
        m_window.draw(m_pressStartToPlay);
    }
}

void Render::drawMainMenu()
{
    drawTitleScreen();

    m_window.draw(m_dimmer);

    m_window.draw(m_game.m_rectShapeButton);
}

void Render::drawGameplay()
{
    // Clear the screen and draw your game sprites
    m_window.clear();

    // DRAW BACKGROUND
    m_window.draw(m_level.m_rectShapeBGImage);

    //m_window.draw(m_level.m_rectShape8x8Grid);

    //m_window.draw(m_level.m_circShapeSafeZone);

    

    Player plrRef = m_level.m_player01;

    if (plrRef.m_myState == PlayerInvulnerable)
    {
        if (m_renderFlicker)
        {
            m_window.draw(plrRef.m_rectShapeVis);
            //m_window.draw(plrRef.m_rectShapeCol);
        }
    }
    else
    {
        m_window.draw(plrRef.m_rectShapeVis);
        //m_window.draw(plrRef.m_rectShapeCol);
    }

    for (int i = 0; i < static_cast<int>(m_level.m_monkeys.size()); i++)
    {
        if (m_level.m_monkeys[i].m_isActive)
        {
            m_window.draw(m_level.m_monkeys[i].m_rectShape);
            //m_window.draw(m_level.m_monkeys[i].m_circShape);
        }
    }

    for (int i = 0; i < static_cast<int>(m_level.m_player01.m_bananaBullets.size()); i++)
    {
        if (m_level.m_player01.m_bananaBullets[i].m_myState != BananaInactive)
        {
            m_window.draw(m_level.m_player01.m_bananaBullets[i].m_rectShape);
            //m_window.draw(m_level.m_player01.m_bananaBullets[i].m_circShapeAttractZone);
        }
    }

    switch (m_level.m_visitor.m_myState)
    {
    case VisitorFresh:
        if (m_renderFlicker)
        {
            m_window.draw(m_level.m_visitor.m_rectShape);
        }
        break;
    case VisitorRescue:
        if (m_renderFlicker)
        {
            m_window.draw(m_level.m_visitor.m_rectShape);
        }
        break;
    default:
        m_window.draw(m_level.m_visitor.m_rectShape);
        break;
    }

    switch (m_level.m_ammoBox.m_myState)
    {
    case preSpawn:
        // Do nowt
        break;
    case gettable:
        m_window.draw(m_level.m_ammoBox.m_rectShape);
        break;
    case expiring:
        if (m_renderFlicker)
        {
            m_window.draw(m_level.m_ammoBox.m_rectShape);
        }
        break;
    default:
        break;
    }

    // DRAW HUD
    m_window.draw(m_hudLives);
    m_window.draw(m_hudVisitors);
    m_window.draw(m_hudFruit);

    if (m_level.m_rallyTimer <= 10.0f)
    {
        
        if (m_flashShow)
        {
            m_window.draw(m_hudTimer);
        }
    }
    else
    {
        m_window.draw(m_hudTimer);
    }

    if (m_game.getGameState() == GameState::GameOver)
    {
        drawGameOver();
    }
    
}

void Render::drawGameOver()
{
    m_window.draw(m_dimmer);
    m_window.draw(m_hudGameOver);
    m_hudScore.setString("You Saved " + std::to_string(m_level.m_visitorScore) + " Clowns!");
    m_window.draw(m_hudScore);
}

void Render::onUpdate(sf::Time t_deltaTime)
{
    if (m_flashTimer > 0)
    {
        m_flashTimer -= t_deltaTime.asSeconds();
    }
    else
    {
        m_flashTimer = M_FLASH_PERIOD;
        m_flashShow = !m_flashShow;
    }
}

void Render::setHudLives(int lives)
{
    std::string output = "Lives: " + std::to_string(lives) + " / 3";
    m_hudLives.setString(output);
    
}

//void Render::setHudBananas(int bananas)
//{
//    std::string output = "Lives: " + std::to_string(lives) + " / 3";
//}

void Render::setHudVisitors(int visitors)
{
    std::string output = "Visitors: " + std::to_string(visitors) + "";
    m_hudVisitors.setString(output);
}

void Render::setHudBananas(int bananas)
{
    std::string output = "Fruit: " + std::to_string(bananas) + " / 3";
    m_hudFruit.setString(output);
}

void Render::setHudTime(std::string time)
{
    std::string output = "TIME: " + time; // std::to_string(time);
    m_hudTimer.setString(output);
}
