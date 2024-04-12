#include "Render.h"
#include <iostream>

Render::Render(Level& t_level) : m_window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH),
    static_cast<int>(SCREEN_HEIGHT)),
    "Monkey Gear", sf::Style::Default), m_level(t_level)
{
    if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf")) {
        std::cout << "error with font file file";
    }

    // set up the message string
    m_message.setFont(m_font);                 // set the font for the text
    m_message.setCharacterSize(24);            // set the text size
    m_message.setFillColor(sf::Color::White);  // set the text colour
    m_message.setPosition(10, 10);             // its position on the screen
}

Render::~Render()
{
}

void Render::onDraw()
// This function draws the game world
{
    // Clear the screen and draw your game sprites
    m_window.clear();

    m_message.setString("Game Play");
    m_window.draw(m_message);  // write message to the screen
    m_window.draw(m_level.m_player01.m_rectShape);

    for (int i = 0; i < m_level.m_monkeys.size(); i++)
    {
        if (m_level.m_monkeys[i].isActive)
        {
            m_window.draw(m_level.m_monkeys[i].m_rectShape);
            m_window.draw(m_level.m_monkeys[i].m_circShape);
        }
    }

    

    m_window.display();
}
