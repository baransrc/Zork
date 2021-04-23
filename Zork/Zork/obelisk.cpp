#include "obelisk.h"
#include "exit.h"
#include "item.h"
#include "room.h"

Zork::Obelisk::Obelisk(
	const char * newName, 
	const char * newDescription, 
	Room * newRoom, 
	Exit * unlockedExit) : Entity(newName, newDescription, (Entity*)newRoom)
{
	exit = unlockedExit;
}

const bool Zork::Obelisk::AllCavitiesFilled() const
{
	for (int i = 0; i < 4; ++i)
	{
		if (runes[i] == NULL)
		{
			return false;
		}
	}

	return true;
}

const Zork::EntityType Zork::Obelisk::GetType() const
{
	return EntityType::OBELISK;
}

const Zork::Room* Zork::Obelisk::GetRoom() const
{
	try
	{
		if (GetParent()->GetType() != EntityType::ROOM)
		{
			throw (GetParent()->GetType());
		}
	}
	catch (EntityType type)
	{
		std::cout << "Parent of " << name << " is of type: " << EntityTypeToString(type)
			      << "Parent of a obelisk cannot be anything other than room." << std::endl;
	}

	return (Room*)GetParent();
}

void Zork::Obelisk::AddChild(Entity* child)
{
	if (child->GetType() != EntityType::ITEM)
	{
		std::cout << "This does not fit any of the cavities." << std::endl;
		
		return;
	}

	bool placedRune = PlaceRune((Item*)child);

	if (!placedRune)
	{
		std::cout << "This does not fit any of the cavities." << std::endl;

		return;
	}

	Entity::AddChild(child);
}

void Zork::Obelisk::RemoveChild(Entity* child)
{
	if (child->GetType() != EntityType::ITEM)
	{
		std::cout << "This is not inside cavities." << std::endl;

		return;
	}

	bool unplacedRune = UnplaceRune((Item*)child);

	if (!unplacedRune)
	{
		std::cout << "This is not inside cavities." << std::endl;

		return;
	}

	Entity::RemoveChild(child);
}

bool Zork::Obelisk::PlaceRune(Item* item)
{
	// Item is not a rune:
	if (item->GetItemType() != ItemType::RUNE)
	{
		return false;
	}

	// A rune with same type already placed:
	if (runes[item->GetNatureType()] != NULL)
	{
		return false;
	}

	runes[item->GetNatureType()] = item;

	return true;
}

bool Zork::Obelisk::UnplaceRune(Item * item)
{
	// Item is not a rune:
	if (item->GetItemType() != ItemType::RUNE)
	{
		return false;
	}

	// Item is not one of runes inside:
	if (item != runes[item->GetNatureType()])
	{
		return false;
	}

	runes[item->GetNatureType()] = NULL;

	return true;
}

void Zork::Obelisk::Info() const
{
	std::cout << name << std::endl << description << std::endl;

	bool filled = AllCavitiesFilled();
	
	if (filled)
	{
		std::cout << "The magic circle around it is active!" << std::endl;
	}
	else
	{
		std::cout << "Cavities from top to bottom: " << std::endl;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (runes[i] == NULL)
		{
			std::cout << "A " << NatureTypeShapeFromInt(i) << " shaped cavity." << std::endl;
			continue;
		}
		
		std::cout << "Shining " << runes[i]->name << std::endl;
 	}
}

void Zork::Obelisk::Update()
{
	if (!exit->locked)
	{
		return;
	}

	if (AllCavitiesFilled())
	{
		exit->locked = false;

		std::cout << std::endl << "A new door is unlocked at the "
			<< DirectionToString(exit->GetDirection())
			<< " of the room." << std::endl;
		
		return;
	}

	exit->locked = true;
}

Zork::Obelisk::~Obelisk()
{
}
