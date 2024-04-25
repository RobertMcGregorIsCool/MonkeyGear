#include "Input.h"

// FORWARD DEPENDENCY
#include "Game.h"

Input::Input(Level& t_level01, Render& t_render, Game& t_game) : m_level01{ t_level01 }, m_render{ t_render }, m_game{ t_game } {}

Input::~Input(){}

void Input::onUpdate()
{// This can be flagged as a keylogger, apparently!
    //m_desiredDir = VEC2F_ZERO; // Reinitialise m_desiredDir to zero.

    //// get keyboard input
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    //    m_desiredDir.x = -1.0f;
    //}
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    //    m_desiredDir.x = 1.0f;
    //}
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //{
    //    m_desiredDir.y = -1.0f;
    //}
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //{
    //    m_desiredDir.y = 1.0f;
    //}

    //// update any game variables here ...
    //m_level01.m_player01.setDesiredDir(m_desiredDir);
}

// void Input::onProcessEvents(sf::Event event)
void Input::onProcessEvents()
{
    sf::Event event;

    while (m_render.m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) m_render.m_window.close();

        //m_mouseCur.x = newEvent.mouseMove.x;
        //m_mouseCur.y = newEvent.mouseMove.y;

        switch (event.type)
        {
        case sf::Event::Closed:
            m_render.m_exitGame = true;
            break;
        case sf::Event::KeyPressed:
            onKeyPressed(event);
            break;
        case sf::Event::KeyReleased:
            onKeyReleased(event);
            break;
        default:
            break;
        }
    }
    
    m_level01.m_player01.setDesiredDir(m_desiredDir);
}

void Input::onKeyPressed(sf::Event event)
{
    switch (m_game.getGameState())
    {
    case TitleScreen:
        if (sf::Keyboard::Space == event.key.code && !m_pressedSpace)
        {
            m_pressedSpace = true;
            m_game.setGameState(GameState::MainMenu);
            m_desiredDir = VEC2F_ZERO;
        }
        break;
    case MainMenu:
        if (sf::Keyboard::Space == event.key.code && !m_pressedSpace)
        {
            m_pressedSpace = true;
            m_game.setGameState(GameState::Gameplay);
            m_desiredDir = VEC2F_ZERO;
        }
        break;
    case Gameplay:
        if (sf::Keyboard::Left == event.key.code || sf::Keyboard::A == event.key.code)
        {
            m_desiredDir.x = -1.0f;
        }
        if (sf::Keyboard::Right == event.key.code || sf::Keyboard::D == event.key.code)
        {
            m_desiredDir.x = 1.0f;
        }
        if (sf::Keyboard::Up == event.key.code || sf::Keyboard::W == event.key.code)
        {
            m_desiredDir.y = -1.0f;
        }
        if (sf::Keyboard::Down == event.key.code || sf::Keyboard::S == event.key.code)
        {
            m_desiredDir.y = 1.0f;
        }

        if (m_desiredDir != VEC2F_ZERO)
        {
            m_desiredDirPrev = m_desiredDir; // Problem with firing diagonally
        }
        break;
    case GameOver:
        if (sf::Keyboard::Space == event.key.code && !m_pressedSpace)
        {
            m_pressedSpace = true;
            m_game.setGameState(GameState::TitleScreen);
            // Ultimately want to stop player here, but let them orientate.
        }
        break;
    default:
        break;
    }
}

void Input::onKeyReleased(sf::Event event)
{

    if(sf::Keyboard::Escape == event.key.code)
    {
        m_render.m_exitGame = true;
    }

    switch (m_game.getGameState())
    {
    case TitleScreen:
        if (sf::Keyboard::Space == event.key.code)
        {
            m_pressedSpace = false;
            m_releasedSpaceIgnoreFirst = true;
        }
        break;
    case MainMenu:
        if (sf::Keyboard::Space == event.key.code)
        {
            m_pressedSpace = false;
            m_releasedSpaceIgnoreFirst = true;
        }
        break;
    case Gameplay:
        if (sf::Keyboard::Left == event.key.code || sf::Keyboard::A == event.key.code)
        {
            if (m_desiredDir.x == -1.0f) m_desiredDir.x = 0.0f;
        }
        if (sf::Keyboard::Right == event.key.code || sf::Keyboard::D == event.key.code)
        {
            if (m_desiredDir.x == 1.0f) m_desiredDir.x = 0.0f;
        }
        if (sf::Keyboard::Up == event.key.code || sf::Keyboard::W == event.key.code)
        {
            if (m_desiredDir.y == -1.0f) m_desiredDir.y = 0.0f;
        }
        if (sf::Keyboard::Down == event.key.code || sf::Keyboard::S == event.key.code)
        {
            if (m_desiredDir.y == 1.0f) m_desiredDir.y = 0.0f;
        }

        if (sf::Keyboard::Space == event.key.code)
        {
            if (m_releasedSpaceIgnoreFirst)
            {
                m_releasedSpaceIgnoreFirst = false;
            }
            else
            {
                m_pressedSpace = false;
                m_level01.m_player01.throwBanana(Hlp::v2fGetNormal(m_desiredDirPrev));
            }
        }
        break;
    case GameOver:
        if (sf::Keyboard::Space == event.key.code)
        {
            m_pressedSpace = false;
        }
        break;
    default:
        break;
    }

    
}


