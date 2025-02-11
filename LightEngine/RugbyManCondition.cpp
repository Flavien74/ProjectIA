#include "RugbyManCondition.h"
#include "Field.h"
#include "Utils.h"
#include "RugbyManAction.h"

bool RugbyManCondition_AllyGotBall::OnTest(RugbyMan* owner)
{
	for (auto rugbymen : owner->GetScene<Field>()->mAllRugbyMan)
	{
		if (rugbymen->IsTag(owner->GetTag()) && rugbymen->HaveBall()) {
			return true;
		}
	}
	return false;
}

bool RugbyManCondition_GetBall::OnTest(RugbyMan* owner)
{
	if (owner->HaveBall())
		return true;
	return false;
}

bool RugbyManCondition_BlockedByEnemies::OnTest(RugbyMan* owner)
{
	int numberOfEnemies = 0;

	for (RugbyMan* rugbyMan : owner->GetScene<Field>()->mAllRugbyMan)
	{
		if (rugbyMan->IsTag(owner->GetTag())) 
			continue;

		float distance = Utils::GetDistance(owner->GetPosition().x, owner->GetPosition().y, rugbyMan->GetPosition().x, rugbyMan->GetPosition().y);
		if (distance > owner->GetEnemiesDetectionRange()) 
			continue;

		float angle = Utils::GetAngleDegree(owner->GetDirection(), rugbyMan->GetPosition() - owner->GetPosition());
		if (angle >= -owner->GetEnemiesDetectionConeAngle() && owner->GetEnemiesDetectionConeAngle() >= angle)
			numberOfEnemies++;
	}
	return numberOfEnemies > 1;
}

bool RugbyManCondition_EnemyVisible::OnTest(RugbyMan* owner)
{
	bool condition = false;
	for (auto rugbyMan : owner->GetScene<Field>()->mAllRugbyMan) {
		if (!rugbyMan->IsTag(owner->GetTag()))
		{
			condition = Utils::GetDistance(owner->GetPosition().x, owner->GetPosition().y,
				rugbyMan->GetPosition().x, rugbyMan->GetPosition().y) < owner->GetEnemiesDetectionRange();
			if (condition) {
				return condition;
			}
		}
	}
	return condition;
}

bool RugbyManCondition_SecuredBall::OnTest(RugbyMan* owner)
{
	return (!owner->IsImmune() && owner->mCanPass && owner->GetSpeed() == owner->mDefaultSpeed);
}
