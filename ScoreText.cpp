//project inlcude
#include "ScoreText.h"
#include "Framework/AssetManager.h"

ScoreText::ScoreText()
	: TextObject()
{
	m_Text.setFont(AssetManager::GetFont("fonts/mainfont.ttf"));
	m_Text.setCharacterSize(50);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setStyle(sf::Text::Bold | sf::Text::Italic);
	m_Text.setString("Score: 0");
}

void ScoreText::PositionOnScreen(float width, float height)
{
	//set text size to screen size
	//it does this by dividing the screen size by the textures width or height respectively
	m_Text.setPosition(width / 2 - m_Text.getLocalBounds().width, height - m_Text.getLocalBounds().height * 4);
}

void ScoreText::UpdateScore(int _score)
{
	m_Text.setString("Score: " + std::to_string(_score));
}