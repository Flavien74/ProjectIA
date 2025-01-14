#include "Entity.h"
#pragma once

class RugbyMan : public Entity
{
private:
	float mStrength;
	float mSprintStrength;

	float mPassCooldownAfterCatch;
	float mImmuneTimeAfterCatch;

	std::string mName;

	int mLane;
	int mSpawnIndex;

	bool mHaveBall;

public:
	float GetStrength() const { return mStrength; }
	float GetSprintStrength() const { return mSprintStrength; }
	float GetSpeed() const { return mSpeed; }
	std::string GetName() const { return mName; }

	RugbyMan();
	void OnStart(int tag, int spawnIndex);

	void ReceiveBall();

protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
	void GiveTheBall(RugbyMan* pCollidedWith);
};