#include "Assets.h"

Assets::Assets()
{
	if (!m_spriteSheet.loadFromFile("ASSETS\\monkeyGearSketch01001RS.png"))
	{
		std::cout << "monkeyGearSketch01001RS.png failed to load."; // 42x60
	}

	if (!m_spriteSheet.loadFromFile("ASSETS\\monkeyGearSpriteSheet01001RS.png"))
	{
		std::cout << "monkeyGearSpriteSheet01001RS.png failed to load."; // 42x60
	}
}

Assets::~Assets()
{
}
