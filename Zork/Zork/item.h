#pragma once
#include "entity.h"
#include "item_type.h"
#include "stats.h"

namespace Zork
{
	class Item : public Entity
	{
	public:
		Item(const char* newName, const char* newDescription, Entity* newParent, ItemType newItemType, Stats newStats);

		const EntityType GetType() const;
		const ItemType GetItemType() const;
		const Stats GetStats() const;
		void Look() const;

		~Item();
	private:
		Stats stats;
		ItemType itemType;
	};
}

