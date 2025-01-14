#include "Ball.h"
#include "RugbyMan.h"
#include "Resources.h"

void Ball::InitBall(RugbyMan* from, RugbyMan* to)
{
	mFrom = from;
	mTo = to;

}

void Ball::OnUpdate()
{
	float rugbyMenDist = std::sqrt(
		(mTo->GetPosition().x - mFrom->GetPosition().x) * (mTo->GetPosition().x - mFrom->GetPosition().x)
		+ (mTo->GetPosition().y - mFrom->GetPosition().y) * (mTo->GetPosition().y - mFrom->GetPosition().y));

	float ballFromDist = std::sqrt(
		(GetPosition().x - mFrom->GetPosition().x) * (GetPosition().x - mFrom->GetPosition().x)
		+ (GetPosition().y - mFrom->GetPosition().y) * (GetPosition().y - mFrom->GetPosition().y));

	float TraveledDistanceRatio = (ballFromDist - (rugbyMenDist / 2) / rugbyMenDist) + .5f;
	mShape.setRadius(Resources::BallSize * (1 + TraveledDistanceRatio));
}