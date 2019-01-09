#pragma once

//library includes
#include <SFML/Graphics.hpp>

//project includes
#include "GridObject.h"
#include "ResetButton.h"
#include "ScoreText.h"

class Level
{

public:
	Level();

	void Draw(sf::RenderTarget& _Target);
	void Update(sf::Time _FrameTime);
	void GridUpdate();
	void Input(sf::Event _GameEvent);

	//set window size from main
	void SetWindowSize(sf::Vector2u _WindowSize);

	//control levels
	void LoadLevel(int _LevelToLoad);
	void ReloadLevel();
	void ResetLevel();

	//set up and control grid objects
	float GetCellSize();
	bool MoveObjectTo(GridObject* _ToMove, sf::Vector2i _TargetPos);
	bool DeleteObject(GridObject* _Todelete);
	std::vector<GridObject* > GetObjectAt(sf::Vector2i _TargetPos);

	//control level progression
	bool CheckComplete();
	bool LevelComplete();

	//tell the Exit if the door is open or not
	bool GetDoorOpen();

	//update the player score
	void SetScore();

private:
	//private data
	const float m_CellSize;
	int m_CurrentLevel;
	int m_PendingLevel;
	std::vector< std::vector < sf::Sprite > > m_Background;
	std::vector< std::vector < std::vector< GridObject* > > > m_Contents;
	bool m_DoorOpen;
	int m_Score;
	bool m_PlayerDead;
	ResetButton m_ResetButton;
	ScoreText m_ScoreText;
	sf::Sound m_WinSound;
	sf::Sound m_DeathSound;
};