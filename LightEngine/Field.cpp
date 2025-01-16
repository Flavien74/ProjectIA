#include "Resources.h"
#include "Ball.h"
#include "Field.h"
#include "RugbyMan.h"
#include <iostream>
#include "RugbyDebug.h"
#include "Debug.h"

void Field::OnInitialize()
{
	int width = GetWindowWidth();
	int height = GetWindowHeight();

	std::cout << width << std::endl;
	std::cout << height << std::endl;

	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Green));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Green));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Green));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Green));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Green));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Red));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Red));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Red));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Red));
	mAllRugbyMan.push_back(CreateEntity<RugbyMan>(30, sf::Color::Red));

	for (int i = 0; i < 10; i++)
	{
		mAllRugbyMan[i]->SetPosition(mSpawns[i].x, mSpawns[i].y);
	}

	mAllRugbyMan[0]->OnStart((Tag::TEAMBLUE), 0, mSpawns[0], false);
	mAllRugbyMan[1]->OnStart((Tag::TEAMBLUE), 0, mSpawns[1], false);
	mAllRugbyMan[2]->OnStart((Tag::TEAMBLUE), 1, mSpawns[2], false);
	mAllRugbyMan[3]->OnStart((Tag::TEAMBLUE), 2, mSpawns[3], false);
	mAllRugbyMan[4]->OnStart((Tag::TEAMBLUE), 2, mSpawns[4], false);
	mAllRugbyMan[5]->OnStart((Tag::TEAMRED), 0, mSpawns[5], false);
	mAllRugbyMan[6]->OnStart((Tag::TEAMRED), 0, mSpawns[6], false);
	mAllRugbyMan[7]->OnStart((Tag::TEAMRED), 1, mSpawns[7], false);
	mAllRugbyMan[8]->OnStart((Tag::TEAMRED), 2, mSpawns[8], false);
	mAllRugbyMan[9]->OnStart((Tag::TEAMRED), 2, mSpawns[9], false);

	mTouchdownLines[0] = width * 0.1;
	mTouchdownLines[1] = width * 0.9;

	rugbyDebug = new RugbyDebug();

	rugbyDebug->SetListOfRugbyMan(mAllRugbyMan);

	GiveTheBallRandom(0, 10);

	mLanes[0] = { 0, 0 ,GetWindowWidth(), GetWindowHeight() / 2 };
	mLanes[2] = { 0, GetWindowHeight() / 2, GetWindowWidth(), GetWindowHeight() };
	mLanes[1] = { 0, GetWindowHeight() / 4 ,GetWindowWidth(),3 * GetWindowHeight() / 4 };
}

void Field::OnEvent(const sf::Event& event)
{
	rugbyDebug->OnDebugEvent(event, mBallOwner);
}

void Field::OnUpdate()
{
	rugbyDebug->OnUpdate();
	Debug d;

	d.DrawLine(mTouchdownLines[0], 0, mTouchdownLines[0], GetWindowHeight(), sf::Color::White);
	d.DrawLine(mTouchdownLines[1], 0, mTouchdownLines[1], GetWindowHeight(), sf::Color::White);

	//d.DrawLine(0, 0, GetWindowWidth(), GetWindowHeight() / 2, sf::Color::Red);
	//d.DrawLine(0, GetWindowHeight() / 2, GetWindowWidth(), GetWindowHeight(), sf::Color::Blue);
	//d.DrawLine(0, GetWindowHeight() / 4, GetWindowWidth(), 3 * GetWindowHeight() / 4, sf::Color::Magenta);

	if (mBallOwner != nullptr)IsPlayerScoring(mBallOwner);
}

void Field::ChangeBallOwner(RugbyMan* newBallOwner)
{
	mBallOwner = newBallOwner;
}

void Field::IsPlayerScoring(RugbyMan* ballOwner)
{
	if (ballOwner->IsTag(Tag::TEAMBLUE)) {
		if (ballOwner->GetPosition().x > mTouchdownLines[1])
		{
			ScoreBlue++;
			Reset();
			GiveTheBallRandom(5, 4);
			return;
		}
	}
	if (ballOwner->GetPosition().x < mTouchdownLines[0])
	{
		ScoreRed++;
		Reset();
		GiveTheBallRandom(0, 5);
	}
}

void Field::Reset()
{
	for (RugbyMan* rugbyman : mAllRugbyMan)
	{
		rugbyman->SetPosition(rugbyman->GetDefaultPos().x, rugbyman->GetDefaultPos().y);
		rugbyman->LooseBall();
		rugbyDebug->ResetEntitySelected();
	}
}

void Field::GiveTheBallRandom(int min, int max)
{
	srand(time(NULL));
	mAllRugbyMan[min + rand() % max]->ReceiveBall();
}