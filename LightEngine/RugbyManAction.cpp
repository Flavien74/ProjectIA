#include "RugbyManAction.h"
#include "GameManager.h"
#include "Field.h"
#include "Utils.h"

void RugbyManAction_EnemyGotBall::Update(RugbyMan* rugbyman)
{
	if (mTarget == nullptr)
		mTarget = dynamic_cast<Field*>(rugbyman->GetScene())->mBallOwner;

	rugbyman->GoToPosition(mTarget->GetPosition().x, mTarget->GetPosition().y);
}
/// RAPH (haut) Flav (bas)

void RugbyManAction_WithoutBall::Start(RugbyMan* rugbyman)
{
}

void RugbyManAction_WithoutBall::Update(RugbyMan* rugbyman)
{
	mBallOwner = dynamic_cast<Field*>(rugbyman->GetScene())->mBallOwner;
	sf::Vector2f direction = mBallOwner->GetPosition() - rugbyman->GetPosition();

	Utils::Normalize(direction);

	direction *= Utils::GetDistance(mBallOwner->GetPosition().x, mBallOwner->GetPosition().y, rugbyman->GetPosition().x, rugbyman->GetPosition().y) - mBallOwner->GetAlliesDetectionRange() * .75f;
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

	for (RugbyMan* toDodge : dynamic_cast<Field*>(rugbyman->GetScene())->mAllRugbyMan)
	{
		if (toDodge->GetTag() == rugbyman->GetTag()) continue;

		if (Utils::GetDistance(rugbyman->GetPosition().x, rugbyman->GetPosition().y,
			toDodge->GetPosition().x, toDodge->GetPosition().y) <= rugbyman->GetEnemiesDetectionRange())
			continue;
		
		if (!mCanPass) 
			continue;

		for (RugbyMan* toPass : dynamic_cast<Field*>(rugbyman->GetScene())->mAllRugbyMan)
		{
			if (toPass->GetTag() != rugbyman->GetTag()) continue;

			if (Utils::GetDistance(rugbyman->GetPosition().x, rugbyman->GetPosition().y,
				toPass->GetPosition().x, toPass->GetPosition().y) <= rugbyman->GetAlliesDetectionRange())
				continue;

			rugbyman->PassBall(toPass);
		}
	}

	int dir = (rugbyman->IsTag(Field::TEAMBLUE)) ? 1 : -1;
	rugbyman->GoToDirection(dir, 0);

	/////cherche a marqu� et si il est marqu�, fait une passe au gadji le plus close
}

void RugbyManAction_PossessBall::End(RugbyMan* rugbyman)
{
	//transi
}