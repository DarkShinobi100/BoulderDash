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
	//attempt to move the box in the given direction

	//get the current position
	//calculate the target position
	sf::Vector2i TargetPos = m_GridPosition + _direction;

	// check if the space is empty
	// get list of  objects in our target position
	std::vector<GridObject*> TargetCellContents = m_Level->GetObjectAt(TargetPos);

	// check if any of those objects block movement
	bool blocked = false;
	for (int i = 0; i < TargetCellContents.size(); ++i)
	{
		//check if blocker is mud
		Mud* mudBlocker = dynamic_cast<Mud*>(TargetCellContents[i]);
		blocked = mudBlocker != nullptr;
		if (blocked==true)
		{
			return false;
		}

	}

	//if empty, move there
	if (blocked == false)
	{
		m_PushSound.play();
		return m_Level->MoveObjectTo(this, TargetPos);
	}
}