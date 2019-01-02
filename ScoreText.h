#pragma once

//project includes
#include "Framework/TextObject.h"

class ScoreText : public TextObject
{

public:
	ScoreText();
	void ScaleToFit(float width);
	void UpdateScore(int _score);
};
