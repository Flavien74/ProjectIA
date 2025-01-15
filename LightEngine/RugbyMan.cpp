#include "RugbyMan.h"
#include "Field.h"
#include "Ball.h"
#include "Resources.h"
#include <iostream>

RugbyMan::RugbyMan() :
	mStrength(10), mSprintStrength(10), mPassCooldownAfterCatch(1), mImmuneTimeAfterCatch(0.5), mDetectionRange(200), mName("Jake")
{
	mRigidBody = true;
}

void RugbyMan::PassBall(RugbyMan* to)
{
	if (dynamic_cast<Field*>(GetScene())->mBall != nullptr || to == this || to == nullptr) return;
	dynamic_cast<Field*>(GetScene())->mBall = GetScene()->CreateEntity<Ball>(Resources::BallSize, sf::Color::Yellow);
	sf::Vector2f direction = (to->GetPosition() - GetPosition());
	//normalize direction
	direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);


	dynamic_cast<Field*>(GetScene())->mBall->SetPosition(
		GetPosition().x + direction.x * (Resources::PlayerSize + 5),
		GetPosition().y + direction.y * (Resources::PlayerSize + 5));

	dynamic_cast<Field*>(GetScene())->mBall->InitBall(this, to);
	dynamic_cast<Field*>(GetScene())->mBall->SetSpeed(Resources::BallSpeed * GetStrength());
	dynamic_cast<Field*>(GetScene())->mBall->SetDir(to->GetPosition());
	dynamic_cast<Field*>(GetScene())->mBall->SetTag(Field::BALL);
	LooseBall();
}


void RugbyMan::OnStart(int tag, int lane, sf::Vector2i spawn, bool isBallMine)
{
	mLane = lane;
	mHaveBall = isBallMine;
	DefautPos = spawn;
	SetTag(tag);
	if (IsTag(Field::Tag::TEAMBLUE)) {
		mDirection = sf::Vector2f(0.5f,0);
	}
	else {
		mDirection = sf::Vector2f(-0.5f, 0);
	}
	mSpeed = 50;
	SetDirection(mDirection.x, mDirection.y, mSpeed);
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

void RugbyMan::LooseBall()
{
	mHaveBall = false;
	dynamic_cast<Field*>(GetScene())->ChangeBallOwner(nullptr);
}
