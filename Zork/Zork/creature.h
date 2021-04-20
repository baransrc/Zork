#pragma once
#include "entity.h"
#include "nature_type.h"

namespace Zork
{
	class Room;
	class Item;

	class Creature : public Entity
	{
	public: 
		Creature(const char* newName, const char* newDescription, 
			     const char* newAttackDescription, 
				 Room* newRoom, int newHealthMultiplier, 
				 int newAttackMultiplier, 
				 int newDefenceMultiplier, 
				 NatureType newNatureType);
		
		virtual void Update();
		virtual void Equip(const std::vector<std::string>& arguments);
		virtual void Unequip(const std::vector<std::string>& arguments);
		virtual void Go(const std::vector<std::string>& arguments);
		virtual void Take(const std::vector<std::string>& arguments);
		virtual void Look(const std::vector<std::string>& arguments) const;
		virtual void LookInside(const std::vector<std::string>& arguments) const;
		virtual void Put(const std::vector<std::string>& arguments);
		virtual void Attack(const std::vector<std::string>& arguments);
		virtual void PrintInventory() const;		
		virtual void TakeDamage(int takenDamage, NatureType otherNatureType);
		virtual void Die() const;
		virtual const NatureTypeEffectiveness GetStunned(NatureType otherNatureType);
		virtual const EntityType GetType() const;
		virtual const int GetDefenceAmount() const;
		virtual const int GetAttackAmount() const;

		const int GetHealthMultiplier() const;
		const int GetAttackMultiplier() const;
		const int GetDefenceMultiplier() const;

		const int GetMaxHealth() const;
		void SetHealth(int newHealth);
		void AddHealth(int addition); // Can be used to decrease health if given negative integers.
		
		const bool PlayerInsideRoom() const;
		const bool IsAlive() const;
	
		~Creature();
	public:
		std::string attackDescription;
		NatureType natureType;
		Creature* combatTarget;
		Item* weapon;
		Item* armor;
	private:
		int currentHealth;
	protected:
		int healthMultiplier;
		int attackMultiplier;
		int defenceMultiplier;
	};
}

// TODO: Add stun flag and related logic.