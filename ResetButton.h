#pragma once

//project includes
#include "GridObject.h"

class ResetButton : public GridObject
{

public:
	ResetButton();
	void PositionOnScreen(float width, float height);

	//function for when clicked run reset level
	bool OnClicked(sf::Event _gameEvent);
}; 
