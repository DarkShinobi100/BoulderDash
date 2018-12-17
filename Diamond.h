#pragma once

//project includes
#include "GridObject.h"

class Diamond : public GridObject
{

public:
	Diamond();
	//overriding method
	void Update(sf::Time _FrameTime);

private:

	bool AttemptMove(sf::Vector2i _Direction);

};