#include "Entity.h"
#pragma once

class RugbyMan : public Entity
{
private:
	float mStrength;
	float mSprintStrength;

	float mPassCooldownAfterCatch;
	float mImmuneTimeAfterCatch;

	float mDetectionRange;

	std::string mName;

	int mLane;
	int mSpawnIndex;

	bool mHaveBall;

public:
	float GetStrength() const { return mStrength; }
	float GetSprintStrength() const { return mSprintStrength; }
	float GetSpeed() const { return mSpeed; }
	float GetDetectionRange() const { return mDetectionRange; }
	bool HaveBall() { return mHaveBall; }
	std::string GetName() const { return mName; }

	RugbyMan();
	void PassBall(RugbyMan* to);
	void OnStart(int tag, int spawnIndex, bool);

	void ReceiveBall();
	void LooseBall() { mHaveBall = false; }

protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
	void GiveTheBall(RugbyMan* pCollidedWith);
};