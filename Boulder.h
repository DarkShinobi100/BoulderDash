#pragma once

//project includes
#include "GridObject.h"

class Boulder : public GridObject
{

public:
	Boulder();

	bool AttemptPush(sf::Vector2i _direction);

private:
	sf::Sound m_PushSound;
};