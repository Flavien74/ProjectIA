#include "RugbyMan.h"
#include "Field.h"
#include "Ball.h"
#include "Resources.h"
#include <iostream>

RugbyMan::RugbyMan() :
	mStrength(10), mSprintStrength(10), mPassCooldownAfterCatch(1), mImmuneTimeAfterCatch(0.5), mName("Jake")
{
	mRigidBody = true;
}

void RugbyMan::PassBall(RugbyMan* to)
{
	Ball* mBall = GetScene()->CreateEntity<Ball>(Resources::BallSize, sf::Color::Yellow);
	sf::Vector2f direction = (to->GetPosition() - GetPosition());
	//normalize direction
	direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);


	mBall->SetPosition(
		GetPosition().x + direction.x * (Resources::PlayerSize + 5),
		GetPosition().y + direction.y * (Resources::PlayerSize + 5));

	mBall->InitBall(this, to);
	mBall->SetSpeed(Resources::BallSpeed * GetStrength());
	mBall->SetDir(to->GetPosition());
	mBall->SetTag(Field::BALL);
	LooseBall();
}


void RugbyMan::OnStart(int tag, int spawnIndex, bool isBallMine)
{
	//mLane = lane;
	mHaveBall = isBallMine;
	mSpawnIndex = spawnIndex;
	SetTag(tag);
	if (IsTag(Field::Tag::TEAMBLUE)) {
		SetDirection(.5f, 0, 50);
	}
	else {
		SetDirection(-.5f, 0, 50);
	}
}

void RugbyMan::OnUpdate()
{

}

void RugbyMan::OnCollision(Entity* pCollidedWith)
{
	if (pCollidedWith->IsTag(Field::Tag::BALL)) {
		ReceiveBall();
		return;
	}
	if (mHaveBall && !pCollidedWith->IsTag(mTag)) {
		RugbyMan* pRugbyMan = dynamic_cast<RugbyMan*>(pCollidedWith);
		GiveTheBall(pRugbyMan);
	}
}

void RugbyMan::GiveTheBall(RugbyMan* pCollidedWith)
{
	mHaveBall = false;
	pCollidedWith->ReceiveBall();
	std::cout << "I gave the ball" << std::endl;
}

void RugbyMan::ReceiveBall()
{
	std::cout << "I have the ball" << std::endl;
	mHaveBall = true;
	dynamic_cast<Field*>(GetScene())->ChangeBallOwner(this);
}
