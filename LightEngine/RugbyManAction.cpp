#include "RugbyManAction.h"
#include "GameManager.h"
#include "Field.h"
#include "Utils.h"

void RugbyManAction_EnemyGotBall::Update(RugbyMan* rugbyman)
{
	if (mTarget == nullptr)
		mTarget = dynamic_cast<Field*>(rugbyman->GetScene())->mBallOwner;
	AABB playerLane = dynamic_cast<Field*>(rugbyman->GetScene())->mLanes[rugbyman->GetLane()];

	rugbyman->GoToPosition(mTarget->GetPosition().x, mTarget->GetPosition().y);
}
/// RAPH (haut) Flav (bas)

void RugbyManAction_WithoutBall::Start(RugbyMan* rugbyman)
{
	//Se rapproche du joueur qui a la ball tout en respectant +/- sa range sans jamais le d�pacer
}

void RugbyManAction_WithoutBall::Update(RugbyMan* rugbyman)
{
	/////Cherche a se d�marquer
}

void RugbyManAction_WithoutBall::End(RugbyMan* rugbyman)
{
	//transi
}


void RugbyManAction_PossessBall::Start(RugbyMan* rugbyman)
{
	float newSpeed = rugbyman->GetSpeed() * mSpeedMultiplicator;
	rugbyman->SetSpeed(newSpeed);
	mIsImmune = true;
	mCanPass = false;

	Field* pScene = rugbyman->GetScene<Field>();
	pScene->mBallOwner = rugbyman;
}

void RugbyManAction_PossessBall::Update(RugbyMan* rugbyman)
{
	mImmuneTimer += GameManager::Get()->GetDeltaTime();
	mPassCooldownTimer += GameManager::Get()->GetDeltaTime();
	mAccelerationTimer += GameManager::Get()->GetDeltaTime();

	if (mImmuneTimer < rugbyman->mImmuneTimeAfterCatch)
		mIsImmune = false;
	if (mPassCooldownTimer < rugbyman->mPassCooldownAfterCatch)
		mCanPass = true;
	if (mPassCooldownTimer < rugbyman->mPassCooldownAfterCatch)
		rugbyman->SetSpeed(rugbyman->GetSpeed());

	if (mCanPass){

	}
	/////cherche a marqu� et si il est marqu�, fait une passe au gadji le plus close
}

void RugbyManAction_PossessBall::End(RugbyMan* rugbyman)
{
	//transi
}