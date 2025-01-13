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
	enum Tag
	{
		TEAMBLUE,
		TEAMRED,
		BALL
	};

	AABB mLanes[3];
	float mTouchdownLines[2];

	RugbyMan* mBallOwner;

	std::vector<int, int> mSpawns;

	std::vector<Tag, int> mScores;
};