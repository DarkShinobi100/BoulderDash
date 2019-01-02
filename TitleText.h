#pragma once

//project includes
#include "Framework/TextObject.h"

class TitleText : public TextObject
{

public:
	TitleText();
	void ScaleToFit(float width);
};