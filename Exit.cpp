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
{//check the m_DoorOpen value in level
	if (m_Level->GetDoorOpen())
	{//if it = true, change sprite
		m_Sprite.setTexture(AssetManager::GetTexture("graphics/DoorOpen.png"));
	}
//else do nothing
}

