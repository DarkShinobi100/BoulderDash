//project inlcude
#include "Mud.h"
#include "Framework/AssetManager.h"

Mud::Mud()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/mud.png"));
	m_BlocksMovement = true;
}