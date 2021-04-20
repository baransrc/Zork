#pragma once

namespace Zork
{
	enum NatureType
	{
		WATER,
		EARTH,
		AIR,
		FIRE,
	};

	enum NatureTypeEffectiveness
	{
		NOT_EFFECTIVE,
		EFFECTIVE,
		OVERLY_EFFECTIVE
	};

	inline const float GetDamageMultiplierByEffectiveness(const NatureTypeEffectiveness effectiveness)
	{
		switch (effectiveness)
		{
			case NatureTypeEffectiveness::NOT_EFFECTIVE:
			{
				return 0.0f;
			}

			case NatureTypeEffectiveness::EFFECTIVE:
			{
				return 1.0f;
			}

			case NatureTypeEffectiveness::OVERLY_EFFECTIVE:
			{
				return 1.2f;
			}

			default:
			{
				return 0.0f;
			}
		}
	}

	inline const char* NatureTypeToString(const NatureType natureType)
	{
		switch (natureType)
		{
			case NatureType::AIR:
			{
				return "Air";
			}

			case NatureType::EARTH:
			{
				return "Earth";
			}

			case NatureType::FIRE:
			{
				return "Fire";
			}

			case NatureType::WATER:
			{
				return "Water";
			}

			default:
			{
				return "None";
			}
		}
	}


	inline const NatureTypeEffectiveness GetOtherNatureTypeEffectiveness(const NatureType thisNatureType, const NatureType otherNatureType)
	{
		switch (otherNatureType)
		{
			case NatureType::AIR:
			{
				if (thisNatureType == NatureType::FIRE)
				{
					return NatureTypeEffectiveness::NOT_EFFECTIVE;
				}

				if (thisNatureType == NatureType::EARTH)
				{
					return NatureTypeEffectiveness::OVERLY_EFFECTIVE;
				}

				return NatureTypeEffectiveness::EFFECTIVE;
			}

			case NatureType::EARTH:
			{
				if (thisNatureType == NatureType::AIR)
				{
					return NatureTypeEffectiveness::NOT_EFFECTIVE;
				}

				if (thisNatureType == NatureType::WATER)
				{
					return NatureTypeEffectiveness::OVERLY_EFFECTIVE;
				}

				return NatureTypeEffectiveness::EFFECTIVE;
			}

			case NatureType::FIRE:
			{
				if (thisNatureType == NatureType::WATER)
				{
					return NatureTypeEffectiveness::NOT_EFFECTIVE;
				}

				if (thisNatureType == NatureType::AIR)
				{
					return NatureTypeEffectiveness::OVERLY_EFFECTIVE;
				}

				return NatureTypeEffectiveness::EFFECTIVE;
			}

			case NatureType::WATER:
			{
				if (thisNatureType == NatureType::EARTH)
				{
					return NatureTypeEffectiveness::NOT_EFFECTIVE;
				}

				if (thisNatureType == NatureType::FIRE)
				{
					return NatureTypeEffectiveness::OVERLY_EFFECTIVE;
				}

				return NatureTypeEffectiveness::EFFECTIVE;
			}

			default:
			{
				return NatureTypeEffectiveness::NOT_EFFECTIVE;
			}
		}
	}
}