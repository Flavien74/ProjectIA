#pragma once
#include "Condition.h"
#include "RugbyMan.h"

class RugbyManCondition : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};
