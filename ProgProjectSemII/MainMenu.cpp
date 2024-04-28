/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

#include "MainMenu.h"

// FORWARD DEPENDENCY
#include "Game.h"

MainMenu::MainMenu(Assets& t_assets, Game& t_game) : m_assets {t_assets}, m_game{t_game}
{
    std::string menuTexts[] = { "Play", "How to Play", "Quit" };

    m_rectShapeButton.setTexture(&m_assets.m_spriteSheet);
    m_intRect = { 192, 32, 64, 16 };
    m_rectShapeButton.setTextureRect(m_intRect);
    m_rectShapeButton.setSize(sf::Vector2f(M_BUTTON_WDH * SCREEN_SCALAR, M_BUTTON_HGT * SCREEN_SCALAR));
    m_rectShapeButton.setScale(sf::Vector2f(1.5f, 1.5f));
    m_rectShapeButton.setOrigin(m_rectShapeButton.getSize() * 0.5f);

    for (int i = 0; i < M_MENU_OPTIONS; i++)
    {
        m_textButtons[i].setFont(m_assets.m_font01);
        m_textButtons[i].setFillColor(sf::Color(255, 248, 220, 255));
        m_textButtons[i].setCharacterSize(40);
        m_textButtons[i].setString(menuTexts[i]);
        float butnXSizLessTextXSizThenHalved = (M_BUTTON_WDH - m_textButtons[i].getLocalBounds().width) * 0.5f;
        m_textButtons[i].setPosition(M_BUTTON_X_START + butnXSizLessTextXSizThenHalved, M_BUTTON_Y_START + (M_BUTTON_GAP + M_BUTTON_HGT) * i);
        m_buttonLocations[i] = sf::Vector2f(SCREEN_WIDTH * 0.5f, 32.0f + M_BUTTON_Y_START + (M_BUTTON_GAP + M_BUTTON_HGT) * i);
    }
}

MainMenu::~MainMenu(){}

/// <summary>
/// Called from Render::Draw
/// </summary>
/// <param name="t_window">Target window</param>
void MainMenu::onRender(sf::RenderWindow& t_window)
{
    for (int i = 0; i < M_MENU_OPTIONS; i++)
    {
        m_rectShapeButton.setPosition(m_buttonLocations[i]);
        t_window.draw(m_rectShapeButton);
        t_window.draw(m_textButtons[i]);
    }
}
