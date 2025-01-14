#include "Scene.h"
#include <vector>
#include <stdio.h>
#include "RugbyMan.h"
#pragma once

struct AABB
{
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};

class Field : Scene
{
public:
	void PassBall(RugbyMan from, RugbyMan to);

public:
	enum Tag
	{
		TEAMBLUE,
		TEAMRED,
		BALL
	};

	AABB mLanes[3];
	float mTouchdownLines[2];

	RugbyMan* mBallOwner;

	std::vector<std::vector< int>> mSpawns = {};

	std::vector<std::pair<Tag, int>> mScores = { {TEAMBLUE,0} ,{TEAMRED,0} };
};