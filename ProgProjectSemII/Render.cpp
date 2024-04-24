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
    m_hudTimer.setCharacterSize(24);
    m_hudTimer.setFillColor(sf::Color(255, 248, 220, 255));
    m_hudTimer.setPosition(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.95f);

    setHudLives(3);
    setHudVisitors(0);
    setHudBananas(3);
    setHudTime(5.0f);
}

Render::~Render(){}

void Render::onDraw()
// This function draws the game world
{
    // Clear the screen and draw your game sprites
    m_window.clear();

    // DRAW BACKGROUND
    m_window.draw(m_level.m_rectShapeBGImage);

    //m_window.draw(m_level.m_rectShape8x8Grid);

    //m_window.draw(m_level.m_circShapeSafeZone);

    // DRAW CHARACTERS
    if (renderFlicker)
    {
        renderFlicker = false;
    }
    else
    {
        renderFlicker = true;
    }

    Player plrRef = m_level.m_player01;

    if (plrRef.m_myState == PlayerInvulnerable)
    {
        if (renderFlicker)
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
            m_window.draw(m_level.m_player01.m_bananaBullets[i].m_circShapeAttractZone);
        }
    }

    for (int i = 0; i < static_cast<int>(m_level.m_visitors.size()); i++)
    {
        switch (m_level.m_visitors[i].myState)
        {
        case VisitorInactive:

            break;
        case VisitorRescue:
            if (renderFlicker)
            {
                m_window.draw(m_level.m_visitors[i].m_rectShape);
            }
            break;
        default:
            m_window.draw(m_level.m_visitors[i].m_rectShape);
            break;
        }
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
        if (renderFlicker)
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
    m_window.draw(m_hudTimer);

    m_window.display();
}

void Render::onUpdate()
{
    
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
    std::string output = "Visitors: " + std::to_string(visitors) + " / 4";
    m_hudVisitors.setString(output);
}

void Render::setHudBananas(int bananas)
{
    std::string output = "Fruit: " + std::to_string(bananas) + " / 3";
    m_hudFruit.setString(output);
}

void Render::setHudTime(float time)
{
    std::string output = "TIME LEFT: " + std::to_string(time);
    m_hudTimer.setString(output);
}
