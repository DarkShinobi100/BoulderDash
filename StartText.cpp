//project inlcude
#include "StartText.h"
#include "Framework/AssetManager.h"

StartText::StartText()
	: TextObject()
{
	m_Text.setFont(AssetManager::GetFont("fonts/mainfont.ttf"));
	m_Text.setCharacterSize(25);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setStyle(sf::Text::Bold | sf::Text::Italic);
	m_Text.setString("Please Press enter");
}

void StartText::ScaleToFit(float width, float height)
{
	//set text size to screen size
	//it does this by dividing the screen size by the textures width or height respectively
	m_Text.setPosition(width / 2 - m_Text.getLocalBounds().width, (height / 3 + m_Text.getLocalBounds().height)*2);
}