#pragma once
#include <SFML/Window/Event.hpp>
#include "Entity.h"

class RugbyMan;

class RugbyDebug
{
public:
	RugbyDebug();

	void OnDebugEvent(const sf::Event& event);
	void OnUpdate();
	void SetListOfRugbyMan(std::vector<RugbyMan*>&);

private:
	std::vector<RugbyMan*> mAllRugbyMan;
	RugbyMan* mEntitySelected;

	void TrySetSelectedEntity(RugbyMan* pEntity, int x, int y);
};