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
	void PassBall(RugbyMan* from, RugbyMan* to);

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

	std::vector<std::pair<Tag, int>> mScores = { {TEAMBLUE,0} ,{TEAMRED,0} };
	std::vector<RugbyMan*> mAllRugbyMan;

	std::vector<sf::Vector2i> mSpawns;


	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void ChangeBallOwner(RugbyMan*);
};