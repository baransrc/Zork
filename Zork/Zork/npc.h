#pragma once
#include "creature.h"

namespace Zork
{
	class Npc : public Creature
	{
	public:
		Npc(const char* newName, 
			const char* newDescription,
			const char* newAttackDescription,
			Room* newRoom,
			Stats newStats,
			NatureType newNatureType, 
			bool newAutoAttack);

		void Update();

		const EntityType GetType() const;

		~Npc();
	
	private:
		bool autoAttack;

	};
}