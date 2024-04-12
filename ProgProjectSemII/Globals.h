// Mon 8nd of April demo
// x The player moving within the boundary of the screen using 4 keys.
// x The player should look in the direction it is facing.
// One of the NPCs(enemy) types moving around within the boundary of the screen.
// You should have more than one object of this NPC type moving on the screen.
//
// Mon 15th of April demo
// The second NPCs(enemy) type moving around within the boundary of the screen.
// You should have more than one object of this NPC type moving on the screen.
// Collision detection between game entities(including player weapon fire).
//
// Mon 22th of April demo
// Scoring & new game
//
// Fri the 26th of April
// Final Project code due : (put on GitHub).
//
// Monday 29nd April or Wed 1st May(9am – 11 noon)
// Final demos are taking place in the lab

// Contains the game globals
#pragma once

// The direction the sprite is moving in
const int static WEST = 1;
const int static EAST = 2;
const int static NORTH = 3;  // direction north
const int static SOUTH = 4;
// the size of the screen in pixels used in the game
const float SCREEN_WIDTH = 160 * 4.0f;// Previous Value = 800;   // Original value 1500
const float SCREEN_HEIGHT = 144 * 4.0f; // Previous Value = 480;  // Original value 800

const sf::Vector2f VEC2F_ZERO = sf::Vector2f(0.0f, 0.0f);