#include "Ball.h"
#include "RugbyMan.h"
#include "Resources.h"
#include "Field.h"
#include <iostream>

void Ball::InitBall(RugbyMan* from, RugbyMan* to)
{
	mFrom = from;
	mTo = to;

}

void Ball::SetDir(sf::Vector2f destination)
{
	mDestination = destination;
}

void Ball::OnUpdate()
{
	GoToPosition(mDestination.x, mDestination.y);
}

void Ball::OnCollision(Entity* collidedWith)
{
	if (collidedWith != mFrom)Destroy();
}

void Ball::OnDestroy()
{
	GetScene<Field>()->mBall = nullptr;
}
