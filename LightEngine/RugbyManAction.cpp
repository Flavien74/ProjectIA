#include "Field.h"
#include "RugbyManAction.h"

void RugbyManAction_EnemyGotBall::Update(RugbyMan* rugbyman)
{
	if (mTarget == nullptr)
		dynamic_cast<Field*>(rugbyman->GetScene())->mBallOwner;

	AABB playerLane = dynamic_cast<Field*>(rugbyman->GetScene())->mLanes[rugbyman->GetLane()];

	rugbyman->GoToPosition(mTarget->GetPosition().x, mTarget->GetPosition().y);

	rugbyman->KeepInRect(playerLane);
}


/// RAPH (haut) Flav (bas)