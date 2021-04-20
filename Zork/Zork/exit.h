#pragma once
#include "entity.h"
#include "direction.h"

namespace Zork
{
	class Room;

	class Exit : public Entity
	{
	public:
		Exit(const char* newName, const char* newDescription, Direction newDirection, Room* newOriginRoom, Room* newDestinationRoom, bool isLocked);

		void Look() const;
		void SetParent(Entity* newParent);
		const EntityType GetType() const;
		const Room* GetDestinationRoom() const;
		const Room* GetOriginRoom() const;
		const Direction GetDirection() const;

		~Exit();

	public:
		bool locked;
	private:
		Room* originRoom;
		Room* destinationRoom;
		Direction direction;
	};
}

