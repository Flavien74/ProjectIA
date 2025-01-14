#include "Resources.h"
#include "Entity.h"
#include "Ball.h"
#include "Field.h"

void Field::PassBall(RugbyMan* from, RugbyMan* to)
{
	mBall = CreateEntity<Ball>(Resources::BallSize, sf::Color::Yellow);
	sf::Vector2f direction = (to->GetShape()->getPosition() - from->GetShape()->getPosition());
	//normalize direction
	direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

	mBall->SetPosition(
		from->GetPosition().x + direction.x * (Resources::PlayerSize + Resources::BallSize),
		from->GetPosition().y + direction.y * (Resources::PlayerSize + Resources::BallSize));

	mBall->InitBall(from, to);
	mBall->SetSpeed(Resources::BallSpeed * from->GetStrength());
	mBall->GoToPosition(to->GetPosition().x, to->GetPosition().y);
}
