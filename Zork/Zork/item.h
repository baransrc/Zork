#pragma once
#include "entity.h"
#include "item_type.h"
#include "nature_type.h"
#include "stats.h"

namespace Zork
{
	class Item : public Entity
	{
	public:
		Item(const char* newName, const char* newDescription, Entity* newParent, ItemType newItemType, Stats newStats, NatureType newNatureType);

		const bool CanContainChildren() const;
		const EntityType GetType() const;
		const ItemType GetItemType() const;
		const NatureType GetNatureType() const;
		const Stats GetStats() const;
		void Info() const;
		void Look() const;

		~Item();
	private:
		Stats stats;
		ItemType itemType;
		NatureType natureType;
	};
}

