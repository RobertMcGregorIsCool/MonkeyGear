// Contains the game globals
#pragma once

const float SCREEN_SCALAR = 4.0f; // Given the original Gameboy resolution, this is scaled up for modern displays.

// the size of the screen in pixels used in the game
const float SCREEN_WIDTH = 160 * SCREEN_SCALAR;
const float SCREEN_HEIGHT = 144 * SCREEN_SCALAR;
const sf::Vector2f SCREEN_SIZE {SCREEN_WIDTH, SCREEN_HEIGHT};

const sf::Vector2f VEC2F_ZERO = sf::Vector2f(0.0f, 0.0f);