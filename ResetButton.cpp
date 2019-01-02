//project inlcude
#include "ResetButton.h"
#include "Framework/AssetManager.h"
#include "Level.h"

ResetButton::ResetButton()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/Start.png"));
}

void ResetButton::PositionOnScreen(float width)
{
	//set text size to screen size
	//it does this by dividing the screen size by the textures width or height respectively
	m_Sprite.setPosition(width / 2 - m_Sprite.getLocalBounds().width, 500);
}

//function for when clicked run reset level
void ResetButton::OnClicked()
{
	//function for when clicked run reset level
	m_Level->ReloadLevel();
}