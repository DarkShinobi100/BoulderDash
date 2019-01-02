#pragma once

//project includes
#include "GridObject.h"

class ResetButton : public GridObject
{

public:
	ResetButton();
	void PositionOnScreen(float width);

	//function for when clicked run reset level
	void OnClicked();
}; 
