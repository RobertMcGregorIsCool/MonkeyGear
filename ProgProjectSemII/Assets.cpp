#include "Assets.h"

Assets::Assets()
{
	if (!m_font01.loadFromFile("ASSETS/FONTS/Silkscreen/slkscr.ttf")) 
	{
		std::cout << "Error loading slkscr.ttf";
	}
	if (!m_font02.loadFromFile("ASSETS/FONTS/Silkscreen/slkscreb.ttf")) 
	{
		std::cout << "Error loading slkscreb.ttf";
	}

	if (!m_background01.loadFromFile("ASSETS\\monkeyGearBG01001RS.png"))
	{
		std::cout << "monkeyGearBG01001RS.png failed to load."; // 42x60
	}

	if (!m_8x8GreyGrid.loadFromFile("ASSETS\\8x8GreyGridBG01001RS.png"))
	{
		std::cout << "8x8GreyGridBG01001RS.png failed to load."; // 42x60
	}

	if (!m_spriteSheet.loadFromFile("ASSETS\\monkeyGearSpriteSheet01008RS.png"))
	{
		std::cout << "monkeyGearSpriteSheet01008RS.png failed to load."; // 42x60
	}

	if (!m_titleScreen.loadFromFile("ASSETS\\monkeyGearTitleScreen01002RS.png"))
	{
		std::cout << "monkeyGearTitleScreen01002RS.png failed to load.";
	}

	if (!m_titleScreenTextStars.loadFromFile("ASSETS\\monkeyGearTitleScreenStars01002RS.png"))
	{
		std::cout << "monkeyGearTitleScreenStars01002RS.png failed to load.";
	}

	if (!m_howToPlay.loadFromFile("ASSETS\\howToPlay01001RS.png"))
	{
		std::cout << "howToPlay01001RS.png failed to load.";
	}
}

Assets::~Assets()
{
}
