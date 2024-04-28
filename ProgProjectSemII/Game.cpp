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
// 02) Possible for menu buttons to not recieve clicks on every part of buttons.
// 03) Console reports, "Failed to retrieve pixel format information: The 
// operation completed successfully."
// 04) Firing diagonally can be tricky, input a little sticky. To be fixed

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
  aGame.run();

  return 0;
}

Game::Game()
{
    m_rectShapeTitleScreen.setTexture(&m_assets.m_titleScreen);
    m_rectShapeTitleScreen.setSize(SCREEN_SIZE);

    m_rectShapeTitleScreenTextStars.setTexture(&m_assets.m_titleScreenTextStars);
    m_rectShapeTitleScreenTextStars.setSize(SCREEN_SIZE);

    m_rectShapeHowToPlay.setTexture(&m_assets.m_howToPlay);
    m_rectShapeHowToPlay.setSize(SCREEN_SIZE);

    setGameState(GameState::GSTitleScreen);
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

  while (m_render.m_window.isOpen()) {
    // check if the close window button is clicked on
    
    processEvents(); // Process as many events as possible

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

    switch (m_myState)
    {
    case GSTitleScreen:
        m_render.onUpdate(t_deltaTime);
        break;
    case GSMainMenu:
        break;
    case GSGameplay:
        m_input.onUpdate();
        m_level01.onUpdate(t_deltaTime, *this);
        m_render.onUpdate(t_deltaTime);
        break;
    case GSGameOver: // Not sure I ended up using this, Gameover is via Level, right?
        break;
    default:
        break;
    }
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
    m_input.onProcessEvents();
}

/// <summary>
/// External access to GameState
/// </summary>
/// <param name="t_newState">Sent new state</param>
void Game::setGameState(GameState t_newState)
{
    switch (t_newState)
    {
    case GSTitleScreen:
        break;
    case GSMainMenu:
        break;
    case GSGameplay:
        m_level01.onReset();
        break;
    case GSGameOver:
        break;
    default:
        break;
    }
    m_myState = t_newState;
}

/// <summary>
/// Ends the game
/// </summary>
void Game::quitGame()
{
    m_render.m_window.close();
}
