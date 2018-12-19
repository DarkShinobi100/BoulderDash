//project inlcude
#include "Diamond.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Player.h"

Diamond::Diamond()
	: GridObject()
	, m_SkipMove(false)
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/diamond.png"));
	m_BlocksMovement = true;
}

void Diamond::GridUpdate()
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
bool Diamond::ClearUnder(sf::Vector2i _Direction)
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

		//if so(the thing is a player(not nullptr))
		if (player != nullptr)
		{
			return true;
		}
		//if movement is blocked, do nothing, return false
		return false;
	}
}


bool Diamond::AttemptFall(sf::Vector2i _Direction)
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
		{	//TODO increase score

			//touched player so they die
			m_Level->ReloadLevel();
			return m_Level->MoveObjectTo(this, TargetPos);
		}
		//if movement is blocked, do nothing, return false
		return false;
	}
	//we were blocked!
//if movement is blocked, do nothing, return false
	return false;
}