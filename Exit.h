#pragma once

//project includes
#include "GridObject.h"
#include "Player.h"

class Exit : public GridObject
{
public:
	Exit();

	//Overridding methods
	void Update(sf::Time _FrameTime);
	void Collide(GameObject& _Collider);
	// Public Score Methods
	void SetPlayer(Player* _Player);

private:

	Player* m_Player;

};