#include "exit.h"
#include "room.h"

Zork::Exit::Exit(const char * newName, 
                 const char * newDescription, 
                 Direction newDirection, 
                 Room * newOriginRoom, 
                 Room * newDestinationRoom, 
                 bool isLocked) : Entity(newName, newDescription, (Entity*)newOriginRoom) 
{
    direction = newDirection;
    originRoom = newOriginRoom;
    destinationRoom = newDestinationRoom;
    locked = isLocked;
}

void Zork::Exit::Look() const
{
    if (locked)
    {
        std::cout << "It's locked. " << description << std::endl;  

        return;
    }

    std::cout << "It opens to "  << GetDestinationRoom()->name  << ". " << description << std::endl;     
}

void Zork::Exit::SetParent(Entity* newParent)
{
    Entity::SetParent(newParent);

    // Parent of an Exit cannot be room, because of that I am 
    // checking for runtime errors that may occur:
    try 
    {
        // Since every entity overrides the method GetType,
        // we can get what it actually is with nearly no cost: 
        if (newParent->GetType() != EntityType::ROOM)
        {
            throw newParent->GetType();
        }
    }
    catch (EntityType type)
    {
        std::cout << "Parent of an entity type of Exit must be Room but it is " << EntityTypeToString(type) << std::endl;
    }

    originRoom = (Room*) newParent;
}

const Zork::EntityType Zork::Exit::GetType() const
{
	return EntityType::EXIT;
}

const Zork::Room* Zork::Exit::GetDestinationRoom() const
{
    return destinationRoom;
}

const Zork::Room* Zork::Exit::GetOriginRoom() const
{
    return originRoom;
}

const Zork::Direction Zork::Exit::GetDirection() const
{
	return direction;
}

Zork::Exit::~Exit()
{
}
