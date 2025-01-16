#pragma once
#include "Condition.h"
#include "RugbyMan.h"


class RugbyManCondition_AllyGotBall : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};

class RugbyManCondition_GetBall : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};

class RugbyManCondition_BlockedByEnemies : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};

class RugbyManCondition_EnemyVisible : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};
class RugbyManCondition_SecuredBall: public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};
