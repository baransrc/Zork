#include "room.h"
#include "creature.h"
#include "exit.h"

Zork::Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
}

void Zork::Room::Look() const
{
    std::cout << std::endl << "You are in " << name << ". " << description << std::endl;

	std::list<Entity*> childrenReference = GetChildren();
	std::string printBuffer = "";

    // Creatures:
	for (std::list<Entity*>::const_iterator iterator = childrenReference.begin(); iterator != childrenReference.cend(); ++iterator)
	{
		if ((*iterator)->IsCreature())
		{
			if ((*iterator)->GetType() == EntityType::PLAYER)
			{
				continue;
			}

			bool isDead = !(((Creature*)(*iterator))->IsAlive());

			if (isDead)
			{
				std::cout << "A dead body of " << (*iterator)->name << " lies on the ground." << std::endl;
			}
			else
			{
				std::cout << "A creature named " << (*iterator)->name << " wanders around. It may be dangerous." << std::endl;
			}
		}
	}

	// Obelisks:
	for (std::list<Entity*>::const_iterator iterator = childrenReference.begin(); iterator != childrenReference.cend(); ++iterator)
	{
		if ((*iterator)->GetType() == EntityType::OBELISK)
		{
			std::cout << "There is a " << (*iterator)->name << ". " << (*iterator)->description << std::endl;
		}
	}

    // Items:
	std::string itemsPrintBuffer = "";
	for (std::list<Entity*>::const_iterator iterator = childrenReference.begin(); iterator != childrenReference.cend(); ++iterator)
	{
		if ((*iterator)->GetType() == EntityType::ITEM)
		{
			itemsPrintBuffer += "  " + (*iterator)->name + "\n";
		}
	}
	// If there are items, print:
	if (!Util::Equals("", itemsPrintBuffer, false))
	{
		std::cout << "Inside there are:" << std::endl << itemsPrintBuffer;
	}
	
    // Exits:
	for (std::list<Entity*>::const_iterator iterator = childrenReference.begin(); iterator != childrenReference.cend(); ++iterator)
	{
		// Look if it is of type Exit:
		if ((*iterator)->GetType() == EntityType::EXIT)
		{
			Exit* exit = (Exit*)(*iterator);

			std::cout << "To the " << Zork::DirectionToString(exit->GetDirection()) << " you see a " 
                  << "\"" << exit->name  << "\". " << exit->description << std::endl; 
		}
	}

}


const Zork::EntityType Zork::Room::GetType() const
{
    return Zork::EntityType::ROOM;
}

const Zork::Exit* Zork::Room::GetExit(Direction direction) const
{
	std::list<Entity*> childrenReference = GetChildren();

	for (std::list<Entity*>::const_iterator iterator = childrenReference.begin(); iterator != childrenReference.cend(); ++iterator)
	{
		if ((*iterator)->GetType() == EntityType::EXIT && ((Exit*)(*iterator))->GetDirection() == direction)
		{
			return (Exit*)(*iterator);		
		}
	}

	return NULL;
}

Zork::Room::~Room()
{
}