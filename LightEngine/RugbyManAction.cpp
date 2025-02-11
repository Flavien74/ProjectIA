#include "RugbyManAction.h"
#include "GameManager.h"
#include "Resources.h"
#include "Ball.h"
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

	if (mBallOwner != nullptr && mBallOwner->IsTag(rugbyman->GetTag()))
	{
		if (rugbyman->GetTag() == Field::TEAMBLUE)
		{
			if (mBallOwner->GetPosition().x < rugbyman->GetPosition().x + rugbyman->mShape.getRadius()) return;
		}
		else
		{
			if (mBallOwner->GetPosition().x > rugbyman->GetPosition().x - rugbyman->mShape.getRadius()) return;
		}
	}

	int dir = (rugbyman->IsTag(Field::TEAMBLUE)) ? 1 : -1;
	rugbyman->SetDirection(dir, 0);
	return;
}

void RugbyManAction_PossessBall::Update(RugbyMan* rugbyman)
{
	if (!rugbyman->HaveBall()) return;

	int dir = (rugbyman->IsTag(Field::TEAMBLUE)) ? 1 : -1;
	rugbyman->SetDirection(dir, 0);
}

void RugbyManAction_EnterPossession::Start(RugbyMan* rugbyman)
{
	float newSpeed = rugbyman->GetSpeed() * rugbyman->mSpeedMultiplicator;
	rugbyman->SetSpeed(newSpeed);
	rugbyman->mCanPass = false;
	rugbyman->SetImmune(true);

	mImmuneTimer = 0;
	mPassCooldownTimer = 0;
	mAccelerationTimer = 0;
}

void RugbyManAction_EnterPossession::Update(RugbyMan* rugbyman)
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

	int dir = (rugbyman->IsTag(Field::TEAMBLUE)) ? 1 : -1;
	rugbyman->SetDirection(dir, 0);
}

void RugbyManAction_EnterPossession::End(RugbyMan* rugbyman)
{
	rugbyman->SetImmune(false);
	rugbyman->mCanPass = true;
	rugbyman->SetSpeed(rugbyman->mDefaultSpeed);
}

void RugbyManAction_Drible::Start(RugbyMan* rugbyman)
{
	float newSpeed = rugbyman->GetSpeed() * rugbyman->mSpeedMultiplicator;
	rugbyman->SetSpeed(newSpeed);
}

void RugbyManAction_Drible::Update(RugbyMan* rugbyman)
{
	for (RugbyMan* toDodge : rugbyman->GetScene<Field>()->mAllRugbyMan)
	{
		if (toDodge->GetTag() == rugbyman->GetTag()) continue;

		float dist = Utils::GetDistance(rugbyman->GetPosition().x, rugbyman->GetPosition().y, toDodge->GetPosition().x, toDodge->GetPosition().y);

		if (dist > rugbyman->GetEnemiesDetectionRange()) continue;

		float angle = Utils::GetAngleDegree(rugbyman->GetDirection(), toDodge->GetPosition() - rugbyman->GetPosition());
		if (angle >= -rugbyman->GetEnemiesDetectionConeAngle() && rugbyman->GetEnemiesDetectionConeAngle() >= angle)
		{
			if (toDodge->GetPosition().y > rugbyman->GetPosition().y)
				rugbyman->SetDirection(rugbyman->GetDirection().x, -1, rugbyman->GetSpeed());

			else
				rugbyman->SetDirection(rugbyman->GetDirection().x, 1, rugbyman->GetSpeed());
		}
	}
}

void RugbyManAction_Drible::End(RugbyMan* rugbyman)
{
	rugbyman->SetSpeed(rugbyman->mDefaultSpeed);
}
void RugbyManAction_PassBall::Start(RugbyMan* rugbyman)
{
	for (RugbyMan* toPass : rugbyman->GetScene<Field>()->mAllRugbyMan)
	{
		if (toPass->GetTag() != rugbyman->GetTag() || toPass == rugbyman) 
			continue;

		if (rugbyman->GetTag() == Field::TEAMBLUE)
		{
			if (toPass->GetPosition().x > rugbyman->GetPosition().x) 
				continue;
		}
		else
		{
			if (toPass->GetPosition().x < rugbyman->GetPosition().x) 
				continue;
		}

		float dist = Utils::GetDistance(rugbyman->GetPosition().x, rugbyman->GetPosition().y, toPass->GetPosition().x, toPass->GetPosition().y);
		if (dist > rugbyman->GetAlliesDetectionRange())	
			continue;

		for (RugbyMan* interceptor : rugbyman->GetScene<Field>()->mAllRugbyMan)
		{
			if (interceptor->IsTag(rugbyman->GetTag()))
				continue;

			sf::Vector2f p = { toPass->GetPosition().x - rugbyman->GetPosition().x,  toPass->GetPosition().y - rugbyman->GetPosition().y };
			float dAB = p.x * p.x + p.y * p.y;
			float u = ((interceptor->GetPosition().x - rugbyman->GetPosition().x) * p.x + (interceptor->GetPosition().y - rugbyman->GetPosition().y) * p.y) / dAB;

			sf::Vector2f projection = { rugbyman->GetPosition().x + u * p.x, rugbyman->GetPosition().y + u * p.y };
			
			float distance = Utils::GetDistance(projection.x, projection.y, interceptor->GetPosition().x, interceptor->GetPosition().y);
			if (distance <= Resources::BallSize + interceptor->GetRadius() * 1.5f)
				return;
		}
		rugbyman->PassBall(toPass);
		return;

	}
}
