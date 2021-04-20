#include "entity.h"

Zork::Entity::Entity(const char* newName, const char* newDescription, Entity* newParent)
{
    name = newName;
    description = newDescription;
    SetParent(newParent);
}

void Zork::Entity::Look() const
{
    std::cout << "Looking at entity: " << std::endl;
    std::cout << name << std::endl << description << std::endl;
}

void Zork::Entity::LookInside() const
{
    Look();

    if (children.size() == 0)
    {
        std::cout << "There is nothing inside it." << std::endl; 
        return;
    }

    std::cout << "Inside there are:" << std::endl; 

    for (std::list<Entity*>::const_iterator iterator = children.begin(); iterator != children.cend(); ++iterator)
    {
        std::cout << "\t" << (*iterator)->name << std::endl;
    } 
}

void Zork::Entity::Update()
{
}

const Zork::EntityType Zork::Entity::GetType() const
{
    return EntityType::ENTITY;
}

void Zork::Entity::SetParent(Entity * newParent)
{
    if (parent != NULL)
    {
		parent->RemoveChild(this);
    }

    if (newParent != NULL)
    {
        newParent->AddChild(this);
    }

    parent = newParent;
}

const Zork::Entity* Zork::Entity::GetParent() const
{
	return parent;
}

const std::list<Zork::Entity*>& Zork::Entity::GetChildren() const
{
	return children;
}

void Zork::Entity::AddChild(Entity* child)
{
    children.push_back(child);
}

void Zork::Entity::RemoveChild(Entity* child) 
{
	children.remove(child);
}

Zork::Entity* Zork::Entity::FindInChildren(const std::string childName) const
{
	for (std::list<Entity*>::const_iterator iterator = children.begin(); iterator != children.cend(); ++iterator)
    {
        if (Util::Equals((*iterator)->name, childName))
        {
            return (*iterator);
        }
    } 

    // If such child could not be found return null:
    return NULL;   
}

Zork::Entity* Zork::Entity::FindInChildren(const std::string childName, EntityType childType) const
{
	for (std::list<Entity*>::const_iterator iterator = children.begin(); iterator != children.cend(); ++iterator)
    {
        if (Util::Equals((*iterator)->name, childName) && (*iterator)->GetType() == childType)
        {
            return (*iterator);
        }
    } 

    // If such child could not be found return null:
    return NULL;   
}

Zork::Entity* Zork::Entity::FindInChildren(EntityType childType) const
{
	for (std::list<Entity*>::const_iterator iterator = children.begin(); iterator != children.cend(); ++iterator)
    {
        if ((*iterator)->GetType() == childType)
        {
            return (*iterator);
        }
    } 

    // If such child could not be found return null:
    return NULL;   
}

Zork::Entity* Zork::Entity::FindInChildren(Entity * child) const
{
	for (std::list<Entity*>::const_iterator iterator = children.begin(); iterator != children.cend(); ++iterator)
    {
        if ((*iterator) == child)
        {
            return (*iterator);
        }
    } 

    // If such child does not exist in children list:
    return NULL;   
}

void Zork::Entity::FindAllInChildren(EntityType childType, std::list<Entity*>* returnedList) const
{
    for (std::list<Entity*>::const_iterator iterator = children.begin(); iterator != children.cend(); ++iterator)
    {
        if ((*iterator)->GetType() == childType)
        {
            returnedList->push_back(*iterator);
        }
    } 
}

const bool Zork::Entity::IsCreature() const
{
    return (GetType() == EntityType::CREATURE || 
            GetType() == EntityType::PLAYER || 
            GetType() == EntityType::NPC);
}

Zork::Entity::~Entity()
{
}
