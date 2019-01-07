#pragma once

//project includes
#include "Framework/TextObject.h"

class StartText : public TextObject
{

public:
	StartText();
	void ScaleToFit(float width, float height);
};
