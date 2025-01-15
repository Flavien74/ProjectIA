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
				mEntitySelected = TrySetSelectedEntity(rugbyman, event.mouseButton.x, event.mouseButton.y);
				if (mEntitySelected != nullptr) break;
			}
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		for (auto rugbyman : mAllRugbyMan) {
			ballOwner->PassBall(TrySetSelectedEntity(rugbyman, event.mouseButton.x, event.mouseButton.y));
		}

	}
}

void RugbyDebug::SetListOfRugbyMan(std::vector<RugbyMan*>& list)
{
	mAllRugbyMan = list;
}

void RugbyDebug::ResetEntitySelected()
{
	/*sf::Vector2f baseDir = mEntitySelected->GetDirection();
	float baseSpeed = mEntitySelected->GetSpeed();
	mEntitySelected->SetDirection(baseDir.x, baseDir.y, baseSpeed);
	mEntitySelected = nullptr;*/
}

RugbyMan* RugbyDebug::TrySetSelectedEntity(RugbyMan* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false) {
		return nullptr;
	}

	return pEntity;
}

void RugbyDebug::OnUpdate()
{
	if (mEntitySelected != nullptr)
	{
		sf::Vector2f position = mEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 12, sf::Color::Blue);
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

	Debug::DrawCircle(BallOwner->GetPosition().x, BallOwner->GetPosition().y, 15, sf::Color::Yellow);



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