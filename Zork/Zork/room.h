#pragma once
#include "entity.h"
#include "direction.h"

namespace Zork
{
	class Exit;

	class Room : public Entity
	{
	public:			
		Room(const char* name, const char* description);
		
		void Look() const;
		const EntityType GetType() const;
		const Exit* GetExit(Direction direction) const;

		~Room();
	};
}
