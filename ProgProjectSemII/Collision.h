#pragma once
#include "Level.h"

class Collision
{
	

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

