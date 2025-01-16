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
		Drible,
		EnterPossession,

		Count
	};

	float mStrength;
	float mSprintStrength;

	float mSpeedMultiplicator;

	float mAlliesDetectionRange;

	float mEnemiesDetectionRange;
	float mEnemiesDetectionConeAngle;

	std::string mName;

	int mLane;
	sf::Vector2i mDefautPos;
	bool mEnemyOnContact = false;
	bool mHaveBall;
	bool mIsImmune = false;

public:
	float mImmuneTimeAfterCatch = 1.25f;
	float mPassCooldownAfterCatch = 1;
	float mAccelerationAfterCatch = 1;

	float mDefaultSpeed;
	bool mCanPass = false;

	float GetStrength() const { return mStrength; }
	float GetSprintStrength() const { return mSprintStrength; }
	float GetSpeed() const { return mSpeed; }
	sf::Vector2f GetDirection() const { return mDirection; }
	sf::Vector2i GetDefaultPos() const { return mDefautPos; }
	float GetAlliesDetectionRange() const { return mAlliesDetectionRange; }

	float GetEnemiesDetectionRange() const { return mEnemiesDetectionRange; }
	float GetEnemiesDetectionConeAngle() const { return mEnemiesDetectionConeAngle; }

	int GetLane() const { return mLane; }

	bool IsImmune() const { return mIsImmune; }
	bool HaveBall() const { return mHaveBall; }
	std::string GetName() const { return mName; }

	void KeepInRect(class AABB rect);

	void SetImmune(bool state);

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
	friend class RugbyManAction_Drible;

	friend class RugbyManCondition_GetBall;
	friend class RugbyManCondition_AllieGetBall;
	friend class RugbyManCondition_EnemyContact;
	friend class RugbyManCondition_BlockedByEnemies;
	friend class RugbyManCondition_EnemyVisible;
	friend class RugbyManCondition_CanPass;
	friend class RugbyManAction_EnterPossession;
};