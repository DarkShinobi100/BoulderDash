//project includes
#include "Level.h"
#include "Framework/AssetManager.h"
#include "Wall.h"
#include "Player.h"
#include "Mud.h"
#include "Diamond.h"
#include "Boulder.h"
#include "Exit.h"
#include "ResetButton.h"

//library includes
#include <iostream>
#include <fstream>

Level::Level()
	:m_CellSize(64.0f)
	,m_BGM()
	,m_CurrentLevel(0)
	,m_PendingLevel(0)
	,m_Background()
	,m_Contents()
	,m_DoorOpen(false)
	,m_Score(0)
{
	m_BGM.setBuffer(AssetManager::GetSoundBuffer("audio/BGM.ogg"));
	m_BGM.setLoop(true);
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget& _Target)
{
	//create and update camera
	sf::View Camera = _Target.getDefaultView();

	//adjust camera as needed
	Camera.setCenter(m_Background[0].size()* m_CellSize/2 ,m_Background.size()*m_CellSize/2);

	// Draw game world to the window
	_Target.setView(Camera);

	// TODO Draw game objects
	for (int y = 0; y < m_Background.size(); ++y)
	{
		for (int x = 0; x < m_Background[y].size(); ++x)
		{
			_Target.draw(m_Background[y][x]);
		}
	}

	//draw grid objects
	//Y = rows
	for (int y = 0; y < m_Contents.size(); ++y)
	{
		//X = Cells
		for (int x = 0; x < m_Contents[y].size(); ++x)
		{
			//Z = stickoutty(GridObjects)
			for (int z = 0; z < m_Contents[y][x].size(); ++z)
			{
				m_Contents[y][x][z]->Draw(_Target);
			}
		}
	}

	//TODO Adjust camera as needed

	// Reset view
	_Target.setView(_Target.getDefaultView());

}


void Level::Update(sf::Time _FrameTime)
{
	//Y = rows
	for (int y = 0; y < m_Contents.size(); ++y)
	{
		//X = Cells
		for (int x = 0; x < m_Contents[y].size(); ++x)
		{
			//Z = stickoutty(GridObjects)
			for (int z = 0; z < m_Contents[y][x].size(); ++z)
			{
				m_Contents[y][x][z]->Update(_FrameTime);
			}
		}
	}
	//load the next level if there is a pending level
	if (m_PendingLevel != 0)
	{
		//load it
		LoadLevel(m_PendingLevel);
		//remove pending level
		m_PendingLevel = 0;
	}
}

void Level::GridUpdate()
{
	//Y = rows
	//count from bottom to top of the screen so gravity works!
	for (int y = m_Contents.size()-1; y >= 0; --y)
	{
		//X = Cells
		for (int x = 0; x < m_Contents[y].size(); ++x)
		{
			//Z = stickoutty(GridObjects)
			for (int z = 0; z < m_Contents[y][x].size(); ++z)
			{
				//call grid update on the kids
				m_Contents[y][x][z]->GridUpdate();
			}
		}
	}
}


void Level::Input(sf::Event _GameEvent)
{
	//Y = rows
	for (int y = 0; y < m_Contents.size(); ++y)
	{
		//X = Cells
		for (int x = 0; x < m_Contents[y].size(); ++x)
		{
			//Z = stickoutty(GridObjects)
			for (int z = 0; z < m_Contents[y][x].size(); ++z)
			{
				m_Contents[y][x][z]->Input(_GameEvent);
			}
		}
	}
}

void Level::LoadLevel(int _LevelToLoad)
{
	//Clean up the old level

	//Delete any data already in the level
	
	//Y = rows
	for (int y = 0; y < m_Contents.size(); ++y)
	{
		//X = Cells
		for (int x = 0; x < m_Contents[y].size(); ++x)
		{
			//Z = stickoutty(GridObjects)
			for (int z = 0; z < m_Contents[y][x].size(); ++z)
			{
				delete m_Contents[y][x][z];
			}
		}
	}
	
	//clear out our lists
	m_Background.clear();
	m_Contents.clear();

	//set the current level
	m_CurrentLevel = _LevelToLoad;


	if (m_CurrentLevel == 1)
	{

		//start music
		m_BGM.play();
	}

	//-=Set up the new level=-

	// Open our file for reading
	std::ifstream inFile;
	std::string fileName = "levels/Level" + std::to_string(m_CurrentLevel) + ".txt";
	inFile.open(fileName);

	// make sure the file was opened
	if (!inFile)
	{
		std::cerr << "Unable to open file " + fileName;
		exit(1); // call system to stop program with error

	}

	// set the starting x and y coordinates used to position level objects in our new grid system
	int x = 0.0f;
	int y = 0.0f;

	//Create the first row in our grid
	m_Background.push_back(std::vector<sf::Sprite>());
	m_Contents.push_back(std::vector< std::vector<GridObject*> >());

	// read each character one by one from the file...
	char ch;
	//each time try to read the next character
	//if successful, execute body of loop
	//the "noskipws" means our input from the fill will include
	// the white space(spaces and new lines)

	while (inFile>> std::noskipws >> ch)
	{
		//perform actions based on what character was read in
		if (ch == ' ')
		{
			x += 1;
		}
		else if (ch == '\n')
		{
			++y;
			x = 0;


			//Create a new row in our grid
			m_Background.push_back(std::vector<sf::Sprite>());
			m_Contents.push_back(std::vector< std::vector<GridObject*> >());
		}
		else
		{
			//this is going to be some object(or empty space),so we need a background
			//create background sprite
			m_Background[y].push_back(sf::Sprite(AssetManager::GetTexture("graphics/ground.png")));
			m_Background[y][x].setPosition(x * m_CellSize, y * m_CellSize);

			//create an empty vector for our grid contents in this cell
			m_Contents[y].push_back(std::vector<GridObject*>());

			 if (ch == '-')
			{
				// do nothing - empty space
			}
			 else if (ch =='W')
			 {
				 //if it is a wall
				 Wall* wall = new Wall();
				 wall->SetLevel(this);
				 wall->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(wall);

			 }
			 else if (ch == 'M')
			 {
				 //if it is some mud
				 Mud* mud = new Mud();
				 mud->SetLevel(this);
				 mud->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(mud);

			 }
			 else if (ch == 'D')
			 {
				 //if it is a diamond
				 Diamond* diamond = new Diamond();
				 diamond->SetLevel(this);
				 diamond->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(diamond);

			 }
			 else if (ch == 'B')
			 {
				 //if it is a boulder
				 Boulder* boulder = new Boulder();
				 boulder->SetLevel(this);
				 boulder->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(boulder);

			 }
			 else if (ch == 'E')
			 {
				 //if it is a Exit
				 Exit* exit = new Exit();
				 exit->SetLevel(this);
				 exit->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(exit);

			 }

			 else if (ch == 'P')
			 {
				 //if it is a Player
				 Player* player = new Player();
				 player->SetLevel(this);
				 player->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(player);

			 }
			else
			{
				std::cerr << "unrecognised character in level file: " << ch;
			}
		}
	}

	//close the file now that were done with it
	inFile.close();
	}

void Level::ReloadLevel()
{
	//set pending level to the current one when we want to reset on death
	m_PendingLevel = m_CurrentLevel;
	m_Score = 0;
}

void Level::ResetLevel() 
{
//TODO when player has died display reset button
}

void Level::LoadNextLevel()
{
	LoadLevel(m_CurrentLevel + 1);
}

float Level::GetCellSize()
{
	return m_CellSize;
}

bool Level::MoveObjectTo(GridObject* _ToMove, sf::Vector2i _TargetPos)
{
	//don't trust other code make sure _ToMove is a valid pointer 
	//also check our target position is within the grid
	if (_ToMove != nullptr
		&& _TargetPos.y >= 0 && _TargetPos.y < m_Contents.size()
		&& _TargetPos.x >= 0 && _TargetPos.x < m_Contents[_TargetPos.y].size())
	{
		//get the current position of the grid object
		sf::Vector2i OldPos = _ToMove->GetGridPosition();

		// find the object in the list
		//using an iterator and the "find" method
		auto it = std::find(m_Contents[OldPos.y][OldPos.x].begin(),
							m_Contents[OldPos.y][OldPos.x].end(),
							_ToMove);

		//if we found the object at this location,
		//it will NOT equal the end of the vector
		if (it != m_Contents[OldPos.y][OldPos.x].end())
		{
			//we found the object!

			//remove it from the old position
			m_Contents[OldPos.y][OldPos.x].erase(it);

			//add it to it's new position
			m_Contents[_TargetPos.y][_TargetPos.x].push_back(_ToMove);

			//tell the object it's new position
			_ToMove->SetGridPosition(_TargetPos);

			//return success
			return true;
		}
	}
	//return failure
	return false;
}

bool Level::DeleteObject(GridObject* _Todelete)
{
	//don't trust other code make sure _Todelete is a valid pointer 
	//also check our target position is within the grid
	if (_Todelete != nullptr)
	{
		//get the current position of the grid object
		sf::Vector2i OldPos = _Todelete->GetGridPosition();

		// find the object in the list
		//using an iterator and the "find" method
		auto it = std::find(m_Contents[OldPos.y][OldPos.x].begin(),
			m_Contents[OldPos.y][OldPos.x].end(),
			_Todelete);

		//if we found the object at this location,
		//it will NOT equal the end of the vector
		if (it != m_Contents[OldPos.y][OldPos.x].end())
		{
			//we found the object!

			//remove it from the old position
			m_Contents[OldPos.y][OldPos.x].erase(it);

			//delete the pointer
			delete _Todelete;

			//return success
			return true;
		}
	}
	//return failure
	return false;
}

std::vector<GridObject* > Level::GetObjectAt(sf::Vector2i _TargetPos)
{
	//don't trust the data
	//make sure the data is valid
	//=also make sure the coordinates are within the vector slice

	if (_TargetPos.y >= 0 && _TargetPos.y < m_Contents.size()
		&& _TargetPos.x >= 0 && _TargetPos.x < m_Contents[_TargetPos.y].size())
	{

		//get the contents
		//return them
		return m_Contents[_TargetPos.y][_TargetPos.x];

	}

	//default return
	//return an empty vector wih nothing in it
	//(Default constructor)
	return std::vector<GridObject*>();

}

bool Level::CheckComplete()
{
	//Loop through and check all diamonds to see if they are stored
	//Y = rows
	for (int y = 0; y < m_Contents.size(); ++y)
	{
		//X = Cells
		for (int x = 0; x < m_Contents[y].size(); ++x)
		{
			//Z = stickoutty(GridObjects)
			for (int z = 0; z < m_Contents[y][x].size(); ++z)
			{
				//current object in the loop we are examining
				GridObject* thisObject = m_Contents[y][x][z];

				//check if it is a Diamond via dynamic cast
				Diamond* Gem = dynamic_cast<Diamond*>(thisObject);
				if (Gem != nullptr)
				{
					//it WAS a Diamond!
					m_Score = m_Score + 5;

					//if a diamond exists
					//leave
					
					//any single Diamond being alive means the whole level is NOT complete
					return false;
			
				}

			}
		}
	}

	// all diamonds are deleted
	//so we completed the level!
	//but must touch the exit first

	// play victory music
	//m_winSound.play();

	//change Exit sprite via setting m_doorOpen to true
	m_DoorOpen = true;

	// the level is complete so return true
	return true;
}

bool Level::LevelComplete()
{
	if (m_DoorOpen)
	{
	//level complete!!
	//queue the next level to load during the next update
	//if you do it immidately, 
	//there is an access violation due to update still running
		m_PendingLevel = m_CurrentLevel + 1;
		m_DoorOpen = false;
		return true;

	}
	return false;
}

bool Level::GetDoorOpen()
{
	return m_DoorOpen;
}

int Level::GetScore()
{
	return m_Score;
}