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
	/*float rugbyMenDist = std::sqrt(
		(mTo->GetPosition().x - mFrom->GetPosition().x) * (mTo->GetPosition().x - mFrom->GetPosition().x)
		+ (mTo->GetPosition().y - mFrom->GetPosition().y) * (mTo->GetPosition().y - mFrom->GetPosition().y));
	float ballFromDist = std::sqrt(
		(GetPosition().x - mFrom->GetPosition().x) * (GetPosition().x - mFrom->GetPosition().x)
		+ (GetPosition().y - mFrom->GetPosition().y) * (GetPosition().y - mFrom->GetPosition().y));

	float TraveledDistanceRatio = 1.5f-(abs(ballFromDist - (rugbyMenDist / 2)) / rugbyMenDist);
	std::cout << TraveledDistanceRatio << std::endl;
	mShape.setRadius(Resources::BallSize * (TraveledDistanceRatio));*/
}

void Ball::OnCollision(Entity* collidedWith)
{
	Destroy();
}

void Ball::OnDestroy()
{
	dynamic_cast<Field*>(GetScene())->mBall = nullptr;
}
