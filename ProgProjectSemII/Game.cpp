// Name: RoBert McGregor
// Login: C00302210
// Starting Date: 05/04/2024
// Approximate time taken:
//---------------------------------------------------------------------------
// Project description: Semester2ProgrammingProject2024
// The player must rescue visitors from patrolling hungry monkeys, which will
// harm the player on contact
// ---------------------------------------------------------------------------
// Known Bugs:
// ?

////////////////////////////////////////////////////////////
// include correct library file for release and debug versions
////////////////////////////////////////////////////////////

#ifdef _DEBUG
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#else
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-network.lib")
#endif
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "Game.h"  // include Game header file

int main() {
  Game aGame;
  aGame.loadContent();
  aGame.run();

  return 0;
}

Game::Game()
    : m_window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH),
                           static_cast<int>(SCREEN_HEIGHT)),
             "Joint Project Game", sf::Style::Default)
// Default constructor
{}

void Game::loadContent()
// Load the font file & setup the message string
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

void Game::run()
// This function contains the main game loop which controls the game.
{
  srand((int)time(nullptr));  // set the seed once

  const float fps{ 60.0f };

  sf::Time timePerFrame = sf::seconds(1.0f / fps);

  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  // the clock object keeps the time.
  sf::Clock clock;

  clock.restart();

  while (m_window.isOpen()) {
    // check if the close window button is clicked on
    sf::Event event;
    
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) m_window.close();
    }
    processEvents(event); // Process as many events as possible

    // get the time since last update and restart the clock
    timeSinceLastUpdate += clock.restart();

    // update every 60th of a second - see var fps
    // only when the time since last update is greater than 1/60 update the
    // world.
    if (timeSinceLastUpdate > timePerFrame) {
      update(timePerFrame);
      

      // reset the timeSinceLastUpdate to 0
      timeSinceLastUpdate = sf::Time::Zero;
    }
    draw(); // Draw as much as is possible - ideally more than 60fps.
  }  // end while loop
}

void Game::update(sf::Time t_deltaTime)
// This function takes the keyboard input and updates the game world
{
    if (m_exitGame)
    {
        m_window.close();
    }

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
  player.move(t_deltaTime, m_desiredDir);
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents(sf::Event event)
{
    // sf::Event newEvent;
    while (m_window.pollEvent(event))
    {
        //m_mouseCur.x = newEvent.mouseMove.x;
        //m_mouseCur.y = newEvent.mouseMove.y;

        if (sf::Event::Closed == event.type) // window message
        {
            m_exitGame = true;
        }
    }
}    

void Game::draw()
// This function draws the game world
{
  // Clear the screen and draw your game sprites
  m_window.clear();

  m_message.setString("Game Play");
  m_window.draw(m_message);  // write message to the screen
  m_window.draw(player.m_rectShape);

  m_window.display();
}