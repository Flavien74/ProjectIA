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
		mAllRugbyMan[i]->OnStart((Tag::TEAMBLUE), mSpawns[i], false);
	}
	for (int i = 5; i < 10; i++)
	{
		mAllRugbyMan[i]->OnStart((Tag::TEAMRED), mSpawns[i], false);
	}
	mTouchdownLines[0] = width * 0.1;
	mTouchdownLines[1] = width * 0.9;

	rugbyDebug = new RugbyDebug();

	rugbyDebug->SetListOfRugbyMan(mAllRugbyMan);

	GiveTheBallRandom(0, 10);
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
	if (mBallOwner != nullptr)IsPlayerScoring(mBallOwner);
}

void Field::PassBall(RugbyMan* from, RugbyMan* to)
{
	mBall = CreateEntity<Ball>(Resources::BallSize, sf::Color::Yellow);
	sf::Vector2f direction = (to->GetPosition() - from->GetPosition());
	//normalize direction
	direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);


	mBall->SetPosition(
		from->GetPosition().x + direction.x * (Resources::PlayerSize + 5),
		from->GetPosition().y + direction.y * (Resources::PlayerSize + 5));

	mBall->InitBall(from, to);
	mBall->SetSpeed(Resources::BallSpeed * from->GetStrength());
	mBall->SetDir(to->GetPosition());
	mBall->SetTag(BALL);
	from->LooseBall();
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
		}

	}
	else {
		if (ballOwner->GetPosition().x < mTouchdownLines[0])
		{
			ScoreRed++;
			Reset();
			GiveTheBallRandom(0, 5);
		}
	}
}

void Field::Reset()
{
	for (RugbyMan* rugbyman : mAllRugbyMan)
	{
		rugbyman->SetPosition(rugbyman->GetDefaultPos().x, rugbyman->GetDefaultPos().y);
		rugbyman->LooseBall();
	}
}

void Field::GiveTheBallRandom(int min, int max)
{
	srand(time(NULL));
	mAllRugbyMan[min + rand() % max]->ReceiveBall();
}