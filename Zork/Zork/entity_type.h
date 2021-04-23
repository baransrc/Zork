#pragma once

namespace Zork
{
	enum EntityType
	{
		ENTITY,
		ROOM,
		EXIT,
		ITEM,
		CREATURE,
		NPC,
		PLAYER,
		OBELISK,
	};

	inline const char* EntityTypeToString(const EntityType type)
	{
		switch (type)
		{
			case EntityType::ENTITY:
			{
				return "Entity";
			}

			case EntityType::ROOM:
			{
				return "Room";
			}

			case EntityType::EXIT:
			{
				return "Exit";
			}

			case EntityType::ITEM:
			{
				return "Item";
			}

			case EntityType::CREATURE:
			{
				return "Creature";
			}

			case EntityType::NPC:
			{
				return "NPC";
			}

			case EntityType::PLAYER:
			{
				return "Player";
			}

			case EntityType::OBELISK:
			{
				return "Obelisk";
			}

			default:
			{
				return "NONE";
			}
		}
	}
}
