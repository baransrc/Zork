#pragma once
#include "entity.h"
#include "nature_type.h"
#include "stats.h"

namespace Zork
{
	class Room;
	class Item;

	class Creature : public Entity
	{
	public: 
		Creature(const char* newName, const char* newDescription, 
			     const char* newAttackDescription, 
				 Room* newRoom, 
				 Stats newStats,
				 NatureType newNatureType);
		
		virtual void Update();
		virtual void Go(const std::vector<std::string>& arguments);
		virtual void Take(const std::vector<std::string>& arguments);
		virtual void Look() const;
		virtual void Look(const std::vector<std::string>& arguments) const;
		virtual void Put(const std::vector<std::string>& arguments);
		virtual void Attack();
		virtual void EnterCombat(const std::vector<std::string>& arguments);
		virtual void PrintInventory() const;		
		virtual void TakeDamage(int takenDamage, NatureType otherNatureType);
		virtual void Die() const;
		virtual void Info() const;
		virtual void GetStunned(NatureType otherNatureType);
		virtual const EntityType GetType() const;
		virtual const int GetDefenceAmount() const;
		virtual const int GetAttackAmount() const;
		virtual void SetRoom(const Room* room);

		const Room* GetRoom() const;
		const Stats GetStats() const;
		const int GetCurrentHealth() const;
		const int GetMaxHealth() const;
		const bool PlayerInsideRoom() const;
		const bool IsAlive() const;

		void Equip(const std::vector<std::string>& arguments);
		void Unequip(const std::vector<std::string>& arguments);
		void SetHealth(int newHealth);
		void AddHealth(int addition); // Can be used to decrease health if given negative integer as input.
			
		~Creature();
	protected:
		virtual void Equip(Item* item, bool verbose = true);
		virtual void Unequip(Item* item, bool verbose = true);

	private:
		void DropAll();

	public:
		std::string attackDescription;
		NatureType natureType;
		Creature* combatTarget;
		Item* weapon;
		Item* armor;
	protected:
		Stats stats;
	private:
		int currentHealth;
		int stunLock;
	};
}

// TODO: Add stun flag and related logic.