#pragma once
#include <string>
#include "creature.h"

namespace Zork
{
	class Player : public Creature
	{
	public:
		Player(const char* newName, 
			   const char* newDescription, 
			   const char* newAttackDescription, 
			   const char* prayerDescription,
			   const char* stunDescription,
			   Stats newStats,
			   Room* room);

		void Update();
		void Go(const std::vector<std::string>& arguments);
		void Take(const std::vector<std::string>& arguments);
		void Look() const;
		void Look(const std::vector<std::string>& arguments) const;
		void Info() const;
		void Examine(const std::vector<std::string>& arguments) const;
		void Equip(const std::vector<std::string>& arguments);
		void Unequip(const std::vector<std::string>& arguments);
		void Put(const std::vector<std::string>& arguments);
		void EnterCombat(const std::vector<std::string>& arguments);
		void CommitStats(const std::vector<std::string>& arguments);
		void Attack();
		void Stun();
		void Prayer();

		const bool HaveRune(NatureType natureType) const;
		const EntityType GetType() const;
	
		~Player();
	protected:
		void Equip(Item* item, bool verbose = true);
		void Unequip(Item* item, bool verbose = true);
	public:
		std::string prayerDescription;
		std::string stunDescription;
		std::list<Item*> runes;
		int statPoints;
	};
}
