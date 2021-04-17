#include "world.h"

Zork::World::World()
{
	Intro();
}

void Zork::World::Intro()
{
	std::cout << "You find yourself in a dark area beneath the surface of the ground, slowly regaining your consciousness." << std::endl;
	std::cout << "You see a obelisk right before you, surrounded with a faded magic sircle." << std::endl;
	std::cout << "On the obelisk, lies four cavities. A triangle, a cross, a square and a circle." << std::endl;
	std::cout << "As you slowly regain your memories, you struggle to recall your name." << std::endl;

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
