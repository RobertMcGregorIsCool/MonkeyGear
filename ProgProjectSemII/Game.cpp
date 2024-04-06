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
// 01) Too awesome.

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

Game::Game(){}

void Game::loadContent() {} // Load font file & setup message string REMOVE!

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

  while (m_render.m_window.isOpen()) {
    // check if the close window button is clicked on
    sf::Event event;
    
    while (m_render.m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) m_render.m_window.close();
    }
    processEvents(event); // Process as many events as possible

    // get the time since last update and restart the clock
    timeSinceLastUpdate += clock.restart();

    // update every 60th of a second - see var fps
    // only when time since last update is greater than 1/60 update world.
    if (timeSinceLastUpdate > timePerFrame) {
      update(timePerFrame);

      // reset the timeSinceLastUpdate to 0
      timeSinceLastUpdate = sf::Time::Zero;
    }
    m_render.onDraw(); // Draw as much as is possible - ideally more than 60fps.
  }  // end while loop
}

void Game::update(sf::Time t_deltaTime)
// This function takes the keyboard input and updates the game world
{
    if (m_render.m_exitGame)
    {
        m_render.m_window.close();
    }

    m_input.onUpdate(t_deltaTime);
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents(sf::Event event)
{
    m_input.onProcessEvents(event);
}    