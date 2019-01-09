//project inlcude
#include "Boulder.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Mud.h"
#include "Player.h"
#include "Diamond.h"

Boulder::Boulder()
	: GridObject()
	, m_PushSound()
	, m_SkipMove(false)
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/boulder.png"));
	m_BlocksMovement = true;
	m_PushSound.setBuffer(AssetManager::GetSoundBuffer("audio/push.wav"));
}

bool Boulder::AttemptPush(sf::Vector2i _direction)
{
	//attempt to move the boulder in the given direction

	//get the current position
	//calculate the target position
	sf::Vector2i TargetPos = m_GridPosition + _direction;

	// check if the space is empty
	// get list of  objects in our target position
	std::vector<GridObject*> TargetCellContents = m_Level->GetObjectAt(TargetPos);

	// check if any of those objects block movement
	bool blocked = false;
	GridObject* blocker = nullptr;
	for (int i = 0; i < TargetCellContents.size(); ++i)
	{
		if (TargetCellContents[i]->GetBlockedMovement() == true)
		{
			blocked = true;
			blocker = TargetCellContents[i];
		}
	}

	//if empty, move there
	if (blocked == false)
	{
		//play sound effect
		m_PushSound.play();
		//move to free space
		return m_Level->MoveObjectTo(this, TargetPos);
	}
	return false;	
}

void Boulder::GridUpdate()
{
	if (ClearUnder(sf::Vector2i(0, 1)))
	{
		//if skip move is true check this
		if (m_SkipMove)
		{
			//Call the AttemptFall function
			//move in that direction
			bool MoveSuccessful = AttemptFall(sf::Vector2i(0, 1));
			m_SkipMove = false;
		}
		else
		{
			//else skip move
			m_SkipMove = true;
		}

	}

}
bool Boulder::ClearUnder(sf::Vector2i _Direction)
{
	// Attempt to move in the given direction

	//get the current position
	//calculate the target position
	sf::Vector2i TargetPos = m_GridPosition + _Direction;

	// check if the space is empty
	// get list of  objects in our target position
	std::vector<GridObject*> TargetCellContents = m_Level->GetObjectAt(TargetPos);

	// check if any of those objects block movement
	bool blocked = false;
	GridObject* blocker = nullptr;
	for (int i = 0; i < TargetCellContents.size(); ++i)
	{
		if (TargetCellContents[i]->GetBlockedMovement() == true)
		{
			blocked = true;
			blocker = TargetCellContents[i];
		}
	}
	//if empty, move there
	if (blocked == false)
	{
		return true;
	}
	else
	{
		//is it a player?
		Player* player = dynamic_cast<Player*>(blocker);
		// OR is it a Boulder?
		Boulder* boulder = dynamic_cast<Boulder*>(blocker);
		//OR is it a diamond?
		Diamond* gem = dynamic_cast<Diamond*>(blocker);

		//if so(the thing is one of these(not nullptr))
		if (player != nullptr || boulder != nullptr || gem != nullptr)
		{	
						return true;
		}
		//if movement is blocked, do nothing, return false
		return false;
	}

}


bool Boulder::AttemptFall(sf::Vector2i _Direction)
{
	// Attempt to move in the given direction

	//get the current position
	//calculate the target position
	sf::Vector2i TargetPos = m_GridPosition + _Direction;

	// check if the space is empty
	// get list of  objects in our target position
	std::vector<GridObject*> TargetCellContents = m_Level->GetObjectAt(TargetPos);

	// check if any of those objects block movement
	bool blocked = false;
	GridObject* blocker = nullptr;
	for (int i = 0; i < TargetCellContents.size(); ++i)
	{
		if (TargetCellContents[i]->GetBlockedMovement() == true)
		{
			blocked = true;
			blocker = TargetCellContents[i];
		}
	}

	//if empty, move there
	if (blocked == false)
	{
		return m_Level->MoveObjectTo(this, TargetPos);
	}
	else
	{
		//is it a player?
		Player* player = dynamic_cast<Player*>(blocker);

		//if so(the thing is a player(not nullptr))
		if (player != nullptr)
		{	
			//is the boulder moving right
			if (_Direction == sf::Vector2i(1, 1))
			{//don't slide into the player
				return false;
			}
			//are we moving left
			if (_Direction == sf::Vector2i(-1, 1))
			{//don't slide into the player
				return false;
			}
			
			//touched player so they die
			//display reset button
			m_Level->ResetLevel();
			return m_Level->MoveObjectTo(this, TargetPos);
		}

		//is it a boulder?
		Boulder* boulder = dynamic_cast<Boulder*>(blocker);
		//is it a Diamond?
		Diamond* gem = dynamic_cast<Diamond*>(blocker);

		//if so(the thing is a obstacle(not nullptr))
		if (boulder != nullptr || gem != nullptr)
		{
			//if diretion is down
			if (_Direction == sf::Vector2i(0, 1))
			{
			//try and move right
			AttemptFall(sf::Vector2i(1, 1));
			}

			else if (_Direction == sf::Vector2i(1, 1))
			{
				//else if direction is Right
				//go left
				AttemptFall(sf::Vector2i(-1, 1));
			}
			else
			{
				//do nothing stop trying to move
				return false;
			}

		}
	}
		//we were blocked!
	//if movement is blocked, do nothing, return false
	return false;
}