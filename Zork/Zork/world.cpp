#include "world.h"
#include "entity.h"
#include "room.h"
#include "creature.h"
#include "player.h"
#include "exit.h"
#include "stats.h"
#include "item.h"
#include "obelisk.h"
#include <list>

Zork::World::World()
{
	std::string playerName = Intro();

	// --- Rooms ---
	Room* obeliskRoom = new Room("Hall of ancient obelisk", "It is a dark circle shaped room.");
	Room* fireRoom = new Room("Ancient hell", "It is a really hot area with blindingly bright lava flowing everywhere.");
	Room* exitRoom = new Room("Shrine of Shana", "It is a room that resembles eternity with a overwhelmingly godly presence.");
	Room* airRoom = new Room("Temple of Breeze", "You feel a breath blowing to your ears, it sounds like words of curse.");
	Room* waterRoom = new Room("Lost Seas", "Your body is half in water, it feels like something alive.");
	Room* earthRoom = new Room("Ancient Artifacts", "It is a room full of earthen artifacts that holds ancient technology.");
	Room* corridor = new Room("Passage", "It is a really long passage full of unsettling aesthetics.");
	Room* hallway = new Room("Hallway", "Smell is really bad here. On the ground lies countless rotten sea food.");
	Room* library = new Room("Abandoned Library", "It is full of empty book shelves from the ground to the endless ceiling. In the middle of the room, there are hovering objects on a earthen pedestal.");

	entities.push_back(obeliskRoom);
	entities.push_back(fireRoom);
	entities.push_back(exitRoom);
	entities.push_back(airRoom);
	entities.push_back(waterRoom);
	entities.push_back(earthRoom);
	entities.push_back(corridor);
	entities.push_back(hallway);
	entities.push_back(library);

	// --- Exits ---
	// Obelisk Room Exits:
	Exit* obeliskNorth = new Exit(
		"Shiny Door",
		"It has a cross shaped carving and hot steam is coming from it's sides.",
		Direction::NORTH,
		obeliskRoom,
		fireRoom,
		false
	);
	Exit* obeliskEast = new Exit(
		"Light Void",
		"It slightly illuminates the room. It has a magic circle consisting of a triangle, a square, a circle and a cross.",
		Direction::EAST,
		obeliskRoom,
		exitRoom,
		true
	);
	Exit* obeliskWest = new Exit(
		"Black Broken Wall",
		"It looks like someone break the wall before you were here. Among the broken parts, there is a triangle carving.",
		Direction::WEST,
		obeliskRoom,
		airRoom,
		false
	);
	Exit* obeliskSouth = new Exit(
		"Wet Rotten Door",
		"It has a circle shaped carving and it smells fishy.(Haha)",
		Direction::SOUTH,
		obeliskRoom,
		waterRoom,
		false
	);

	// Exit room exits:
	Exit* exitWest = new Exit(
		"Dark Void",
		"It leaks light to the other side and has a magic circle consisting of a triangle, a square, a circle and a cross.",
		Direction::NORTH,
		exitRoom,
		obeliskRoom,
		false
	);

	// Fire Room Exits:
	Exit* fireRoomSouth = new Exit(
		"Shiny Door",
		"It is made of molten iron shining like hellfire.",
		Direction::SOUTH,
		fireRoom,
		obeliskRoom,
		false
	);
	Exit* fireRoomWest = new Exit(
		"Red Door",
		"It's a door with unsettling reliefs.",
		Direction::WEST,
		fireRoom,
		corridor,
		false
	);

	// Corridor Room Exits:
	Exit* corridorEast = new Exit(
		"Shiny Red Door",
		"It's a red door made of molten iron with ugly reliefs. Among the reliefs there is a cross shaped carving.",
		Direction::EAST,
		corridor,
		fireRoom,
		false
	);
	Exit* corridorSouth = new Exit(
		"Red Broken Wall",
		"It looks like it exploded from inside. Among the broken parts, there is a triangle carving.",
		Direction::SOUTH,
		corridor,
		airRoom,
		false
	);

	// Air room exits:
	Exit* airRoomNorth = new Exit(
		"Red Broken Wall",
		"It looks like it exploded from inside.",
		Direction::NORTH,
		airRoom,
		corridor,
		false
	);
	Exit* airRoomEast = new Exit(
		"Black Broken Wall",
		"It looks like it exploded from inside.",
		Direction::EAST,
		airRoom,
		obeliskRoom,
		false
	);
	Exit* airRoomSouth = new Exit(
		"Blue Broken Wall",
		"It looks like it exploded from inside. A really bad smell comes from there.",
		Direction::SOUTH,
		airRoom,
		hallway,
		false
	);

	// Hallway exits:
	Exit* hallwayNorth = new Exit(
		"Broken Wall",
		"Looks like it is exploded from inside.\nAmong the broken parts, there is a triangle carving.\nAeavy breathing sounds comes from there.",
		Direction::NORTH,
		hallway,
		airRoom,
		false
	);
	Exit* hallwayEast = new Exit(
		"Wet Rotten Door",
		"It has a circle shaped carving and a really bad smell comes from it.",
		Direction::EAST,
		hallway,
		waterRoom,
		false
	);
	Exit* hallwaySouth = new Exit(
		"Slightly Open Curtain",
		"From the gap you can see hovering objects on a earthen pedestal.",
		Direction::SOUTH,
		hallway,
		library,
		false
	);

	// Library exits:
	Exit* libraryNorth = new Exit(
		"Slightly Open Curtain",
		"From the gap you can see and smell the rotten sea foods.",
		Direction::NORTH,
		library,
		hallway,
		false
	);
	Exit* libraryEast = new Exit(
		"Earthen Gate",
		"It has detailed reliefs and a square shaped carving at the very top.",
		Direction::EAST,
		library,
		earthRoom,
		false
	);

	// Earth room exits:
	Exit* earthRoomWest = new Exit(
		"Earthen Gate",
		"It has detailed reliefs and a square shaped carving at the very top.",
		Direction::WEST,
		earthRoom,
		library,
		false
	);
	Exit* earthRoomNorth = new Exit(
		"Rotten Door",
		"It has a water leak coming from the bottom with an awful smell and a circle shaped carving.",
		Direction::NORTH,
		earthRoom,
		waterRoom,
		false
	);

	// Water room exits:
	Exit* waterRoomNorth = new Exit(
		"Wet Rotten Door",
		"It leaks a great amount of smell to outside and looks like it's about to break down.",
		Direction::NORTH,
		waterRoom,
		obeliskRoom,
		false
	);
	Exit* waterRoomWest = new Exit(
		"Wet Rotten Door",
		"It is covered with rotten food residues.",
		Direction::WEST,
		waterRoom,
		hallway,
		false
	);
	Exit* waterRoomSouth = new Exit(
		"Wet Rotten Door",
		"It has detailed reliefs and a square shaped carving at the very top.",
		Direction::SOUTH,
		waterRoom,
		earthRoom,
		false
	);

	entities.push_back(obeliskNorth);
	entities.push_back(obeliskEast);
	entities.push_back(obeliskWest);
	entities.push_back(obeliskSouth);
	entities.push_back(exitWest);
	entities.push_back(fireRoomSouth);
	entities.push_back(fireRoomWest);
	entities.push_back(corridorEast);
	entities.push_back(corridorSouth);
	entities.push_back(airRoomNorth);
	entities.push_back(airRoomEast);
	entities.push_back(airRoomSouth);
	entities.push_back(hallwayNorth);
	entities.push_back(hallwayEast);
	entities.push_back(hallwaySouth);
	entities.push_back(libraryNorth);
	entities.push_back(libraryEast);
	entities.push_back(earthRoomWest);
	entities.push_back(earthRoomNorth);
	entities.push_back(waterRoomNorth);
	entities.push_back(waterRoomWest);
	entities.push_back(waterRoomSouth);


	// --- Player ---
	// Initial Stats:
	Stats playerStats = { // This is used as plain old data.
		5, // Health
		2, // Attack
		1  // Defence
	};
	player = new Player(
		playerName.c_str(),
		"A powerful mage with no memories about his/her past.",
		"mana into the lost ancient form of magic and channeled it to",
		"recited a hymn to gods of mana.",
		"formed a prison of",
		playerStats,
		obeliskRoom
	);

	player->statPoints = 4;

	entities.push_back(player);

	// --- Creatures ---
	// TODO: Make these NPC.
	// These creatures are added for combat test.
	Stats monsterStats = { 5,2,1 };
	Creature* earthCreature = new Creature(
		"Hyx",
		"A unsettling idol that looks like a hovering human silhoulette made of rock.",
		"Ripped off a rock from itself, charged it with mana and throwed it to",
		obeliskRoom,
		monsterStats,
		NatureType::EARTH
	);
	//Creature* fireCreature = new Creature(
	//	"Hot Eye",
	//	"A frightening creature that looks like a burning eye.",
	//	"Created a spiral of fire charged with red mana and throwed it to",
	//	obeliskRoom,
	//	monsterStats,
	//	NatureType::FIRE
	//);

	entities.push_back(earthCreature);
	//entities.push_back(fireCreature);

	// --- Items ---
	Stats staffStats = { 0, 1, 0 };
	Stats armorStats = { 0, 0, 2 };
	Stats zeroStats = { 0, 0, 0 };
	Item* staff = new Item(
		"Staff",
		"A staff made of a branch of the tree of life.",
		library,
		ItemType::WEAPON,
		staffStats,
		NatureType::NONE
	);
	Item* chest = new Item(
		"Chest",
		"A wooden chest.",
		corridor,
		ItemType::CONTAINER,
		zeroStats,
		NatureType::NONE
	);
	Item* armor = new Item(
		"Robe",
		"A blue robe made of dragon hair.",
		chest,
		ItemType::ARMOR,
		armorStats,
		NatureType::NONE
	);
	Item* fireRune = new Item(
		"Faerl",
		"A cross shaped, red colored rune stone.",
		obeliskRoom,
		ItemType::RUNE,
		zeroStats,
		NatureType::FIRE
		);
	Item* waterRune = new Item(
		"Elemyr",
		"A circle shaped, blue colored rune stone.",
		obeliskRoom,
		ItemType::RUNE,
		zeroStats,
		NatureType::WATER
	);
	Item* airRune = new Item(
		"Sendulai",
		"A triangle shaped, gray colored rune stone.",
		obeliskRoom,
		ItemType::RUNE,
		zeroStats,
		NatureType::AIR
	);
	Item* earthRune = new Item(
		"Traiche",
		"A square shaped, green colored rune stone.",
		earthCreature,
		ItemType::RUNE,
		zeroStats,
		NatureType::EARTH
	);


	entities.push_back(staff);
	entities.push_back(chest);
	entities.push_back(armor);
	entities.push_back(fireRune);
	entities.push_back(waterRune);
	entities.push_back(airRune);
	entities.push_back(earthRune);

	Obelisk* obelisk = new Obelisk(
		"Obelisk",
		"It has four cavities, from top to bottom there are a triangle, a square, a circle and a cross.",
		obeliskRoom,
		obeliskEast
	);

	entities.push_back(obelisk);

	player->GetParent()->Look();
}

std::string Zork::World::Intro()
{
	std::cout << "You find yourself in a dark area beneath the surface of the ground, slowly regaining your consciousness." << std::endl;
	std::cout << "You see an obelisk right before you, surrounded with a faded magic sircle." << std::endl;
	std::cout << "On the obelisk, lies four cavities. A triangle, a square, a circle and a cross." << std::endl;
	std::cout << "As you slowly regain your consciousness, you struggle to recall your name." << std::endl;

	// Get character name as input from user until she/he decides:
	std::string characterName = DetermineCharacterName();

	std::cout << std::endl << characterName << ": "
		<< " I don't remember why I am here. Anyway, this place seems highly unfriendly, I must find a way out."
		<< std::endl;

	return characterName;
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

		while ((!Util::Equals(answer, "y", false)) &&
			(!Util::Equals(answer, "yes", false)) &&
			(!Util::Equals(answer, "n", false)) &&
			(!Util::Equals(answer, "no", false)))
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

	// No argument:
	if (arguments.size() <= 0)
	{
		result = false;
	}

	// Clear screen arguments:
	else if (Util::Equals(arguments[0], "cls", false) ||
		Util::Equals(arguments[0], "clear", false)    ||
		Util::Equals(arguments[0], "flush", false))
	{
		system("CLS");
	}

	// Drop item arguments:
	else if (Util::Equals(arguments[0], "drop", false) ||
		     Util::Equals(arguments[0], "put", false)  ||
		     Util::Equals(arguments[0], "place", false))
	{
		player->Put(arguments);
	}

	// Take item arguments:
	else if (Util::Equals(arguments[0], "take", false) ||
			 Util::Equals(arguments[0], "loot", false) ||
			 Util::Equals(arguments[0], "get", false)  ||
			 Util::Equals(arguments[0], "pick", false))
	{
		player->Take(arguments);
	}

	// Move arguments:
	else if (Util::Equals(arguments[0], "go", false)   ||
		     Util::Equals(arguments[0], "move", false) ||
		     Util::Equals(arguments[0], "walk", false))
	{
		player->Go(arguments);
	}

	// Look arguments:
	else if (Util::Equals(arguments[0], "look", false) ||
		     Util::Equals(arguments[0], "gaze", false) ||
		     Util::Equals(arguments[0], "l", false))
	{
		player->Look(arguments);
	}

	// Examine arguments:
	else if (Util::Equals(arguments[0], "examine", false) ||
			 Util::Equals(arguments[0], "inspect", false) ||
		     Util::Equals(arguments[0], "info", false))
	{
		player->Examine(arguments);
	}

	// Attack arguments:
	else if (Util::Equals(arguments[0], "cast", false) ||
			 Util::Equals(arguments[0], "use", false) ||
		     Util::Equals(arguments[0], "throw", false))
	{
		player->EnterCombat(arguments);
	}

	// Equip arguments:
	else if (Util::Equals(arguments[0], "equip", false) ||
		     Util::Equals(arguments[0], "eq", false))
	{
		player->Equip(arguments);
	}

	// Unequip arguments:
	else if (Util::Equals(arguments[0], "unequip", false) ||
		     Util::Equals(arguments[0], "uneq", false))
	{
		player->Unequip(arguments);
	}

	// Commit Stats arguments:
	else if (Util::Equals(arguments[0], "commit", false) ||
			 Util::Equals(arguments[0], "add", false))
	{
		player->CommitStats(arguments);
	}

	// Inventory arguments:
	else if (Util::Equals(arguments[0], "bag", false) ||
			 Util::Equals(arguments[0], "inventory", false) ||
			 Util::Equals(arguments[0], "inv", false)
		)
	{
		player->PrintInventory();
	}

	return result;
}

void Zork::World::GameLoop()
{
	for (std::list<Entity*>::iterator iterator = entities.begin(); iterator != entities.end(); ++iterator)
	{
		(*iterator)->Update();
	}
}

const std::string Zork::World::GetPlayerName() const
{
	return player->name;
}

Zork::World::~World()
{
	for (std::list<Entity*>::iterator iterator = entities.begin(); iterator != entities.end(); ++iterator)
	{
		delete (*iterator);
	}

	entities.clear();
}
