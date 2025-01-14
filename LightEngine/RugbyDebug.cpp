#include "RugbyDebug.h"
#include "RugbyMan.h"
#include "Debug.h"
#include "Field.h"
#include "Utils.h"
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

	RugbyMan* BallOwner = nullptr;

	for (RugbyMan* rugbyMan : mAllRugbyMan)
	{
		if (rugbyMan->HaveBall())
		{
			BallOwner = rugbyMan;
			break;
		}
	}

	if (BallOwner == nullptr)
		return;

	for (RugbyMan* rugbyMan : mAllRugbyMan)
	{
		if (!rugbyMan->IsTag(BallOwner->GetTag()) || rugbyMan == BallOwner)
			continue;

		int behindRelative = (BallOwner->IsTag(Field::TEAMBLUE)) ? -1 : 1;

		if (Utils::GetDistance(BallOwner->GetPosition().x, BallOwner->GetPosition().y,
			rugbyMan->GetPosition().x, rugbyMan->GetPosition().y) > BallOwner->GetDetectionRange())
			continue;

		if (BallOwner->IsTag(Field::TEAMBLUE))
		{
			if (rugbyMan->GetPosition().x > BallOwner->GetPosition().x)
				continue;
		}
		else
		{
			if (rugbyMan->GetPosition().x < BallOwner->GetPosition().x)
				continue;
		}
		Debug::DrawCircle(rugbyMan->GetPosition().x, rugbyMan->GetPosition().y, 10, sf::Color::White);
	}

}