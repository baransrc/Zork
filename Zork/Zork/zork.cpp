#include <iostream>
#include <string>
#include "util.h"
#include "world.h"

int main()
{
	std::cout << "This project will become a Zork inspired game in the future commits!" << std::endl;

	// Initialize World:
	Zork::World* world = new Zork::World();

	// Trying input management:
	while (true)
	{
		std::string userInput = "";

		getline(std::cin, userInput);
		
		std::vector<std::string> tokens = Util::splitStringToWords(userInput);

		std::cout << "User Input Is:" << std::endl;

		for (auto& token : tokens)
		{
			std::cout << token << std::endl;
		}

		std::cout << "------" << std::endl;

		tokens.clear();
	}

	system("pause");

	return EXIT_SUCCESS;
}