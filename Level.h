#pragma once

//library includes
#include <SFML/Graphics.hpp>

//project includes
#include "GridObject.h"

class Level
{

public:
	Level();

	void Draw(sf::RenderTarget& _Target);
	void Update(sf::Time _FrameTime);
	void GridUpdate();
	void Input(sf::Event _GameEvent);

	void LoadLevel(int _LevelToLoad);
	void ReloadLevel();
	void ResetLevel();
	void LoadNextLevel();

	float GetCellSize();
	bool MoveObjectTo(GridObject* _ToMove, sf::Vector2i _TargetPos);
	bool DeleteObject(GridObject* _Todelete);
	std::vector<GridObject* > GetObjectAt(sf::Vector2i _TargetPos);

	bool CheckComplete();
	bool LevelComplete();

	bool GetDoorOpen();
	void SetScore();
	int GetScore();

private:

	const float m_CellSize;
	int m_CurrentLevel;
	int m_PendingLevel;
	std::vector< std::vector < sf::Sprite > > m_Background;
	std::vector< std::vector < std::vector< GridObject* > > > m_Contents;
	bool m_DoorOpen;
	int m_Score;
	bool m_PlayerDead;
	
};