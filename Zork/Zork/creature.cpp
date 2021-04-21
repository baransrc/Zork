#include "creature.h"
#include "item.h"

Zork::Creature::Creature(const char* newName, const char* newDescription, 
			     const char* newAttackDescription, 
				 Room* newRoom, 
				 Stats newStats,
				 NatureType newNatureType) : Entity(newName, newDescription, (Entity*)newRoom)
{
	attackDescription = newAttackDescription;
	stats = newStats;
	natureType = newNatureType; 
	combatTarget = NULL;
	weapon = NULL;
	armor = NULL;

	SetHealth(GetMaxHealth());
}

void Zork::Creature::Update()
{
	if (!IsAlive())
	{
		return;
	}

	if (!PlayerInsideRoom())
	{
		return;
	}
}

void Zork::Creature::Equip(const std::vector<std::string>& arguments)
{
	if (!IsAlive())
	{
		return;
	}

	Item* item = (Item*)FindInChildren(arguments[1], EntityType::ITEM);

	if (item == NULL)
	{
		std::cout << "There is no item in inventory with name " << arguments[1] << std::endl;
		
		return;
	}

	switch (item->GetItemType())
	{
		case ItemType::WEAPON:
		{
			weapon = item;
		}
		break;

		case ItemType::ARMOR:
		{
			armor = item;
		} 
		break;

		default:
		{
			std::cout << item->name << " cannot be equipped." << std::endl;
			
			return;
		}
	}

	std::cout << name << " equipped " << item->name << std::endl;
}

void Zork::Creature::Unequip(const std::vector<std::string>& arguments)
{
	if (!IsAlive())
	{
		return;
	}

	Item* item = (Item*)FindInChildren(arguments[1], EntityType::ITEM);

	if (item == NULL)
	{
		std::cout << "There is no item equipped that has the name " << arguments[1] << std::endl;
		
		return;
	}

	if (item == weapon)
	{
		weapon = NULL;
	} 
	else if (item == armor)
	{
		armor = NULL;
	} 
	else
	{
		std::cout << item->name << " cannot be unequipped since it is not equipped." << std::endl;
	}

	std::cout << name << " unequipped " << item->name << std::endl;
}

void Zork::Creature::Go(const std::vector<std::string>&arguments)
{
}

void Zork::Creature::Take(const std::vector<std::string>& arguments)
{
}

void Zork::Creature::Look(const std::vector<std::string>& arguments) const
{
}

void Zork::Creature::LookInside(const std::vector<std::string>& arguments) const
{
}

void Zork::Creature::Put(const std::vector<std::string>& arguments)
{
}

void Zork::Creature::Attack(const std::vector<std::string>& arguments)
{
	std::string targetName = arguments[1]; 

	Entity* target = (Entity*)(this->GetParent()->FindInChildren(targetName));

	if (!target->IsCreature())
	{
		return;
	}
	
	combatTarget = (Creature*)target;
	
	if (!combatTarget->IsAlive())
	{
		std::cout << combatTarget->name << " is already dead." << std::endl;
		return;
	}

	std::cout << name << " " << attackDescription << " " << combatTarget->name << std::endl;

	combatTarget->TakeDamage(GetAttackAmount(), natureType);
}

void Zork::Creature::PrintInventory() const
{
	if (GetChildren().size() == 0)
    {
        std::cout << "There is nothing inside the inventory of" << name << std::endl; 
        return;
    }

    std::cout << "Inventory of " << name << std::endl; 

    for (std::list<Entity*>::const_iterator iterator = GetChildren().begin(); iterator != GetChildren().cend(); ++iterator)
    {
        std::cout << "\t" << (*iterator)->name << std::endl;
    } 
}

void Zork::Creature::TakeDamage(int takenDamage, NatureType otherNatureType)
{
	Zork::NatureTypeEffectiveness effectiveness = GetOtherNatureTypeEffectiveness(natureType, otherNatureType);
	
	switch (effectiveness)
	{
		case NatureTypeEffectiveness::NOT_EFFECTIVE:
		{
			std::cout << name << " is a " << Zork::NatureTypeToString(natureType) 
				  << " type creature. " << Zork::NatureTypeToString(otherNatureType)
				  << " type spells are not effective." << std::endl;  
		}
		break;

		case NatureTypeEffectiveness::EFFECTIVE:
		{
			std::cout << "It was effective." << std::endl;
		}
		break;

		case NatureTypeEffectiveness::OVERLY_EFFECTIVE:
		{
			std::cout << "It was very effective." << std::endl;
		}
	
		default:
		break;
	}

	float multiplier = GetDamageMultiplierByEffectiveness(effectiveness);
	int multipliedDamage = (int)((float)takenDamage * multiplier); 
	int finalDamage = multipliedDamage - GetDefenceAmount();
	finalDamage = finalDamage < 0 ? 0 : finalDamage;

	AddHealth(-finalDamage);

	std::cout << name << " took " << finalDamage << " damage." << std::endl
			  << name << " has " << currentHealth << " health remaining." << std::endl;  
	
	Die();

	std::cout << std::endl;
}

void Zork::Creature::Die() const
{
	if (IsAlive())
	{
		return;
	}

	std::cout << name << " has died." << std::endl;
}

const Zork::NatureTypeEffectiveness Zork::Creature::GetStunned(NatureType otherNatureType)
{
	Zork::NatureTypeEffectiveness effectiveness = Zork::GetOtherNatureTypeEffectiveness(natureType, otherNatureType);
	

	switch (effectiveness)
	{
		case NatureTypeEffectiveness::NOT_EFFECTIVE:
		{
			std::cout << name << " is a " << NatureTypeToString(natureType) 
				  << " type creature. " << NatureTypeToString(otherNatureType)
				  << " type spells are not effective. Hence," << NatureTypeToString(otherNatureType) 
				  << " Stun was not effective." << std::endl;  
		}
		break;

		case NatureTypeEffectiveness::EFFECTIVE:
		{
			std::cout << NatureTypeToString(otherNatureType) << " Stun was effective." << std::endl;
		}
		break;

		case NatureTypeEffectiveness::OVERLY_EFFECTIVE:
		{
			std::cout << NatureTypeToString(otherNatureType) << " Stun was very effective." << std::endl;
		}
	
		default:
		break;
	}

	return effectiveness;
}

const Zork::EntityType Zork::Creature::GetType() const
{
	return CREATURE;
}

const Zork::Stats Zork::Creature::GetStats() const
{
	return stats;
}

const int Zork::Creature::GetDefenceAmount() const
{
	int defence = stats.defence;

	if (armor != NULL)
	{
		defence += armor->GetStats().defence;
	} 

	if (weapon != NULL)
	{
		defence += weapon->GetStats().defence;
	}

	return Util::RandomNumber((defence * 10), (defence * 15));
}

const int Zork::Creature::GetAttackAmount() const
{
	int attack = stats.attack;

	if (armor != NULL)
	{
		attack += armor->GetStats().attack;
	} 

	if (weapon != NULL)
	{
		attack += weapon->GetStats().attack;
	}

	return Util::RandomNumber((attack * 10), (attack * 15));
}

const int Zork::Creature::GetMaxHealth() const
{
	int health = stats.health;

	if (armor != NULL)
	{
		health += armor->GetStats().health;
	} 

	if (weapon != NULL)
	{
		health += weapon->GetStats().health;
	}

	return health * 10;
}

void Zork::Creature::SetHealth(int newHealth)
{
	int maxHealth = GetMaxHealth();
	
	currentHealth = maxHealth <= newHealth ? maxHealth : newHealth;
	currentHealth = currentHealth < 0 ? 0 : currentHealth;
}

void Zork::Creature::AddHealth(int addition)
{
	int newHealth = currentHealth + addition;
	int maxHealth = GetMaxHealth();
	
	currentHealth = newHealth >= maxHealth ? maxHealth : newHealth;
	currentHealth = currentHealth < 0 ? 0 : currentHealth;
}

const bool Zork::Creature::PlayerInsideRoom() const
{
	return (GetParent()->FindInChildren(Zork::EntityType::PLAYER) != NULL);
}

const bool Zork::Creature::IsAlive() const
{
	return (currentHealth > 0);
}

Zork::Creature::~Creature()
{
}
