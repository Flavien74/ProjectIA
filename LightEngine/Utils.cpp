#include <SFML/System/Vector2.hpp>

#include <cmath>

namespace Utils
{
	bool Normalize(sf::Vector2f& vector)
	{
		float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude != 0)
		{
			vector.x /= magnitude;
			vector.y /= magnitude;

			return true;
		}

		return false;
	}

	float GetDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return std::sqrt(x * x + y * y);
	}

	float GetAngleDegree(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		float dot = v1.x * v2.x + v1.y * v2.y;
		float det = v1.x * v2.y - v1.y * v2.x;

		return std::atan2(det, dot) * 180 / 3.14159265;
	}
}