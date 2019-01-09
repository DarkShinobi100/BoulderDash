#pragma once

//project includes
#include "GridObject.h"

class Startscreen : public GridObject
{
	//functions
public:
	Startscreen();
	void ScaleToFit(float width,float height);
	void StartMusic();

	//private data
private:
	sf::Sound m_BGM;
};