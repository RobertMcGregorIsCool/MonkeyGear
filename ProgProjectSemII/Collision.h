#pragma once
#include "Level.h"

class Collision
{
	// WIP Player / Monkey	= LoseLife/Teleport
	// WIP Player / Visitor	= Follow
	// Player / AmmoBox	= More ammo
	// WIP Player / SafeZone= N/A
	// Visitor/ Monkey	= Cower
	// Visitor/ Banana	= N/A
	// Visitor/ SafeZone= N/A
	// Monkey / BananaAr= Eat
	// Monkey / BananaGd= Eat
	// Visitor/ Solid	= Impassible
	// Player / Solid	= Impassible
	// Monkey / Solid	= Impassible
	// Bananna/ Solid	= Impassible

	void playerMonkey();
	void playerVisitor();
	void monkeyBanana();
	void visitorSafeZone();

public:
	Level& m_level;

	Collision(Level& t_level);
	~Collision();

	void onUpdate();
};

