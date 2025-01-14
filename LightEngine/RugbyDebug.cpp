#include "RugbyDebug.h"
#include "RugbyMan.h"
#include "Debug.h"
#include <iostream>

RugbyDebug::RugbyDebug()
{
}

void RugbyDebug::OnDebugEvent(const sf::Event& event, RugbyMan* ballOwner)
{
	if (event.key.code == sf::Keyboard::Space) {
		mEntitySelected = nullptr;
	}
		
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		if (mEntitySelected != nullptr)
		{
			mEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
		else {
			for (auto rugbyman : mAllRugbyMan) {
				TrySetSelectedEntity(rugbyman, event.mouseButton.x, event.mouseButton.y);
			}
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (mEntitySelected != nullptr)
		{
			ballOwner->PassBall(mEntitySelected);
		}
	}
}

void RugbyDebug::SetListOfRugbyMan(std::vector<RugbyMan*>& list)
{
	mAllRugbyMan = list;
}

void RugbyDebug::TrySetSelectedEntity(RugbyMan* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false) {
		return;
	}

	mEntitySelected = pEntity;
}

void RugbyDebug::OnUpdate()
{
	if (mEntitySelected != nullptr)
	{
		sf::Vector2f position = mEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}