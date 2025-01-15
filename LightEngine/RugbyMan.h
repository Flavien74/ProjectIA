#include "Entity.h"
#pragma once

class RugbyMan : public Entity
{
private:
	float mStrength;
	float mSprintStrength;

	float mAlliesDetectionRange;
	float mEnemiesDetectionRange;

	std::string mName;

	int mLane;
	sf::Vector2i DefautPos;

	bool mHaveBall;

public:
	float mImmuneTimeAfterCatch = 0.5f;
	float mPassCooldownAfterCatch = 0.5f;
	float mAccelerationAfterCatch = 0.5f;

	float GetStrength() const { return mStrength; }
	float GetSprintStrength() const { return mSprintStrength; }
	float GetSpeed() const { return mSpeed; }
	sf::Vector2f GetDirection() const { return mDirection; }
	sf::Vector2i GetDefaultPos() const { return DefautPos; }
	float GetAlliesDetectionRange() const { return mAlliesDetectionRange; }
	float GetEnemiesDetectionRange() const { return mEnemiesDetectionRange; }
	int GetLane() const { return mLane; }

	bool HaveBall() const { return mHaveBall; }
	std::string GetName() const { return mName; }

	void KeepInRect(class AABB rect);

	RugbyMan();
	void PassBall(RugbyMan* to);
	void OnStart(int tag, int lane, sf::Vector2i spawn, bool);

	void ReceiveBall();
	void LooseBall();

protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
	void GiveTheBall(RugbyMan* pCollidedWith);

	friend class RugbyManAction_EnemyGotBall;
	friend class RugbyManAction_WithoutBall;
	friend class RugbyManAction_PossessBall;

	friend class PlantCondition_FullAmmo;
	friend class PlantCondition_NoAmmo;
	friend class PlantCondition_ZombieOnLane;
};