#include "Input.h"
#include "Hlp.h"

Input::Input(Level& t_level01, Render& t_render) : m_level01{t_level01}, m_render{t_render}{}

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

    if (sf::Keyboard::Space == event.key.code)
    {
        // Ultimately want to stop player here, but let them orientate.
    }
}

void Input::onKeyReleased(sf::Event event)
{
    if(sf::Keyboard::Escape == event.key.code)
    {
        m_render.m_exitGame = true;
    }

    

    if (sf::Keyboard::Left == event.key.code || sf::Keyboard::A == event.key.code)
    {
        if(m_desiredDir.x == -1.0f) m_desiredDir.x = 0.0f;
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
        m_level01.m_player01.throwBanana(Hlp::v2fGetNormal(m_desiredDirPrev));
    }
}


