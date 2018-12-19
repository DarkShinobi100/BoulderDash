//Project Includes
#include "Exit.h"
#include "Framework/AssetManager.h"

#include<iostream>
Exit::Exit()
	: GridObject() //Always initialise your parent class in your constructor
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));
	m_BlocksMovement = true;

}


void Exit::Update(sf::Time _FrameTime)
{
	if (m_Level->GetDoorOpen())
	{
		m_Sprite.setTexture(AssetManager::GetTexture("graphics/DoorOpen.png"));
	}
}



//check diamonds in level
//change sprite in exit
//tell player that door is open
