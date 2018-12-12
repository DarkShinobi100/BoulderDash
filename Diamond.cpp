//project inlcude
#include "Diamond.h"
#include "Framework/AssetManager.h"

Diamond::Diamond()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/diamond.png"));
}