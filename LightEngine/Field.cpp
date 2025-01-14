#include "Resources.h"
#include "Entity.h"
#include "Ball.h"
#include "Field.h"
#include "RugbyMan.h"
#include <iostream>
#include "RugbyDebug.h"

void Field::OnInitialize()
{
	int width = GetWindowWidth();
	int height = GetWindowHeight();

	std::cout << width << std::endl;
	std::cout << height << std::endl;

	mSpawns.push_back({ 50, 50 });
	mSpawns.push_back({ 200, 100 });
	mSpawns.push_back({ 320, 360 });
	mSpawns.push_back({ 200, 620 });
	mSpawns.push_back({ 50, 670 });
	mSpawns.push_back({ 1230, 50 });
	mSpawns.push_back({ 1080, 100 });
	mSpawns.push_back({ 960, 360 });
	mSpawns.push_back({ 1080, 620 });
	mSpawns.push_back({ 1230, 670 });

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
	for (int i = 0; i < 5; i++)
	{
		mAllRugbyMan[i]->OnStart((Tag::TEAMBLUE), i, false);
	}
	for (int i = 5; i < 10; i++)
	{
		mAllRugbyMan[i]->OnStart((Tag::TEAMRED), i, false);
	}

	rugbyDebug = new RugbyDebug();

	rugbyDebug->SetListOfRugbyMan(mAllRugbyMan);

	srand(time(NULL));
	mAllRugbyMan[rand() % 10]->ReceiveBall();
}

void Field::OnEvent(const sf::Event& event)
{
	rugbyDebug->OnDebugEvent(event, mBallOwner);
}

void Field::OnUpdate()
{
	rugbyDebug->OnUpdate();
}

void Field::ChangeBallOwner(RugbyMan* newBallOwner)
{
	mBallOwner = newBallOwner;
}
