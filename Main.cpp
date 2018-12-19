// Library Includes
#include <SFML/Window.hpp>	
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cstdlib>
#include <ctime>

// Project Includes
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Startscreen.h"

// The main() Function - entry point for our program
int main()
{
	// -----------------------------------------------
	// Game Setup
	// -----------------------------------------------

	// Window - to draw to the screen
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "BoulderDash!", sf::Style::Titlebar | sf::Style::Close);

	// Seed our random number generator 
	srand(time(NULL));

	// Create AssetManager
	AssetManager assets;

	// Game Clock - to keep track of time passed each frame
	sf::Clock gameClock;

	//Create the game level
	Level OurLevel;

	//set up game start
	bool GameStart = true;

	//create the start screen pic
	Startscreen Start;
	Start.ScaleToFit(gameWindow.getSize().x, gameWindow.getSize().y);
	
	//Create font
	sf::Font gameFont;
	gameFont.loadFromFile("fonts/mainfont.ttf");


	//create Title
	sf::Text titleText;
	titleText.setFont(gameFont);
	titleText.setString("BoulderDash-Rougelike Version");
	titleText.setCharacterSize(50);
	titleText.setFillColor(sf::Color::White);
	titleText.setStyle(sf::Text::Bold | sf::Text::Italic);
	titleText.setPosition(gameWindow.getSize().x / 2
		- titleText.getLocalBounds().width / 2, 30);

	//setup Note Text 
	sf::Text NoteText;
	NoteText.setFont(gameFont);
	NoteText.setString("Please Press enter");
	NoteText.setCharacterSize(25);
	NoteText.setFillColor(sf::Color::Cyan);

	NoteText.setPosition(gameWindow.getSize().x / 2
		- titleText.getLocalBounds().width / 2, gameWindow.getSize().y / 2
		- titleText.getLocalBounds().height / 2);
	
	//score 
	int score = 0; //set score to 0

    //setup score Text
	sf::Text scoreText;
	scoreText.setFont(gameFont);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::White);

	scoreText.setPosition((gameWindow.getSize().x / 2) - 85, 200);

	// -----------------------------------------------
	// Game Loop
	// -----------------------------------------------
	while (gameWindow.isOpen())
	{
		// -----------------------------------------------
		// Input Section
		// -----------------------------------------------

		// Check all events since the last frame and process 
		// each one until there are no more
		sf::Event gameEvent;
		while (gameWindow.pollEvent(gameEvent))
		{
			//check if game has just started
			if (GameStart)
			{
				//wait for player to press enter 
				if (gameEvent.key.code == sf::Keyboard::Enter)
				{//now disable the start screen
					GameStart = false;
				}
			}
			else
			{
				// Pass event to input objects

				OurLevel.Input(gameEvent);
				score = OurLevel.GetScore();
				scoreText.setString("Score: " + std::to_string(score));

				// Did the player try to close the window?
				if (gameEvent.type == sf::Event::Closed)
				{
					// If so, call the close function on the window.
					gameWindow.close();
				}
			}
		} // End event polling loop

		// -----------------------------------------------
		// Update Section
		// -----------------------------------------------
		// Get the time passed since the last frame and restart our game clock
		sf::Time FrameTime = gameClock.restart();

		//pass update to level
		OurLevel.Update(FrameTime);

		// -----------------------------------------------
		// Draw Section
		// -----------------------------------------------

		// Clear the window to a single colour
		gameWindow.clear(sf::Color::Black);

		//check if the game has just started
		if (GameStart)
		{
			//draw the start screen picture
			Start.Draw(gameWindow);
			gameWindow.draw(titleText);
			gameWindow.draw(NoteText);
		}
		else
		{
			gameWindow.draw(scoreText);
			//pass Display to level
			OurLevel.Draw(gameWindow);
		}
		// Display the window contents on the screen
		gameWindow.display();

	} // End of Game Loop
	return 0;

} // End of main() Function