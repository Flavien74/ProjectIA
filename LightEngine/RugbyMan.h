#pragma once

#include "Entity.h"
#include "StateMachine.h"

class RugbyMan : public Entity
{
private:

	StateMachine<RugbyMan> mStateMachine;

	enum State
	{
		EnemyGotBall,
		WithoutBall,
		PossessBall,

		Count
	};

	float mStrength;
	float mSprintStrength;

	float mAlliesDetectionRange;
	float mEnemiesDetectionRange;

	std::string mName;

	int mLane;
	sf::Vector2i DefautPos;

	bool mEnemyOnContact = false;
	bool mHaveBall;
	bool mIsImmune = false;

public:
	float mImmuneTimeAfterCatch = 2.8f;
	float mPassCooldownAfterCatch = 0.5f;
	float mAccelerationAfterCatch = 0.5f;

	bool mCanPass = false;

	float GetStrength() const { return mStrength; }
	float GetSprintStrength() const { return mSprintStrength; }
	float GetSpeed() const { return mSpeed; }
	sf::Vector2f GetDirection() const { return mDirection; }
	sf::Vector2i GetDefaultPos() const { return DefautPos; }
	float GetAlliesDetectionRange() const { return mAlliesDetectionRange; }
	float GetEnemiesDetectionRange() const { return mEnemiesDetectionRange; }

	int GetLane() const { return mLane; }

	bool IsImmune() const { return mIsImmune; }
	bool IsEnemyOnContact() const { return mEnemyOnContact; }
	bool HaveBall() const { return mHaveBall; }
	std::string GetName() const { return mName; }

	void KeepInRect(class AABB rect);

	void SetImmune(bool state) { mIsImmune = state; }

	RugbyMan();
	void PassBall(RugbyMan* to);
	void OnStart(int tag, int lane, sf::Vector2i spawn, bool);

	const char* GetStateName(State state) const;

	void ReceiveBall();
	void LooseBall();

protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
	void GiveTheBall(RugbyMan* pCollidedWith);

	friend class RugbyManAction_EnemyGotBall;
	friend class RugbyManAction_WithoutBall;
	friend class RugbyManAction_PossessBall;

	friend class RugbyManCondition_GetBall;
	friend class RugbyManCondition_AllieGetBall;
	friend class RugbyManCondition_EnemyContact;
	friend class RugbyManCondition_Pass;
	friend class RugbyManCondition_EnemyContact;
};