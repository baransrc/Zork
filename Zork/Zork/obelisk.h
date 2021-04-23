#pragma once
#include "entity.h"

namespace Zork
{
	class Exit;
	class Item;
	class Room;

	class Obelisk : public Entity
	{
	public:
		Obelisk(
			const char* newName, 
			const char* newDescription, 
			Room* newRoom, 
			Exit* unlockedExit
		);

		const bool AllCavitiesFilled() const;
		const EntityType GetType() const;
		const Room* GetRoom() const;
		void AddChild(Entity* child);
		void RemoveChild(Entity* child);
		void Info() const;
		void Update();

		
		~Obelisk();
	private:
		bool PlaceRune(Item* item);
		bool UnplaceRune(Item* item);
	private:
		Exit* exit;
		Item* runes[4];
	};
}

