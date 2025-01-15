#include "RugbyManAction.h"
#include "GameManager.h"
#include "Field.h"
#include "Utils.h"


/// RAPH (haut) Flav (bas)

void RugbyManAction_WithoutBall::Start(RugbyMan* rugbyman)
{
	sf::Vector2f baseDir = rugbyman->GetDirection();
	float baseSpeed = rugbyman->GetSpeed();
	rugbyman->SetDirection(baseDir.x, baseDir.y, baseSpeed);
	//Se rapproche du joueur qui a la ball tout en respectant +/- sa range sans jamais le dépacer
}

void RugbyManAction_WithoutBall::Update(RugbyMan* rugbyman)
{
	/////Cherche a se démarquer
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
	/////cherche a marqué et si il est marqué, fait une passe au gadji le plus close
}

void RugbyManAction_PossessBall::End(RugbyMan* rugbyman)
{
	//transi
}