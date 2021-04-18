#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "util.h"

namespace Zork
{
	enum EntityType
	{
		ENTITY,
		ROOM,
		EXIT,
		ITEM,
		CREATURE,
		PLAYER
	};

	class Entity
	{
	public:
		Entity(const char* newName, const char* newDescription, Entity* newParent);
		
		virtual void Look() const;
		virtual void LookInside() const;
		virtual void Update();
		virtual EntityType GetType() const;

		void SetParent(Entity* newParent);
		Entity* GetParent();

		std::list<Entity*>* GetChildren();
		void AddChild(Entity* child);

		Entity* FindInChildren(const std::string childName, EntityType childType) const;
		Entity* FindInChildren(EntityType childType) const;
		Entity* FindInChildren(Entity* child) const;
		void FindAllInChildren(EntityType childType, std::list<Entity*>* returnedList) const;
		
		virtual ~Entity();
	public:
		EntityType type;
		std::string name;
		std::string description;
	private:
		Entity* parent;
		std::list<Entity*> children;
	};
}

