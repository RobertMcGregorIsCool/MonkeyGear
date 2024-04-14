#include "Assets.h"

Assets::Assets()
{
	if (!m_background01.loadFromFile("ASSETS\\monkeyGearBG01001RS.png"))
	{
		std::cout << "monkeyGearBG01001RS.png failed to load."; // 42x60
	}

	if (!m_8x8GreyGrid.loadFromFile("ASSETS\\8x8GreyGridBG01001RS.png"))
	{
		std::cout << "8x8GreyGridBG01001RS.png failed to load."; // 42x60
	}

	if (!m_spriteSheet.loadFromFile("ASSETS\\monkeyGearSpriteSheet01001RS.png"))
	{
		std::cout << "monkeyGearSpriteSheet01001RS.png failed to load."; // 42x60
	}
}

Assets::~Assets()
{
}
