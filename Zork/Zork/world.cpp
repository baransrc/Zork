#include "world.h"

Zork::World::World()
{
	updateTimer = clock();

	Intro();

	Entity* entity1 = new Entity("Name1", "Desc1", NULL);
	Entity* entity2 = new Entity("Name2", "Desc2", entity1);
	Entity* entity3 = new Entity("Name3", "Desc3", entity2);
	Entity* entity4 = new Entity("Name4", "Desc4", entity1);
	
	entity1->LookInside();

	std::cout << std::endl;
	
	entity2->LookInside();	

	std::cout << std::endl;

	std::cout << "Find all results:" << std::endl;
	std::list<Entity*> children;

	entity1->FindAllInChildren(Zork::EntityType::ENTITY, &children);

	for (std::list<Entity*>::const_iterator iterator = children.begin(); iterator != children.cend(); ++iterator)
	{
		std::cout << "\t" << (*iterator)->name << std::endl;	
	}
}

void Zork::World::Intro()
{
	std::cout << "You find yourself in a dark area beneath the surface of the ground, slowly regaining your consciousness." << std::endl;
	std::cout << "You see an obelisk right before you, surrounded with a faded magic sircle." << std::endl;
	std::cout << "On the obelisk, lies four cavities. A triangle, a cross, a square and a circle." << std::endl;
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
		std::cout << "Who am I?" << std::endl;
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

bool Zork::World::Update(std::vector<std::string>& arguments)
{
	return false;
}

bool Zork::World::Parse(std::vector<std::string>& arguments)
{
	return false;
}

void Zork::World::GameLoop()
{
	// TODO: Implement.
}

Zork::World::~World()
{
	// TODO: Implement.
}
