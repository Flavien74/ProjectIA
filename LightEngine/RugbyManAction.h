#pragma once

#include "Action.h"
#include "RugbyMan.h"

class RugbyManAction_EnemyGotBall : public Action <RugbyMan>
{
public:
	void Start(RugbyMan* rugbyman) override {}
	void Update(RugbyMan* rugbyman) override {}
	void End(RugbyMan* rugbyman) override {}
};

class RugbyManAction_WithoutBall : public Action <RugbyMan>
{
public:
	void Start(RugbyMan* rugbyman) override {}
	void Update(RugbyMan* rugbyman) override {}
	void End(RugbyMan* rugbyman) override {}
};

class RugbyManAction_PossessBall : public Action <RugbyMan>
{
public:
	void Start(RugbyMan* rugbyman) override {}
	void Update(RugbyMan* rugbyman) override {}
	void End(RugbyMan* rugbyman) override {}
};