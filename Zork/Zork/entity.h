#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "util.h"
#include "entity_type.h"

namespace Zork
{
	class Entity
	{
	public:
		Entity(const char* newName, const char* newDescription, Entity* newParent);
		
		virtual void Look() const;
		virtual void LookInside() const;
		virtual void Update();
		virtual const EntityType GetType() const;

		virtual void SetParent(Entity* newParent);
		void AddChild(Entity* child);
		void RemoveChild(Entity* child);
		const Entity* GetParent() const;
		const std::list<Entity*>& GetChildren() const;

		Entity* FindInChildren(const std::string childName) const;
		Entity* FindInChildren(const std::string childName, EntityType childType) const;
		Entity* FindInChildren(EntityType childType) const;
		Entity* FindInChildren(Entity* child) const;
		void FindAllInChildren(EntityType childType, std::list<Entity*>* returnedList) const;

		const bool IsCreature() const; 
		
		virtual ~Entity();
	public:
		std::string name;
		std::string description;
	private:
		Entity* parent;
		std::list<Entity*> children;
	};
}

