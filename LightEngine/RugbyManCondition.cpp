#include "RugbyManCondition.h"
#include "Field.h"
#include "Utils.h"
#include "RugbyManAction.h"

bool RugbyManCondition_AllieGetBall::OnTest(RugbyMan* owner)
{
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
	if (owner->IsEnemyOnContact()&& !owner->mIsImmune)
		return true;
	return false;
}

bool RugbyManCondition_Pass::OnTest(RugbyMan* owner)
{
	bool condition1 = false;
	bool condition2 = false;

	for (auto rugbyMan : owner->GetScene<Field>()->mAllRugbyMan) {
		if (!rugbyMan->IsTag(owner->mTag))
		{
			condition1 = Utils::GetDistance(owner->GetPosition().x, owner->GetPosition().y,
				rugbyMan->GetPosition().x, rugbyMan->GetPosition().y) < owner->GetEnemiesDetectionRange();
		}
		else {
			condition2 = Utils::GetDistance(owner->GetPosition().x, owner->GetPosition().y,
				rugbyMan->GetPosition().x, rugbyMan->GetPosition().y) < owner->GetAlliesDetectionRange();
		}
	}
	if (condition1 && condition2) {
		return true;
	}
	return false;
}
