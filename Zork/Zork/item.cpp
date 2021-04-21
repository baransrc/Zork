#include "item.h"

Zork::Item::Item(const char * newName, 
                 const char * newDescription, 
                 Entity * newParent, 
                 ItemType newItemType,
                 Stats newStats) : Entity(newName, newDescription, newParent)
{
    itemType = newItemType;
    stats = newStats;
}

const Zork::EntityType Zork::Item::GetType() const
{
	return EntityType::ITEM;
}

const Zork::ItemType Zork::Item::GetItemType() const
{
	return itemType;
}

const Zork::Stats Zork::Item::GetStats() const
{
	return stats;
}

void Zork::Item::Look() const
{
    std::cout << name << std::endl << description << std::endl;
}

Zork::Item::~Item()
{
}
