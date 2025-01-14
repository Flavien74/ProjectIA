#include "Entity.h"
#pragma once

class RugbyMan : public Entity
{
private:
	float mStrength;
	float mSprintStrength;

	float mPassCooldownAfterCatch;
	float mImmuneTimeAfterCatch;

	float mDetectionRange;

	std::string mName;

	int mLane;
	sf::Vector2i DefautPos;

	bool mHaveBall;

public:
	float GetStrength() const { return mStrength; }
	float GetSprintStrength() const { return mSprintStrength; }
	float GetSpeed() const { return mSpeed; }
	sf::Vector2i GetDefaultPos() const { return DefautPos; }
	float GetDetectionRange() const { return mDetectionRange; }
	bool HaveBall() { return mHaveBall; }
	std::string GetName() const { return mName; }

	RugbyMan();
	void PassBall(RugbyMan* to);
	void OnStart(int tag, sf::Vector2i spawn, bool);

	void ReceiveBall();
	void LooseBall();

protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
	void GiveTheBall(RugbyMan* pCollidedWith);
};