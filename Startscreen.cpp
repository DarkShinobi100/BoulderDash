//project inlcude
#include "Startscreen.h"
#include "Framework/AssetManager.h"

Startscreen::Startscreen()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/Start.png"));
}

void Startscreen::ScaleToFit(float width, float hieght)
{
	//set sprite size to screen size
	//it does this by diving the screen size by the textures width or height respectively
	m_Sprite.setScale(width / m_Sprite.getLocalBounds().width, hieght / m_Sprite.getLocalBounds().height);
}