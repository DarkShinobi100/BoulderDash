//project inlcude
#include "Startscreen.h"
#include "Framework/AssetManager.h"

Startscreen::Startscreen()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/Start.png"));
	m_BGM.setBuffer(AssetManager::GetSoundBuffer("audio/BGM.ogg"));
	m_BGM.setLoop(true);
}

void Startscreen::ScaleToFit(float width, float height)
{
	//set sprite size to screen size
	//it does this by dividing the screen size by the textures width or height respectively
	m_Sprite.setScale(width / m_Sprite.getLocalBounds().width, height / m_Sprite.getLocalBounds().height);
}

void Startscreen::StartMusic()
{
	//play music
	m_BGM.play();
}