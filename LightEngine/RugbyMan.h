#include "Entity.h"
#pragma once

class RugbyMan : public Entity
{
private:
	float mStrength;
	float mSprintStrength;

	float mPassCooldownAfterCatch;
	float mImmuneTimeAfterCatch;

	int mLane;
	int mSpawnIndex;

	bool mHaveBall;

public:
	float GetStrength() const { return mStrength; }
	float GetSprintStrength() const { return mSprintStrength; }
	float GetSpeed() const { return mSpeed; }


};

