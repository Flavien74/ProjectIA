#include "Resources.h"
#include "Entity.h"
#include "Ball.h"
#include "Field.h"
#include "RugbyMan.h"
#include <iostream>

void Field::PassBall(RugbyMan* from, RugbyMan* to)
{
	mBall = CreateEntity<Ball>(Resources::BallSize, sf::Color::Yellow);
	sf::Vector2f direction = (to->GetShape()->getPosition() - from->GetShape()->getPosition());
	//normalize direction
	direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

	mBall->SetPosition(
		from->GetPosition().x + direction.x * (Resources::PlayerSize + Resources::BallSize),
		from->GetPosition().y + direction.y * (Resources::PlayerSize + Resources::BallSize));

	mBall->InitBall(from, to);
	mBall->SetSpeed(Resources::BallSpeed * from->GetStrength());
	mBall->GoToPosition(to->GetPosition().x, to->GetPosition().y);
}

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

	/*
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMBLUE), 1, 0));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMBLUE), 1, 1));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMBLUE), 2, 2));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMBLUE), 3, 3));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMBLUE), 3, 5));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMRED), 1, 5));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMRED), 1, 6));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMRED), 2, 7));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMRED), 3, 8));
	mAllRugbyMan.push_back(new RugbyMan((Tag::TEAMRED), 3, 9));*/

	for (int i = 0; i < 10; i++)
	{
		mAllRugbyMan[i]->SetPosition(mSpawns[i].x,mSpawns[i].y);
	}
}

void Field::OnEvent(const sf::Event& event)
{
}

void Field::OnUpdate()
{
}

void Field::ChangeBallOwner(RugbyMan* newBallOwner)
{
	mBallOwner = newBallOwner;
}
