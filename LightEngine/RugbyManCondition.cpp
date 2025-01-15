#include "RugbyManCondition.h"
#include "Field.h"
#include "Utils.h"

bool RugbyManCondition_AllieGetBall::OnTest(RugbyMan* owner)
{
	if (owner->HaveBall())
	{
		return false;
	}
	for (auto rugbymen : owner->GetScene<Field>()->mAllRugbyMan)
	{
		if (rugbymen->IsTag(owner->mTag) && rugbymen->HaveBall()) {
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

bool RugbyManCondition_EnemyContact::OnTest(RugbyMan* owner)
{
	if (owner->IsEnemyOnContact())
		return true;
	return false;
}

bool RugbyManCondition_Pass::OnTest(RugbyMan* owner)
{
	for (auto rugbyMan : owner->GetScene<Field>()->mAllRugbyMan) {
		if (!rugbyMan->IsTag(owner->mTag))
		{
			if (Utils::GetDistance(owner->GetPosition().x, owner->GetPosition().y,
				rugbyMan->GetPosition().x, rugbyMan->GetPosition().y) > owner->GetEnemiesDetectionRange()) {
				return true;
			}
		}
	}
	return false;
}
