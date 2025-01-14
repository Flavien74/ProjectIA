#include "RugbyMan.h"
#include "Entity.h"
#pragma once

class Ball : public Entity
{
public:
	void InitBall(RugbyMan* from, RugbyMan* to);
	void SetDir(sf::Vector2f destination);

private:
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void OnDestroy() override;
private:

	sf::Vector2f mDestination;
	RugbyMan* mFrom;
	RugbyMan* mTo;
};

