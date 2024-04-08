#include "Input.h"

Input::Input(Level01& t_level01, Render& t_render) : m_level01{t_level01}, m_render{t_render}
{
}

Input::~Input()
{
}

void Input::onUpdate()
{
    m_desiredDir = VEC2F_ZERO; // Reinitialise m_desiredDir to zero.

    // get keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_desiredDir.x = -1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_desiredDir.x = 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_desiredDir.y = -1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_desiredDir.y = 1.0f;
    }

    // update any game variables here ...
    m_level01.m_player01.setDesiredDir(m_desiredDir);


    // m_level01.m_player01.move(m_desiredDir); t_deltaTime,
}

void Input::onProcessEvents(sf::Event event)
{
    while (m_render.m_window.pollEvent(event))
    {
        std::cout << "Event is polled.";

        //m_mouseCur.x = newEvent.mouseMove.x;
        //m_mouseCur.y = newEvent.mouseMove.y;

        if (sf::Event::Closed == event.type) // window message
        {
            m_render.m_exitGame = true;
        }
        if (sf::Event::KeyReleased == event.type)
        {
            onKeyReleased(event);
        }
    }
}

void Input::onKeyReleased(sf::Event event)
{
    if(sf::Keyboard::Escape == event.key.code)
    {
        m_render.m_exitGame = true;

    }
}


