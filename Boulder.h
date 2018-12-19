#pragma once

//project includes
#include "GridObject.h"

class Boulder : public GridObject
{

public:
	Boulder();

	bool AttemptPush(sf::Vector2i _direction);
	//overriding method
	void Update(sf::Time _FrameTime);

private:

	bool AttemptFall(sf::Vector2i _Direction);

	//data
private:
	sf::Sound m_PushSound;
};