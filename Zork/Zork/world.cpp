#include "world.h"
#include "entity.h"
#include "room.h"
#include "creature.h"
#include "exit.h"
#include "stats.h"
#include "item.h"
#include <list>

Zork::World::World()
{
	updateTimer = clock();

	Intro();

	// Rooms:
	Room* obeliskRoom = new Room("Hall of ancient obelisk", "It is a dark circle shaped room.");
	Room* fireRoom = new Room("Ancient hell", "It is a really hot area with blindingly bright lava flowing everywhere.");
	Room* exitRoom = new Room("Shrine of Shana", "It is a room that resembles eternity with a overwhelmingly godly presence.");

	entities.push_back(obeliskRoom);
	entities.push_back(fireRoom);
	entities.push_back(exitRoom);

	// Exits:
	Exit* obeliskNorth = new Exit("Shiny Door", 
		"It has a cross shaped carving and hot steam is coming from it's sides.", 
		Direction::NORTH, 
		obeliskRoom, 
		fireRoom, 
		false);

	Exit* obeliskEast = new Exit("pure white door", 
		"It slightly illuminates the room.", 
		Direction::EAST, 
		obeliskRoom, 
		exitRoom, 
		false);

	entities.push_back(obeliskNorth);
	entities.push_back(obeliskEast);


	// Creatures:
	// TODO: Make these NPC.
	// These creatures are added for combat test.
	Stats monsterStats = {5,2,1}; // This is used as plain old data.
	Creature* earthCreature = new Creature(
		"Rock Idol", 
		"A unsettling idol that looks like a hovering human silhoulette made of rock.",
		"Ripped off a rock from itself, charged it with mana and throwed it to",
		obeliskRoom,
		monsterStats,
		NatureType::EARTH
		);
	Creature* fireCreature = new Creature(
		"Hot Eye",
		"A frightening creature that looks like a burning eye.",
		"Created a spiral of fire charged with red mana and throwed it to",
		obeliskRoom,
		monsterStats,
		NatureType::FIRE
	);

	entities.push_back(earthCreature);
	entities.push_back(fireCreature);

	// Items:
	Stats staffStats = {0, 1, 0};
	Item* staff = new Item("Staff", 
		"A staff made of a branch of the tree of life.", 
		fireCreature, 
		ItemType::WEAPON, 
		staffStats);

	Stats armorStats = {0, 0, 2};
	Item* armor = new Item("Robe", 
		"A blue robe made of dragon hair.",
		earthCreature,
		ItemType::ARMOR, 
		armorStats);

	obeliskRoom->Look();

	entities.push_back(staff);
	entities.push_back(armor);
	
	// Basic combat Test:
	std::vector<std::string> combatCommandsTest;

	combatCommandsTest.push_back("attack");
	combatCommandsTest.push_back("Rock Idol");

	fireCreature->Attack(combatCommandsTest);

	std::vector<std::string> equipWeaponCommandsTest;
	equipWeaponCommandsTest.push_back("equip");
	equipWeaponCommandsTest.push_back("Staff");

	fireCreature->Equip(equipWeaponCommandsTest);

	fireCreature->Attack(combatCommandsTest);

	std::vector<std::string> equipArmorCommandsTest;
	equipArmorCommandsTest.push_back("equip");
	equipArmorCommandsTest.push_back("Robe");
	earthCreature->Equip(equipArmorCommandsTest);

	fireCreature->Attack(combatCommandsTest);

	earthCreature->Unequip(equipArmorCommandsTest);

	fireCreature->Attack(combatCommandsTest);

	fireCreature->Unequip(equipWeaponCommandsTest);

	fireCreature->Attack(combatCommandsTest);
}

void Zork::World::Intro()
{
	std::cout << "You find yourself in a dark area beneath the surface of the ground, slowly regaining your consciousness." << std::endl;
	std::cout << "You see an obelisk right before you, surrounded with a faded magic sircle." << std::endl;
	std::cout << "On the obelisk, lies four cavities. A triangle, a square, a circle and a cross." << std::endl;
	std::cout << "As you slowly regain your consciousness, you struggle to recall your name." << std::endl;

	// Get character name as input from user until she/he decides:
	std::string characterName = DetermineCharacterName();
	
	std::cout << characterName << ": " << " I don't remember why I am here. Anyway, this place seems highly unfriendly, I must find a way out." << std::endl;
}

std::string Zork::World::DetermineCharacterName()
{
	std::string characterName = "";
	bool nameSelected = false;

	while (!nameSelected)
	{
		std::cout << "You ask yourself: \"Who am I?\"" << std::endl;
		std::cin >> characterName;
		
		std::string answer = "";

		while (answer != "Y" && 
			   answer != "N" && 
			   answer != "y" && 
			   answer != "n" && 
			   answer != "Yes" && 
			   answer != "No" && 
			   answer != "yes" && 
			   answer != "no")
		{
			std::cout << "Is " << characterName << " my name? (Y\\N)" << std::endl;
			std::cin >> answer;
		}

		nameSelected = (answer[0] == 'Y' || answer[0] == 'y');
	}

	return characterName;
}

void Zork::World::Update(std::vector<std::string>& arguments)
{
	if (!Parse(arguments))
	{
		return;
	}

	GameLoop();
}

bool Zork::World::Parse(std::vector<std::string>& arguments)
{
	bool result = true;

	switch (arguments.size())
	{
		case 0:
		{
			result = false;
		} 
		break;

		case 1:
		{
			if (Util::Equals(arguments[0], "cls") || Util::Equals(arguments[0], "clear") || Util::Equals(arguments[0], "flush"))
			{
				system("CLS");
			}
		} 
		break;
	}

	return result;
}

void Zork::World::GameLoop()
{
	// TODO: Implement.
}

Zork::World::~World()
{
	for (std::list<Entity*>::iterator iterator = entities.begin(); iterator != entities.end(); ++iterator)
	{
		delete (*iterator);
	}

	entities.clear();
}
