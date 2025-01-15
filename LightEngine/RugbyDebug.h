#pragma once
#include <SFML/Window/Event.hpp>
#include "Entity.h"

class RugbyMan;

class RugbyDebug
{
public:
	RugbyDebug();

	void OnDebugEvent(const sf::Event& event, RugbyMan* ballOwner);
	void OnUpdate();
	void SetListOfRugbyMan(std::vector<RugbyMan*>&);
	void ResetEntitySelected();
private:
	std::vector<RugbyMan*> mAllRugbyMan;
	RugbyMan* mEntitySelected;

	RugbyMan* TrySetSelectedEntity(RugbyMan* pEntity, int x, int y);
};