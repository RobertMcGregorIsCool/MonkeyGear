#include "Render.h"
#include <iostream>

Render::Render(Level& t_level) : m_window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH),
    static_cast<int>(SCREEN_HEIGHT)),
    "Monkey Gear", sf::Style::Default), m_level(t_level)
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

    m_time.setFont(m_font02);
    m_time.setCharacterSize(24);
    m_time.setFillColor(sf::Color(255, 248, 220, 255));
    m_time.setPosition(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.95f);

    setHudLives(3);
    setHudVisitors(4);
    setHudFruit(4);
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

    m_window.draw(m_level.m_rectShape8x8Grid);

    // DRAW CHARACTERS
    Player plrRef = m_level.m_player01;

    if (plrRef.m_myState == PlayerInvulnerable)
    {
        if (renderPlayer)
        {
            m_window.draw(plrRef.m_rectShapeVis);
            //m_window.draw(plrRef.m_rectShapeCol);
            renderPlayer = false;
        }
        else
        {
            renderPlayer = true;
        }
    }
    else
    {
        m_window.draw(plrRef.m_rectShapeVis);
        //m_window.draw(plrRef.m_rectShapeCol);
    }

    for (int i = 0; i < static_cast<int>(m_level.m_monkeys.size()); i++)
    {
        if (m_level.m_monkeys[i].isActive)
        {
            m_window.draw(m_level.m_monkeys[i].m_rectShape);
            //m_window.draw(m_level.m_monkeys[i].m_circShape);
        }
    }

    // DRAW HUD
    m_window.draw(m_hudLives);
    m_window.draw(m_hudVisitors);
    m_window.draw(m_hudFruit);
    m_window.draw(m_time);

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

void Render::setHudVisitors(int visitors)
{
    std::string output = "Visitors: " + std::to_string(visitors) + " / 4";
    m_hudVisitors.setString(output);
}

void Render::setHudFruit(int fruit)
{
    std::string output = "Fruit: " + std::to_string(fruit) + " / 3";
    m_hudFruit.setString(output);
}

void Render::setHudTime(float time)
{
    std::string output = "TIME LEFT: " + std::to_string(time);
    m_time.setString(output);
}
