#pragma once

//project includes
#include "GridObject.h"
#include "Level.h"

class Exit : public GridObject
{
public:
	Exit();

	//Overridding methods
	void Update(sf::Time _FrameTime);
};