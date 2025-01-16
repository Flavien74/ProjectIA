#include "RugbyMan.h"
#include "Field.h"
#include "Ball.h"
#include "Resources.h"
#include <iostream>
#include "RugbyManAction.h"
#include "RugbyManCondition.h"

RugbyMan::RugbyMan() :
	mStrength(10), mSprintStrength(10), mAlliesDetectionRange(150), mEnemiesDetectionRange(150), mEnemiesDetectionConeAngle(45), mName("Jake"), mStateMachine(this, State::Count)
{
	mRigidBody = true;

	//-> ENEMYGOTBALL
	{
		Behaviour<RugbyMan>* pEnemyGotBall = mStateMachine.CreateBehaviour(State::EnemyGotBall);
		pEnemyGotBall->AddAction<RugbyManAction_EnemyGotBall>();

		//-> WHITHOUTBALL
		{
			auto transition = pEnemyGotBall->CreateTransition(State::WithoutBall);

			auto condition = transition->AddCondition<RugbyManCondition_AllyGotBall>(true);
		}

		//-> ENTERPOSSESSION
		{
			auto transition = pEnemyGotBall->CreateTransition(State::EnterPossession);

			auto condition = transition->AddCondition<RugbyManCondition_GetBall>(true);
		}
	}

	//-> WHITHOUTBALL
	{
		Behaviour<RugbyMan>* pWhitoutBall = mStateMachine.CreateBehaviour(State::WithoutBall);
		pWhitoutBall->AddAction<RugbyManAction_WithoutBall>();

		//-> ENEMYGOTBALL
		{
			auto transition = pWhitoutBall->CreateTransition(State::EnemyGotBall);

			auto condition = transition->AddCondition<RugbyManCondition_AllyGotBall>(false);
		}

		//-> ENTERPOSSESSION
		{
			auto transition = pWhitoutBall->CreateTransition(State::EnterPossession);

			auto condition = transition->AddCondition<RugbyManCondition_GetBall>(true);
		}
	}

	//-> POSSESSBALL
	{
		Behaviour<RugbyMan>* pPossessBall = mStateMachine.CreateBehaviour(State::PossessBall);
		pPossessBall->AddAction<RugbyManAction_PossessBall>();

		//-> WHITHOUTBALL
		{
			auto transition = pPossessBall->CreateTransition(State::WithoutBall);

			auto condition = transition->AddCondition<RugbyManCondition_GetBall>(false);
		}
	}
	//-> ENTERPOSSESSION
	{
		Behaviour<RugbyMan>* pEnterPossession = mStateMachine.CreateBehaviour(State::EnterPossession);
		pEnterPossession->AddAction<RugbyManAction_EnterPossession>();

		//-> POSSESSBALL
		{
			auto transition = pEnterPossession->CreateTransition(State::PossessBall);

			auto condition = transition->AddCondition<RugbyManCondition_SecuredBall>(true);
		}
	}
	mStateMachine.SetState(State::WithoutBall);
}

void RugbyMan::OnStart(int tag, int lane, sf::Vector2i spawn, bool isBallMine)
{
	mLane = lane;
	mHaveBall = isBallMine;
	mDefautPos = spawn;
	mSpeed = 50;
	mDefaultSpeed = mSpeed;
	SetTag(tag);
}

void RugbyMan::KeepInRect(AABB rect)
{
	if (GetPosition().x > rect.xMax)
	{
		SetPosition(GetPosition().x - (GetPosition().x - rect.xMax), GetPosition().y);
	}
	else if (GetPosition().x < rect.xMin)
	{
		SetPosition(GetPosition().x - (GetPosition().x - rect.xMin), GetPosition().y);
	}

	if (GetPosition().y > rect.yMax)
	{
		SetPosition(GetPosition().x, GetPosition().y - (GetPosition().y - rect.yMax));
	}
	else if (GetPosition().y < rect.yMin)
	{
		SetPosition(GetPosition().x, GetPosition().y - (GetPosition().y - rect.yMin));
	}
}

void RugbyMan::SetImmune(bool state)
{
	mIsImmune = state;
}

void RugbyMan::PassBall(RugbyMan* to)
{
	if (GetScene<Field>()->mBall != nullptr || to == this || to == nullptr) return;
	GetScene<Field>()->mBall = GetScene()->CreateEntity<Ball>(Resources::BallSize, sf::Color::Yellow);
	sf::Vector2f direction = (to->GetPosition() - GetPosition());
	//normalize direction
	direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);


	GetScene<Field>()->mBall->SetPosition(
		GetPosition().x + direction.x * (Resources::PlayerSize + 5),
		GetPosition().y + direction.y * (Resources::PlayerSize + 5));

	GetScene<Field>()->mBall->InitBall(this, to);
	GetScene<Field>()->mBall->SetSpeed(Resources::BallSpeed * GetStrength());
	GetScene<Field>()->mBall->SetDir(to->GetPosition());
	GetScene<Field>()->mBall->SetTag(Field::BALL);
	mHaveBall = false;
	GetScene<Field>()->ChangeBallOwner(nullptr);
}

const char* RugbyMan::GetStateName(State state) const
{
	switch (state)
	{
	case EnemyGotBall: return "Idle";
	case WithoutBall: return "Shooting";
	case PossessBall: return "Reloading";
	default: return "Unknown";
	}
}

void RugbyMan::OnUpdate()
{
	this->KeepInRect(GetScene<Field>()->mLanes[mLane]);
	mStateMachine.Update();
}

void RugbyMan::OnCollision(Entity* pCollidedWith)
{
	if (mHaveBall && !pCollidedWith->IsTag(mTag) && !IsImmune()) {
		RugbyMan* pRugbyMan = dynamic_cast<RugbyMan*>(pCollidedWith);
		GiveTheBall(pRugbyMan);
	}
	else if (pCollidedWith->IsTag(Field::Tag::BALL)) {
		ReceiveBall();
	}
}

void RugbyMan::GiveTheBall(RugbyMan* pCollidedWith)
{
	mHaveBall = false;
	pCollidedWith->ReceiveBall();
}

void RugbyMan::ReceiveBall()
{
	mIsImmune = true;
	mHaveBall = true;
	GetScene<Field>()->ChangeBallOwner(this);
	std::cout << "recieved" << std::endl;
}

void RugbyMan::LooseBall()
{
	mHaveBall = false;
}