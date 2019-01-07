//project inlcude
#include "ResetButton.h"
#include "Framework/AssetManager.h"
#include "Level.h"

ResetButton::ResetButton()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/button.png"));
}

void ResetButton::PositionOnScreen(float width, float height)
{
	//set text size to screen size
	//it does this by dividing the screen size by the textures width or height respectively
	m_Sprite.setPosition(width / 2 - m_Sprite.getLocalBounds().width, (height / 3 + m_Sprite.getLocalBounds().height) * 2);
}

//function for when clicked run reset level
bool ResetButton::OnClicked(sf::Event _gameEvent)
{
	if (m_Sprite.getGlobalBounds().contains(_gameEvent.mouseButton.x, _gameEvent.mouseButton.y))
	{
		
	//function for when clicked run reset level
		return true;
	}
	return false;
}