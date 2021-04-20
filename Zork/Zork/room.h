#pragma once
#include "entity.h"

namespace Zork
{
	class Room : public Entity
	{
	public:			
		Room(const char* name, const char* description);
		
		void Look() const;
		void LookInside() const;
		const EntityType GetType() const;
		
		~Room();
	};
}
