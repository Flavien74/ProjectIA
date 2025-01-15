#pragma once

#include "Action.h"
#include "RugbyMan.h"

class RugbyManAction_EnemyGotBall : public Action <RugbyMan>
{
public:
	void Start(RugbyMan* rugbyman) override {}
	void Update(RugbyMan* rugbyman) override;
	void End(RugbyMan* rugbyman) override {}
private:
	RugbyMan* mTarget = nullptr;
};

class RugbyManAction_WithoutBall : public Action <RugbyMan>
{
public:
	void Start(RugbyMan* rugbyman) override;
	void Update(RugbyMan* rugbyman) override;
	void End(RugbyMan* rugbyman) override;
private:
	RugbyMan* mBallOwner = nullptr;
};

class RugbyManAction_PossessBall : public Action <RugbyMan>
{
private:
	float mImmuneTimer;
	float mPassCooldownTimer;
	float mAccelerationTimer;

	float mSpeedMultiplicator = 1.2f;

public:
	void Start(RugbyMan* rugbyman) override;
	void Update(RugbyMan* rugbyman) override;
	void End(RugbyMan* rugbyman) override;
};