#pragma once

//project includes
#include "GridObject.h"

class Diamond : public GridObject
{

public:
	Diamond();
	//overriding method
	void GridUpdate();
	bool ClearUnder(sf::Vector2i _Direction);

private:

	bool AttemptFall(sf::Vector2i _Direction);

	//data keep private
private:
	bool m_SkipMove;
};