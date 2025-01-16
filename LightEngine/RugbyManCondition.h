#pragma once
#include "Condition.h"
#include "RugbyMan.h"


class RugbyManCondition_AllieGetBall : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};

class RugbyManCondition_GetBall : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};

class RugbyManCondition_CanPass : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};

class RugbyManCondition_BlockedByEnemeis : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};