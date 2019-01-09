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
#include "StartText.h"
#include "TitleText.h"
#include "ScoreText.h"
#include "ResetButton.h"

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

	//create the start screen pic and play BGM
	Startscreen Start;
	Start.ScaleToFit(gameWindow.getSize().x, gameWindow.getSize().y);
	Start.StartMusic();

	TitleText TitleText;
	TitleText.ScaleToFit(gameWindow.getSize().x);

	StartText StartText;
	StartText.ScaleToFit(gameWindow.getSize().x, gameWindow.getSize().y);

	ScoreText ScoreText;
	ScoreText.ScaleToFit(gameWindow.getSize().x);
	
	ResetButton ResetButton;
	ResetButton.PositionOnScreen(gameWindow.getSize().x, gameWindow.getSize().y);


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

				// Did the player try to close the window?
				if (gameEvent.type == sf::Event::Closed)
				{
					// If so, call the close function on the window.
					gameWindow.close();
				}
			}
			else
			{
				// Pass event to input objects

				OurLevel.Input(gameEvent);

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
			//draw the start screen picture and Text
			Start.Draw(gameWindow);
			TitleText.Draw(gameWindow);
			StartText.Draw(gameWindow);
		}
		else
		{
			//pass Display to level
			OurLevel.Draw(gameWindow);
		}
		// Display the window contents on the screen
		gameWindow.display();

	} // End of Game Loop
	return 0;

} // End of main() Function
