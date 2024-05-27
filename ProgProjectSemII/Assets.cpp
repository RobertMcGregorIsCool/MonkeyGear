/// <summary>
/// Project description: Semester2ProgrammingProject2024
/// @author RoBert McGregor (C00302210)
/// @date April 2024
/// </summary>

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

	if (!m_musStageSelect.openFromFile("ASSETS/AUDIO/Juhani Junkala [Chiptune Adventures] 4. Stage Select.ogg"))
	{
		std::cout << "Music StageSelect.ogg failed to load";
	}
	m_musStageSelect.setLoop(true);
	m_musStageSelect.setVolume(10);

	if (!m_musStage02.openFromFile("ASSETS/AUDIO/Juhani Junkala [Chiptune Adventures] 2. Stage 2.ogg"))
	{
		std::cout << "Music Stage 2.ogg failed to load.";
	}
	m_musStage02.setLoop(true);
	m_musStage02.setVolume(10);

	if (!m_bufMonkeyScream.loadFromFile("ASSETS/AUDIO/325549__archeos__monkey-screaming.wav"))
	{
		std::cout << "Monkey-screaming.wav failed to load.";
	}

	if (!m_bufPickup.loadFromFile("ASSETS/AUDIO/Picked Coin Echo 2.wav"))
	{
		std::cout << "Picked coin echo 2.wav failed to load.";
	}

	if (!m_bufPlayerDeath.loadFromFile("ASSETS/AUDIO/PlayerDeath.ogg"))
	{
		std::cout << "PlayerDeath.ogg failed to load.";
	}

	if (!m_bufVisitorAahh.loadFromFile("ASSETS/AUDIO/VisitorAahh.ogg"))
	{
		std::cout << "VisitorAahh.ogg failed to load.";
	}

	if (!m_bufVisitorOkay.loadFromFile("ASSETS/AUDIO/VisitorOkay.ogg"))
	{
		std::cout << "VisitorOkay.ogg failed to load.";
	}

	if (!m_bufVisitorWoohoo.loadFromFile("ASSETS/AUDIO/VisitorWoohoo.ogg"))
	{
		std::cout << "VisitorWoohoo.ogg failed to load.";
	}

	if (!m_bufBikeHorn.loadFromFile("ASSETS/AUDIO/bicycle-horn-1.wav"))
	{
		std::cout << "bicycle-horn-1.wav failed to load";
	}

	m_sfxMonkeyScream.setBuffer(m_bufMonkeyScream);
	m_sfxPickup.setBuffer(m_bufPickup);
	m_sfxPlayerDeath.setBuffer(m_bufPlayerDeath);
	m_sfxVisitorAahh.setBuffer(m_bufVisitorAahh);
	m_sfxVisitorOkay.setBuffer(m_bufVisitorOkay);
	m_sfxVisitorWoohoo.setBuffer(m_bufVisitorWoohoo);
	m_sfxBikeHorn.setBuffer(m_bufBikeHorn);
}

Assets::~Assets(){}