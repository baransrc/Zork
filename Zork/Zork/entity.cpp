#include "entity.h"

Zork::Entity::Entity(const char* newName, const char* newDescription, Entity* newParent)
{
    this->name = newName;
    this->description = newDescription;
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

Zork::EntityType Zork::Entity::GetType() const
{
    return EntityType::ENTITY;
}

void Zork::Entity::SetParent(Entity * newParent)
{
    if (parent != NULL)
    {
        parent->GetChildren()->remove(this);
    }

    if (newParent != NULL)
    {
        newParent->AddChild(this);
    }

    parent = newParent;
}

Zork::Entity* Zork::Entity::GetParent()
{
	return parent;
}

std::list<Zork::Entity*>* Zork::Entity::GetChildren()
{
	return &children;
}

void Zork::Entity::AddChild(Entity* child)
{
    children.push_back(child);
}

Zork::Entity* Zork::Entity::FindInChildren(const std::string childName, EntityType childType) const
{
	for (std::list<Entity*>::const_iterator iterator = children.begin(); iterator != children.cend(); ++iterator)
    {
        if (Util::Equals((*iterator)->name, childName) && (*iterator)->type == childType)
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
        if ((*iterator)->type == childType)
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
        if ((*iterator)->type == childType)
        {
            returnedList->push_back(*iterator);
        }
    } 
}

Zork::Entity::~Entity()
{
}
