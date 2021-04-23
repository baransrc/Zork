#include "creature.h"
#include "item.h"

Zork::Creature::Creature(const char* newName, 
					     const char* newDescription,
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
	stunLock = 0;

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

	if (combatTarget == NULL)
	{
		return;
	}

	if (!GetParent()->FindInChildren(combatTarget))
	{
		combatTarget = NULL;
		return;
	}

	if (stunLock > 0)
	{
		std::cout << std::endl << name 
			      << " is stunned. It will not be available to attack for "
				  << stunLock << " turns." << std::endl;
		
		stunLock--;

		return;
	}

	Attack();
}

void Zork::Creature::Equip(Item* item, bool verbose)
{
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
			if (verbose)
			{
				std::cout << std::endl << name << ": " << item->name << " cannot be equipped." << std::endl;
			}

			return;
		}
	}

	if (verbose)
	{
		std::cout << std::endl << name << " equipped " << item->name << std::endl;
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
		std::cout << name << ": There is no item in inventory with name " << arguments[1] << std::endl;

		return;
	}

	Equip(item);
}

void Zork::Creature::Unequip(Item* item, bool verbose)
{
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
		if (verbose)
		{
			std::cout << std::endl << item->name 
				      << " cannot be unequipped since it is not equipped." << std::endl;
		}

		return;
	}

	if (verbose)
	{
		std::cout << std::endl << name 
			      << " unequipped " << item->name << std::endl;
	}	
}

void Zork::Creature::DropAll()
{
	std::list<Entity*> childrenReference = GetChildren();

	if (childrenReference.size() <= 0)
	{
		return;
	}

	std::cout << std::endl << name << " dropped: " << std::endl;

 	for (
			std::list<Entity*>::iterator iterator = childrenReference.begin();
			iterator != childrenReference.end();
			++iterator 
		)
	{
		// If it is an item (Hopefully it will be an item everytime)
		// try unequipping it silently, and set its parent to room.
		if ((*iterator)->GetType() == EntityType::ITEM)
		{
			Unequip((Item*)(*iterator), false);
		}

		// Drop it to room:
		(*iterator)->SetParent((Entity*)GetRoom());

		std::cout << "  " << (*iterator)->name << std::endl;
	}
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
		std::cout << std::endl << "There is no item equipped that has the name " << arguments[1] << std::endl;

		return;
	}

	Unequip(item);
}

void Zork::Creature::Go(const std::vector<std::string>&arguments)
{
}

void Zork::Creature::Take(const std::vector<std::string>& arguments)
{
}

void Zork::Creature::Look() const
{
	std::cout << std::endl << name << std::endl << description << std::endl;
}

void Zork::Creature::Look(const std::vector<std::string>& arguments) const
{
}

void Zork::Creature::Put(const std::vector<std::string>& arguments)
{
}

void Zork::Creature::Attack()
{
	if (!IsAlive() || !combatTarget->IsAlive())
	{
		combatTarget->combatTarget = NULL;
		combatTarget = NULL;
	}

	int damage = GetAttackAmount();

	if (PlayerInsideRoom())
	{
		std::cout << std::endl << name << " " << attackDescription <<  " " << combatTarget->name << std::endl;
	}

	combatTarget->TakeDamage(damage, natureType);

	if (combatTarget->combatTarget == NULL)
	{
		combatTarget->combatTarget = this;
	}
}

void Zork::Creature::EnterCombat(const std::vector<std::string>& arguments)
{
}

void Zork::Creature::PrintInventory() const
{
	if (GetChildren().size() == 0)
	{
		std::cout << std::endl << "There is nothing inside the inventory of " << name << std::endl;
		return;
	}

	std::cout << std::endl << "Inventory of " << name << std::endl;

	for (std::list<Entity*>::const_iterator iterator = GetChildren().begin(); iterator != GetChildren().cend(); ++iterator)
	{
		std::cout << "  " << (*iterator)->name << std::endl;
	}
}

void Zork::Creature::TakeDamage(int takenDamage, NatureType otherNatureType)
{
	Zork::NatureTypeEffectiveness effectiveness = GetOtherNatureTypeEffectiveness(natureType, otherNatureType);

	switch (effectiveness)
	{
	case NatureTypeEffectiveness::NOT_EFFECTIVE:
	{
		std::cout << std::endl << name << " is a " << Zork::NatureTypeToString(natureType)
			<< " type creature. " << Zork::NatureTypeToString(otherNatureType)
			<< " type spells are not effective." << std::endl;
	}
	break;

	case NatureTypeEffectiveness::EFFECTIVE:
	{
		std::cout << std::endl << "It was effective." << std::endl;
	}
	break;

	case NatureTypeEffectiveness::OVERLY_EFFECTIVE:
	{
		std::cout << std::endl << "It was very effective." << std::endl;
	}

	default:
		break;
	}

	float multiplier = GetDamageMultiplierByEffectiveness(effectiveness);
	int multipliedDamage = (int)((float)takenDamage * multiplier);
	int finalDamage = multipliedDamage - GetDefenceAmount();
	finalDamage = finalDamage < 0 ? 0 : finalDamage;

	AddHealth(-finalDamage);

	std::cout << std::endl << name << " took " << finalDamage << " damage." << std::endl
		<< name << " has " << currentHealth << " health remaining." << std::endl;

	Die();

	if (!IsAlive())
	{
		DropAll();
	}
}

void Zork::Creature::Die() const
{
	if (IsAlive())
	{
		return;
	}

	std::cout << name << " has died." << std::endl;
}

void Zork::Creature::Info() const
{
	Look();

	Stats stats = GetStats();
	
	int attackModifiers = 0;
	int defenceModifiers = 0;
	int healthModifiers = 0;

	if (armor != NULL)
	{
		Stats armorStats = armor->GetStats();
		attackModifiers += armorStats.attack;
		defenceModifiers += armorStats.defence;
		healthModifiers += armorStats.health;
	}

	if (weapon != NULL)
	{
		Stats weaponStats = weapon->GetStats();
		attackModifiers += weaponStats.attack;
		defenceModifiers += weaponStats.defence;
		healthModifiers += weaponStats.health;
	}

	std::cout << std::endl << "Health: " << GetCurrentHealth() << " out of " << GetMaxHealth() << std::endl;
	std::cout << "Stats:" << std::endl;
	std::cout << "  Attack:  " << stats.attack << "( +" << attackModifiers << " )" << std::endl;
	std::cout << "  Defence: " << stats.defence << "( +" << defenceModifiers << " )" << std::endl;
	std::cout << "  Health:  " << stats.health << "( +" << healthModifiers << " )" << std::endl;

	if (armor != NULL)
	{
		armor->Info();
	}

	if (weapon != NULL)
	{
		weapon->Info();
	}
}

void Zork::Creature::GetStunned(NatureType otherNatureType)
{
	Zork::NatureTypeEffectiveness effectiveness = Zork::GetOtherNatureTypeEffectiveness(natureType, otherNatureType);

	switch (effectiveness)
	{
		case NatureTypeEffectiveness::NOT_EFFECTIVE:
		{
			std::cout << std::endl << name << " is a " << NatureTypeToString(natureType)
					  << " type creature. " << NatureTypeToString(otherNatureType)
				      << " type spells are not effective. Hence, " << NatureTypeToString(otherNatureType)
				      << " Stun was not effective." << std::endl;
		}
		break;

		case NatureTypeEffectiveness::EFFECTIVE:
		{
			stunLock += 1;
			std::cout << std::endl << "Stun was effective." << name
				      << " will not be avaliable to attack for " 
				      << stunLock << " turns." << std::endl;
		}
		break;

		case NatureTypeEffectiveness::OVERLY_EFFECTIVE:
		{
			stunLock += 2;
			std::cout << std::endl << "Stun was effective." << name
				<< " will not be avaliable to attack for "
				<< stunLock << " turns." << std::endl;
		}

		default:
			break;
	}
}

const Zork::EntityType Zork::Creature::GetType() const
{
	return CREATURE;
}

const Zork::Room* Zork::Creature::GetRoom() const
{
	try
	{
		if (GetParent()->GetType() != EntityType::ROOM)
		{
			throw (GetParent()->GetType());
		}
	}
	catch (EntityType type)
	{
		std::cout << std::endl << "Parent of " << name << " is of type: " << EntityTypeToString(type)
			<< "Parent of a creature cannot be anything other than room." << std::endl;
	}

	return (Room*)GetParent();
}

const Zork::Stats Zork::Creature::GetStats() const
{
	return stats;
}

const int Zork::Creature::GetCurrentHealth() const
{
	return currentHealth;
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

	return Util::RandomNumber((defence * 3), (defence * 6));
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

void Zork::Creature::SetRoom(const Room* room)
{
	SetParent((Entity*)room);
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
