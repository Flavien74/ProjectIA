#include "RugbyMan.h"
#include "Entity.h"
#pragma once

class Ball : public Entity
{
public:
	void InitBall(RugbyMan* from, RugbyMan* to);

private:
	void OnUpdate() override;

private:
	RugbyMan* mFrom;
	RugbyMan* mTo;
};

