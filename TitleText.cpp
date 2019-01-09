//project inlcude
#include "TitleText.h"
#include "Framework/AssetManager.h"

TitleText::TitleText()
	: TextObject()
{
	m_Text.setFont(AssetManager::GetFont("fonts/mainfont.ttf"));
	m_Text.setCharacterSize(50);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setStyle(sf::Text::Bold | sf::Text::Italic);
	m_Text.setString("BoulderDash Rougelike Version");
}

void TitleText::ScaleToFit(float width)
{
	//set text size to screen size
	//it does this by dividing the screen size by the textures width or height respectively
	m_Text.setPosition((width / 2) - (m_Text.getLocalBounds().width/2), 50);
}