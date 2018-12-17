//project inlcude
#include "Boulder.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Mud.h"

Boulder::Boulder()
	: GridObject()
	, m_PushSound()
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
		return m_Level->MoveObjectTo(this, TargetPos);
	}
	else
	{
		//if movement is blocked, do nothing, return false
		return false;
	}
}