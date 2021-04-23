#include "npc.h"

Zork::Npc::Npc(const char * newName, 
			   const char * newDescription, 
			   const char * newAttackDescription, 
			   Room * newRoom, 
			   Stats newStats, 
			   NatureType newNatureType, 
			   bool newAutoAttack) : Creature(newName, newDescription, newAttackDescription, newRoom, newStats, newNatureType)
{
	autoAttack = newAutoAttack;
}

void Zork::Npc::Update()
{
	if (autoAttack)
	{
		if (PlayerInsideRoom() && combatTarget == NULL)
		{
			combatTarget = (Creature*)(GetParent()->FindInChildren(EntityType::PLAYER));
			
			if (combatTarget != NULL)
			{
				combatTarget->combatTarget = this;
			}
		}
	}

	Creature::Update();
}

const Zork::EntityType Zork::Npc::GetType() const
{
	return EntityType::NPC;
}

Zork::Npc::~Npc()
{
}
