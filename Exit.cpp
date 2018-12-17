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
	//if (m_Player != nullptr)
	//{

	//}
	//else
	//{
	//	std::cout << "no pointer to player";
	//}
}

void Exit::Collide(GameObject& _Collider)
{
	// Only do something if the thing we touched was the player

	Player* CastPlayer = dynamic_cast<Player*>(&_Collider);

	// Only do the thing if player is not NULL
	if (CastPlayer != nullptr)
	{
		// we were touched by the player

		
	}
}

void Exit::SetPlayer(Player* _Player)
{
	m_Player = _Player;
}