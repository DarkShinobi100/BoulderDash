#pragma once

//project includes
#include "Framework/TextObject.h"

class ScoreText : public TextObject
{

public:
	ScoreText();
	void PositionOnScreen(float width, float height);
	void UpdateScore(int _score);
};
