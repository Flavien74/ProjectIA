#pragma once

#include <SFML/System/Vector2.hpp>

namespace Utils
{
	bool Normalize(sf::Vector2f& vector);
	float GetDistance(float x1, float y1, float x2, float y2);
	float GetAngleDegree(const sf::Vector2f& v1, const sf::Vector2f& v2);
}