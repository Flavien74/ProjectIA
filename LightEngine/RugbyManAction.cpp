#include "RugbyManAction.h"
#include "GameManager.h"
#include "iostream"
#include "Field.h"
#include "Utils.h"

void RugbyManAction_EnemyGotBall::Update(RugbyMan* rugbyman)
{
	mTarget = rugbyman->GetScene<Field>()->mBallOwner;

	if (mTarget == nullptr)
		return;

	rugbyman->GoToPosition(mTarget->GetPosition().x, mTarget->GetPosition().y);
}

void RugbyManAction_WithoutBall::Update(RugbyMan* rugbyman)
{
	mBallOwner = rugbyman->GetScene<Field>()->mBallOwner;
	int dir = (rugbyman->IsTag(Field::TEAMBLUE)) ? 1 : -1;
	rugbyman->SetDirection(dir, 0);
	return;
}

void RugbyManAction_PossessBall::Start(RugbyMan* rugbyman)
{
	float newSpeed = rugbyman->GetSpeed() * mSpeedMultiplicator;
	rugbyman->SetSpeed(newSpeed);
	rugbyman->mCanPass = false;
	Field* pScene = rugbyman->GetScene<Field>();
	pScene->mBallOwner = rugbyman;

	mImmuneTimer = 0;
	mPassCooldownTimer = 0;
	mAccelerationTimer = 0;
}

void RugbyManAction_PossessBall::Update(RugbyMan* rugbyman)
{
	mImmuneTimer += GameManager::Get()->GetDeltaTime();
	mPassCooldownTimer += GameManager::Get()->GetDeltaTime();
	mAccelerationTimer += GameManager::Get()->GetDeltaTime();

	if (mImmuneTimer > rugbyman->mImmuneTimeAfterCatch)
		rugbyman->SetImmune(false);
	if (mPassCooldownTimer > rugbyman->mPassCooldownAfterCatch)
		rugbyman->mCanPass = true;
	if (mPassCooldownTimer > rugbyman->mPassCooldownAfterCatch)
		rugbyman->SetSpeed(rugbyman->mDefaultSpeed);

	for (RugbyMan* toDodge : rugbyman->GetScene<Field>()->mAllRugbyMan)
	{
		if (toDodge->GetTag() == rugbyman->GetTag()) continue;


		float dist = Utils::GetDistance(rugbyman->GetPosition().x, rugbyman->GetPosition().y, toDodge->GetPosition().x, toDodge->GetPosition().y);

		if (dist > rugbyman->GetEnemiesDetectionRange()) continue;


		if (!rugbyman->mCanPass) continue;


		for (RugbyMan* toPass : rugbyman->GetScene<Field>()->mAllRugbyMan)
		{
			if (toPass->GetTag() != rugbyman->GetTag()) continue;

			if (rugbyman->GetTag() == Field::TEAMBLUE)
			{
				if (toPass->GetPosition().x > rugbyman->GetPosition().x) continue;
			}
			else
			{
				if (toPass->GetPosition().x < rugbyman->GetPosition().x) continue;

			}
			float dist = Utils::GetDistance(rugbyman->GetPosition().x, rugbyman->GetPosition().y, toPass->GetPosition().x, toPass->GetPosition().y);
			if (dist > rugbyman->GetAlliesDetectionRange())	continue;

			rugbyman->PassBall(toPass);
		}
	}

	int dir = (rugbyman->IsTag(Field::TEAMBLUE)) ? 1 : -1;
	rugbyman->SetDirection(dir, 0);

	/////cherche a marqu� et si il est marqu�, fait une passe au gadji le plus close
}

void RugbyManAction_PossessBall::End(RugbyMan* rugbyman)
{
	rugbyman->SetImmune(false);
	rugbyman->mCanPass = true;
	rugbyman->SetSpeed(rugbyman->GetSpeed());
}