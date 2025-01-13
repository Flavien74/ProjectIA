#include "Entity.h"
#pragma once

class RugbyMan : Entity
{
private:
	float mStrength;
	float mSprintStrength;

	float mPassCooldownAfterCatch;
	float mImmuneTimeAfterCatch;

	int mLane;
	int mSpawnIndex;
};

