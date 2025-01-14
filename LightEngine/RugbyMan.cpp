#include "RugbyMan.h"
#include "Field.h"
#include <iostream>

RugbyMan::RugbyMan() :
	mStrength(10), mSprintStrength(10), mPassCooldownAfterCatch(1), mImmuneTimeAfterCatch(0.5), mName("Jake")
{
	mRigidBody = true;
}

void RugbyMan::OnStart(int tag, int spawnIndex, bool isBallMine)
{
	//mLane = lane;
	mHaveBall = isBallMine;
	mSpawnIndex = spawnIndex;
	SetTag(tag);
	if (IsTag(Field::Tag::TEAMBLUE)) {
		SetDirection(1, 0, 50);
	}
	else {
		SetDirection(-1, 0, 50);
	}
}

void RugbyMan::OnUpdate()
{

}

void RugbyMan::OnCollision(Entity* pCollidedWith)
{
	if (pCollidedWith->IsTag(Field::Tag::BALL)) {
		ReceiveBall();
	}
	if (mHaveBall && !pCollidedWith->IsTag(mTag)) {
		RugbyMan* pRugbyMan = dynamic_cast<RugbyMan*>(pCollidedWith);
		GiveTheBall(pRugbyMan);
	}
}

void RugbyMan::GiveTheBall(RugbyMan* pCollidedWith)
{
	mHaveBall = false;
	pCollidedWith->ReceiveBall();
	std::cout << "I gave the ball" << std::endl;
}

void RugbyMan::ReceiveBall()
{
	std::cout << "I have the ball" << std::endl;
	mHaveBall = true;
}
