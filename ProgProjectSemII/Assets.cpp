#include "Assets.h"

Assets::Assets()
{
	if (!m_spriteSheet.loadFromFile("ASSETS/PROJECT_SPRITES/enemy1.png"))
	{
		std::cout << "enemy1.png failed to load."; // 42x60
	}
}

Assets::~Assets()
{
}
