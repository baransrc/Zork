#include <algorithm>
#include "player.h"
#include "item_type.h"
#include "item.h"
#include "room.h"
#include "exit.h"

Zork::Player::Player(const char* newName, 
                     const char* newDescription, 
					 const char* newAttackDescription,
                     const char* newPrayerDescription, 
                     const char* newStunDescription, 
                     Stats newStats, 
                     Room* room, 
					 Room* newEndRoom) : Creature(newName, newDescription, newAttackDescription, room, newStats, NatureType::NONE)
{
	prayerDescription = newPrayerDescription;
	stunDescription = newStunDescription;
	endRoom = newEndRoom;
}

void Zork::Player::Update()
{
	// Do Nothing.
}

void Zork::Player::Equip(Item* item, bool verbose)
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

		case ItemType::RUNE:
		{
			runes.push_back(item);
		}
		break;

		default:
		{
			if (verbose)
			{
				std::cout << std::endl << name << ": " 
					      << item->name << " cannot be equipped." << std::endl;
			}

			return;
		}
	}

	if (verbose)
	{
		std::cout << std::endl << name << " equipped " << item->name << std::endl;
	}
}

void Zork::Player::Unequip(Item* item, bool verbose)
{
	bool unequippedSomething = false;

	if (item == weapon)
	{
		weapon = NULL;
		unequippedSomething = true;
	}
	else if (item == armor)
	{
		armor = NULL;
		unequippedSomething = true;
	}
	else if (item->GetItemType() == ItemType::RUNE)
	{
		for (std::list<Item*>::const_iterator iterator = runes.begin(); iterator != runes.cend(); ++iterator)
		{
			if (item == (*iterator))
			{
				runes.remove(item);
				unequippedSomething = true;
				break;
			}
		}
	}

	if (!verbose)
	{
		return;
	}

	if (!unequippedSomething)
	{
		std::cout << std::endl << item->name 
			      << " cannot be unequipped since it is not equipped." << std::endl;
		return;
	}

	std::cout << std::endl << name << " unequipped " << item->name << std::endl;
}

void Zork::Player::Go(const std::vector<std::string>& arguments)
{
	if (!IsAlive())
	{
		return;
	}

	Direction direction = Direction::EAST;

	if (Util::Equals(arguments[1], DirectionToString(Direction::EAST), false))
	{
		direction = Direction::EAST;
	}
	else if (Util::Equals(arguments[1], DirectionToString(Direction::WEST), false))
	{
		direction = Direction::WEST;
	}
	else if (Util::Equals(arguments[1], DirectionToString(Direction::NORTH), false))
	{
		direction = Direction::NORTH;
	}
	else if (Util::Equals(arguments[1], DirectionToString(Direction::SOUTH), false))
	{
		direction = Direction::SOUTH;
	}
	else
	{
		std::cout << std::endl << "Cannot go to \"" << arguments[1] 
			      << "\" it is not a direction." << std::endl;
		return;
	}

	const Exit* exit = GetRoom()->GetExit(direction);

	if (exit == NULL)
	{
		std::cout << std::endl << name << ": I cannot go " << DirectionToString(direction)
			<< " there is nothing there." << std::endl;

		return;
	}

	if (exit->locked)
	{
		std::cout << std::endl << "You cannot go " << DirectionToString(direction)
			      << " " << exit->name << " is locked." << std::endl;

		return;
	}

	SetRoom(exit->GetDestinationRoom());

	GetRoom()->Look();
}

void Zork::Player::Take(const std::vector<std::string>& arguments)
{
	// There are two different options for take command:
	// First one is tokenized as TAKE ENTITY_NAME, and 
	// in that case, an entity with name ENTITY_NAME is 
	// searched in current room and if it is an item, 
	// it's parent will be set to this player.
	// Second option is TAKE ENTITY_NAME_0 FROM ENTITY_NAME_1.
	// in this case an entity with name ENTITY_NAME_1 will be 
	// searched. If ENTITY_NAME_1 is item, then firstly, 
	// search will be perfomed in current room for it, if found, 
	// inside that item, a search will be perfomed for ENTITY_NAME_0

	switch (arguments.size())
	{
		// First case described above:
		case 2:
		{
			if (Util::Equals(arguments[1], "all", false))
			{
				std::list<Entity*> allItems;
				
				((Entity*)GetRoom())->FindAllInChildren(EntityType::ITEM, &allItems);

				if (allItems.size() <= 0)
				{
					std::cout << std::endl << name 
						      << ": There is no item in current room." << std::endl;

					return;
				}

				for (
					std::list<Entity*>::iterator it = allItems.begin();
					it != allItems.end();
					++it
					)
				{
					(*it)->SetParent(this);

					std::cout << std::endl << name << " took " << (*it)->name << std::endl;
				}

				return;
			}

			// Look for item in current room:
			Item* item = (Item*)(GetParent()->FindInChildren(arguments[1], EntityType::ITEM));

			if (item == NULL)
			{
				std::cout << std::endl << name << ": There is no item named \""
					      << arguments[1] << "\" in current room." << std::endl;
				return;
			}

			item->SetParent(this);

			std::cout << std::endl << name << " took " << item->name << std::endl;
		}
		break;

		// Second case described above:
		case 4:
		{
			// Look for entity in the current room.
			Entity* parent = GetParent()->FindInChildren(arguments[3]);
			
			// If it is not in the room, search it inside inventory as item.
			if (parent == NULL)
			{
				parent = FindInChildren(arguments[3], EntityType::ITEM);
			}

			// If no such entity exists in inventory:
			if (parent == NULL)
			{
				std::cout << std::endl << name << ":I couldn't find the item named \""
					      << arguments[3] << "\". " << std::endl;
				return;
			}

			// If finded entity is not an item nor an obelisk:
			if (parent->GetType() != EntityType::ITEM && parent->GetType() != EntityType::OBELISK)
			{
				std::cout << std::endl << name << ":I couldn't find the item named \""
					<< arguments[3] << "\". " << std::endl;
				return;
			}

			Item* childItem = (Item*)parent->FindInChildren(arguments[1], EntityType::ITEM);

			if (childItem == NULL)
			{
				std::cout << std::endl << name << ": I couldn't find the item named \"" 
					      << arguments[3] << "\" inside \"" << parent->name 
					      << "\"." << std::endl;
				return;
			}

			childItem->SetParent(this);

			std::cout << std::endl << name << " took " << childItem->name << std::endl;
		}
		break;

		// If given arguments does not met with the cases stated above:
		default:
		{
			std::cout << std::endl << name << ": I'm not sure how to respond to that command."
				      << std::endl;
		}
		break;
	}
}

void Zork::Player::Look() const
{
	Creature::Look();
}

void Zork::Player::Look(const std::vector<std::string>& arguments) const
{
	switch (arguments.size())
	{
		// If the argument is just "LOOK", info of current room will be printed.
		case 1:
		{
			GetParent()->Look();
		}
		break;

		// If the arguments is in the form of "LOOK ENTITY_NAME", an entity with name
		// ENTITY_NAME will be searched in the current room.
		case 2:
		{
			if (Util::Equals(arguments[1], "me", false) ||
				Util::Equals(arguments[1], "player", false) ||
				Util::Equals(arguments[1], "character", false) ||
				Util::Equals(arguments[1], name, false)
				)
			{
				Look();
			}

			// Look if such entity exists in current room:
			Entity* entity = GetParent()->FindInChildren(arguments[1]);

			// If it does not exist in current room look for it inside inventory:
			if (entity == NULL)
			{
				entity = FindInChildren(arguments[1]);
			}

			if (entity == NULL)
			{
				std::cout << std::endl << "I'm not sure what to look at. I couldn't find "
						  << arguments[1] << "." << std::endl;
				
				return;
			}

			entity->Look();
		}
		break;

		// If this arguments are invalid.
		default:
		{
			std::cout << std::endl 
					  << "All I can understand is you want me to look at something." << std::endl;
		}
		break;
	}
}

void Zork::Player::Info() const
{
	Creature::Info();
	
	if (runes.size() > 0)
	{
		std::cout << "Runes: " << std::endl;
		
		for (
			std::list<Item*>::const_iterator iterator = runes.begin(); 
			iterator != runes.cend(); 
			++iterator
			)
		{
			std::cout << "  " << (*iterator)->name << " (" 
					  << NatureTypeToString((*iterator)->GetNatureType()) << ")" << std::endl; 
		}
	}

	std::cout << name << " has " << statPoints << " uncommitted stat points." << std::endl;
}

void Zork::Player::Examine(const std::vector<std::string>& arguments) const
{
	switch (arguments.size())
	{
		// If the arguments is in the form of "EXAMINE ENTITY_NAME", an entity with name
		// ENTITY_NAME will be searched in the current room.
		case 2:
		{
			if (
				Util::Equals(arguments[1], "me", false) ||
				Util::Equals(arguments[1], "player", false) ||
				Util::Equals(arguments[1], "character", false) ||
				Util::Equals(arguments[1], name, false)
			   )
			{
				Info();
				return;
			}

			// Look if such entity exists in current room:
			Entity* entity = GetParent()->FindInChildren(arguments[1]);

			// If it does not exist in current room look for it inside inventory:
			if (entity == NULL)
			{
				entity = FindInChildren(arguments[1]);
			}

			if (entity == NULL)
			{
				std::cout << std::endl << name << ": I'm not sure what to examine. I couldn't find "
					<< arguments[1] << " here." << std::endl;

				return;
			}

			entity->Info();
		}
		break;

		// If this arguments are invalid.
		default:
		{
			std::cout << std::endl << name
				<< ": All I can understand is you want me examine something." << std::endl;
		}
		break;
	}
}

void Zork::Player::Equip(const std::vector<std::string>& arguments)
{
	Creature::Equip(arguments);
}

void Zork::Player::Unequip(const std::vector<std::string>& arguments)
{
	Creature::Unequip(arguments);
}

void Zork::Player::Put(const std::vector<std::string>& arguments)
{
	switch (arguments.size())
	{
		// If arguments are of the form DROP/PUT ITEM_NAME
		case 2:
		{
			Item* item = (Item*)FindInChildren(arguments[1], EntityType::ITEM);

			if (item == NULL)
			{
				std::cout << std::endl << name << ": There is no item named \""
					<< arguments[1] << "\" in my inventory." << std::endl;
				return;
			}

			Unequip(item, false);
			
			item->SetParent((Entity*)GetRoom());

			if (item->GetParent() == (Entity*)GetRoom())
			{
				std::cout << std::endl << name << " dropped " << item->name << std::endl;
			}
		}
		break;

		// If arguments are of the form DROP/PUT ITEM_NAME_0 TO ITEM_NAME_1
		case 4:
		{
			Entity* parent = GetParent()->FindInChildren(arguments[3]);

			if (parent == NULL)
			{
				std::cout << std::endl << name << ": There is nothing named \""
					      << arguments[3] << "\" in current room." << std::endl;
				return;
			}

			if (parent->GetType() == EntityType::ITEM)
			{
				// This deals with ridiculous cases such as
				// putting a robe inside staff:
				if (!(((Item*)parent)->CanContainChildren()))
				{
					std::cout << std::endl << name << ": I cannot place anything inside \""
						<< arguments[3] << "\"." << std::endl;
					return;
				}
			} 
			else if (parent->GetType() == EntityType::OBELISK)
			{
				// Not proud of this block of code.
			} 
			else
			{
				std::cout << std::endl << name << ": I cannot place anything inside \""
						  << arguments[3] << "\"." << std::endl;
				return;
			}
			
			Item* childItem = (Item*)FindInChildren(arguments[1], EntityType::ITEM);

			if (childItem == NULL)
			{
				std::cout << std::endl << name << ": There is no item named \"" << arguments[3]
					      << "\" inside inventory." << std::endl;
				return;
			}

			Unequip(childItem, false);

			childItem->SetParent(parent);

			if (childItem->GetParent() == parent)
			{
				std::cout << std::endl << name << " placed " << childItem->name
					<< " inside " << parent->name << std::endl;

			}
		}
		break;

		// If given arguments does not met with the cases stated above:
		default:
		{
			std::cout << std::endl << name << ": I'm not sure how to respond to that command."
				      << std::endl;
		}
		break;
	}
}

void Zork::Player::EnterCombat(const std::vector<std::string>& arguments)
{
	if (!IsAlive())
	{
		return;
	}

	if (arguments.size() != 2 && arguments.size() != 3 && arguments.size() != 4)
	{
		std::cout << std::endl << name
				  << ": All I can understand is you want me to cast spell."
				  << std::endl;
		
		return;
	}

	if (arguments.size() == 2)
	{
		if (Util::Equals(arguments[1], "prayer", false))
		{
			Prayer();
			
			return;
		}
		
		std::cout << std::endl << name
			      << ": All I can understand is you want me to cast spell."
			      << std::endl;

		return;
	}

	NatureType spellNature = StringToNatureType(arguments[1]);

	if (spellNature == NatureType::NONE)
	{
		std::cout << std::endl << name
			      << ": " << NatureTypeToString(spellNature) << " is not a valid spell nature type."
			      << std::endl;
		return;
	}

	if (!HaveRune(spellNature))
	{
		std::cout << std::endl << name
				  << ": I'm not equipped with " << NatureTypeToString(spellNature) 
				  << " rune." << std::endl;
		return;
	}

	if (arguments.size() == 4)
	{
		Entity* target = GetRoom()->FindInChildren(arguments[3]);

		if (target == NULL)
		{
			std::cout << std::endl << name << ": I don't know who to attack."
					  << std::endl;

			return;
		}
		if (!target->IsCreature() || target == this)
		{
			std::cout << std::endl << name
				<< ": " << target->name << " is not a valid target."
				<< std::endl;

			return;
		}

		combatTarget = (Creature*)target;
	}

	if (combatTarget == NULL)
	{
		std::cout << std::endl << name << ": I don't know who to attack."
				  << std::endl;

		return;
	}

	if (!combatTarget->IsAlive())
	{
		std::cout << std::endl << name << ": " << combatTarget->name 
			      << " is already dead." << std::endl;

		return;
	}

	std::string spellName = arguments[2];

	if (Util::Equals(spellName, "arcanum", false))
	{
		// Attack with spellNature, than turn back to normal nature:
		natureType = spellNature;
		Attack();
		natureType = NatureType::NONE; 
		
		return;
	}
	else if (Util::Equals(spellName, "stun", false))
	{
		// Stun with spellNature, than turn back to normal nature:
		natureType = spellNature;
		Stun();
		natureType = NatureType::NONE; 

		return;
	}
	else
	{
		std::cout << std::endl << name
			      << ": " << NatureTypeToString(spellNature) << " "
			      << spellName << " is not a valid spell." << std::endl;
		
		return;
	}
}

void Zork::Player::CommitStats(const std::vector<std::string>& arguments)
{
	if (arguments.size() != 3)
	{
		std::cout << std::endl << name 
			      << ": All I can understand is you want to commit stat points." << std::endl;
		
		return;
	}

	if (statPoints <= 0)
	{
		std::cout << std::endl << name 
			      << ": I don't have any uncommitted stat points." << std::endl;

		return;
	}

	std::string statStr = arguments[1];
	std::string pointStr = arguments[2];
	int committedPoints = 0;

	if (!Util::IsInteger(pointStr))
	{
		std::cout << std::endl << name 
				  << ": Please enter a valid stat point to commit." << std::endl;
		
		return;
	}

	committedPoints = std::stoi(pointStr);

	if (committedPoints <= 0)
	{
		std::cout << std::endl << name 
			      << ": I can only commit points higher than 0 to my stats." << std::endl;

		return;
	}

	committedPoints = statPoints >= committedPoints ? committedPoints : statPoints;
	statPoints -= committedPoints;

	if (Util::Equals(statStr, "attack", false))
	{
		std::cout << std::endl << name << " has committed " 
				  << committedPoints << " point(s) to Attack." << std::endl;

		stats.attack += committedPoints;

		return;
	}
	else if (Util::Equals(statStr, "defence", false))
	{
		std::cout << std::endl << name << " has committed " 
			      << committedPoints << " point(s) Defence." << std::endl;

		stats.defence += committedPoints;
		
		return;
	}
	else if (Util::Equals(statStr, "health", false))
	{
		std::cout << std::endl << name << " has committed "  
			      << committedPoints << " point(s) Health." << std::endl;
		
		stats.health += committedPoints;

		return;
	}

	std::cout << std::endl << name 
		      << ": I don't have a stat called" << statStr << std::endl;
}

void Zork::Player::Attack()
{
	std::cout << std::endl << name << " turned condensed " << NatureTypeToString(natureType)
		<< " " << attackDescription << " " << combatTarget->name << "."
		<< std::endl;

	int damage = GetAttackAmount();

	combatTarget->TakeDamage(damage, natureType);

	if (combatTarget->combatTarget == NULL)
	{
		combatTarget->combatTarget = this;
	}

	if (!combatTarget->IsAlive())
	{
		statPoints += 1;

		std::cout << std::endl << name << " has " 
			      << statPoints << " uncommited stat points now." << std::endl;
	}
}

void Zork::Player::Stun()
{
	std::cout << std::endl << name << " " << stunDescription << " " << NatureTypeToString(natureType)
		<< " and trapped " << combatTarget->name << " inside it." << std::endl;
	
	combatTarget->GetStunned(natureType);
}

void Zork::Player::Prayer()
{
	int maxPrayer = stats.health * stats.attack * 2;
	int prayer = Util::RandomNumber(maxPrayer / 2, maxPrayer);

	AddHealth(prayer);

	std::cout << std::endl << name << " " << prayerDescription << std::endl
			  << "Gods of mana have granted " << name << " with additional "
		      << prayer << " health." << std::endl;  
}

const bool Zork::Player::InEndRoom() const
{
	return GetRoom() == endRoom;
}

const bool Zork::Player::HaveRune(NatureType natureType) const
{
	for (
		std::list<Item*>::const_iterator iterator = runes.begin();
		iterator != runes.cend();
		++iterator
		)
	{
		if ((*iterator)->GetNatureType() == natureType)
		{
			return true;
		}
	}

	return false;
}

const Zork::EntityType Zork::Player::GetType() const
{
	return EntityType::PLAYER;  
}

Zork::Player::~Player()
{
}
