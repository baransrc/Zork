#include "item.h"

Zork::Item::Item(const char * newName, 
                 const char * newDescription, 
                 Entity * newParent, 
                 ItemType newItemType,
                 Stats newStats,
				 NatureType newNatureType) : Entity(newName, newDescription, newParent)
{
	natureType = newNatureType;
    itemType = newItemType;
    stats = newStats;
}

const bool Zork::Item::CanContainChildren() const
{
	return (GetItemType() == ItemType::CONTAINER);
}

const Zork::EntityType Zork::Item::GetType() const
{
	return EntityType::ITEM;
}

const Zork::ItemType Zork::Item::GetItemType() const
{
	return itemType;
}

const Zork::NatureType Zork::Item::GetNatureType() const
{
	return natureType;
}

const Zork::Stats Zork::Item::GetStats() const
{
	return stats;
}

void Zork::Item::Info() const
{
	std::cout << std::endl << name << std::endl;
	std::cout << "  Item Type: " << ItemTypeToString(GetItemType()) << std::endl;
	std::cout << "  Nature: " << NatureTypeToString(GetNatureType()) << std::endl;

	if (stats.attack + stats.defence + stats.health > 0)
	{
		std::cout << "  Modifiers:" << std::endl;

		if (stats.attack > 0)
		{
			std::cout << "    Attack:  +" << stats.attack << std::endl;
		}

		if (stats.defence > 0)
		{
			std::cout << "    Defence: +" << stats.defence << std::endl;
		}

		if (stats.health > 0)
		{
			std::cout << "    Health:  +" << stats.health << std::endl;
		}
	}

	std::list<Entity*> childrenReference = GetChildren();
 
	if (childrenReference.size() > 0)
	{
		std::cout << "  Inside it there are:" << std::endl;
		
		for (
			std::list<Entity*>::const_iterator iterator = childrenReference.begin(); 
			iterator != childrenReference.cend(); 
			++iterator
			)
		{
			std::cout << "    " << (*iterator)->name << ". " << (*iterator)->description << std::endl;;
		}
	}
}

void Zork::Item::Look() const
{
    std::cout << name << std::endl << description << std::endl;
}

Zork::Item::~Item()
{
}
