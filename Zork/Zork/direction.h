#pragma once

namespace Zork
{
	enum Direction
	{
		NORTH,
		EAST,
		SOUTH,
		WEST
	};

	inline const char* DirectionToString(const Direction direction)
	{
		switch (direction)
		{
			case Direction::EAST:
			{
				return "East";
			}

			case Direction::NORTH:
			{
				return "North";
			}

			case Direction::SOUTH:
			{
				return "South";
			}

			case Direction::WEST:
			{
				return "West";
			}

			default:
			{
				return "NONE";
			}
		}
	}
}