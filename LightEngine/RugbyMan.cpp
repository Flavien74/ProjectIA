#include "RugbyMan.h"
#include "Field.h"

RugbyMan::RugbyMan() :
	mStrength(10), mSprintStrength(10), mPassCooldownAfterCatch(1), mImmuneTimeAfterCatch(0.5), mName("Jake"), mLane(1), mSpawnIndex(0), mHaveBall(false)
{
}

RugbyMan::RugbyMan(int tag, int lane, int spawnIndex) :
	mStrength(10), mSprintStrength(10), mPassCooldownAfterCatch(1), mImmuneTimeAfterCatch(0.5), mName("Jake"), mLane(lane),mSpawnIndex(spawnIndex),mHaveBall(false)
{
	SetTag(tag);
	if (IsTag(Field::Tag::TEAMBLUE)) {
		SetDirection(0, 1);
	}
	else {
		SetDirection(0, -1);
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
}

void RugbyMan::ReceiveBall()
{
	mHaveBall = true;
}
