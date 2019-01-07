#pragma once

//project includes
#include "GridObject.h"

class Startscreen : public GridObject
{

public:
	Startscreen();
	void ScaleToFit(float width,float height);
};