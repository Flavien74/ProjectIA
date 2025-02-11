#include "Scene.h"
#include <vector>
#include <stdio.h>
#pragma once

class RugbyMan;
class RugbyDebug;

struct AABB
{
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};

class Field : public Scene
{
public:
	enum Tag
	{
		TEAMBLUE,
		TEAMRED,
		BALL
	};
	RugbyDebug* rugbyDebug;

	AABB mLanes[3];
	float mTouchdownLines[2];

	RugbyMan* mBallOwner;
	class Ball* mBall;

	int ScoreBlue = 0;
	int ScoreRed = 0;

	std::vector<RugbyMan*> mAllRugbyMan;

	std::vector<sf::Vector2i> mSpawns
	{
		{ 50, 50 },
		{ 200, 100 },
		{ 320, 360 },
		{ 200, 620 },
		{ 50, 670 },
		{ 1230, 50 },
		{ 1080, 100 },
		{ 960, 360 },
		{ 1080, 620 },
		{ 1230, 670 },
	};

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void ChangeBallOwner(RugbyMan*);
	void IsPlayerScoring(RugbyMan*);
	void Reset();
	void GiveTheBallRandom(int, int);
};