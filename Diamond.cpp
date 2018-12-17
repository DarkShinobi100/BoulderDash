//project inlcude
#include "Diamond.h"
#include "Framework/AssetManager.h"
#include "Level.h"

Diamond::Diamond()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/diamond.png"));
	m_BlocksMovement = true;
}
void Diamond::Update(sf::Time _FrameTime)
{

	//move in that direction
	bool MoveSuccessful = AttemptMove(sf::Vector2i(0, 1));
}

bool Diamond::AttemptMove(sf::Vector2i _Direction)
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
	for (int i = 0; i < TargetCellContents.size(); ++i)
	{
		if (TargetCellContents[i]->GetBlockedMovement() == true)
		{
			blocked = true;
		}
	}

	//if empty, move there
	if (blocked == false)
	{
		return m_Level->MoveObjectTo(this, TargetPos);
	}
	//we were blocked!
	//if movement is blocked, do nothing, return false
	return false;
}